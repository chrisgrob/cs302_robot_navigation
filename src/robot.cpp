#include "robot.h"

// Default c-tor
Robot::Robot() {} 
//Sets the X, Y coordinates to 0,0 and facing south

// Parameterized c-tor
Robot::Robot(const CoordinateType pos, const CardinalDirectionType orientation, const OccupancyGridMap map)
  : occupied_vertex_(map.Vertex(pos)), orientation_(orientation), map_(map) {}
//Pased off of the cordinate position and orientation, it will make a map and be able to save that map


// setters and getters
void Robot::set_pos(const CoordinateType pos) { occupied_vertex_ = map_.Vertex(pos); } //set position
CoordinateType Robot::get_pos() const { return map_.Coordinate(occupied_vertex_); } //get position

void Robot::set_orientation(const CardinalDirectionType orientation) { orientation_ = orientation; } //set orientation
CardinalDirectionType Robot::get_orientation() const { return orientation_; } //get orientation

void Robot::set_map(const OccupancyGridMap map) { map_ = map; } //set map
const OccupancyGridMap& Robot::get_map() const { return map_; } //get map



// cast out rays and get sensor readings
void Robot::RayCasting()
{
  if (orientation_ == CardinalDirection::North) //Calls Ray Range using the degrees reletive to where the robot is facing
  {
    RayRange(0, 180);
  }
  else if (orientation_ == CardinalDirection::East)
  {
    RayRange(-90, 90);
  }
  else if (orientation_ == CardinalDirection::South)
  {
    RayRange(180, 360);
  }
  else if (orientation_ == CardinalDirection::West)
  {
    RayRange(90, 270);
  }
  else
  {
    throw;
  }
} //end RayCasting



// casts rays from start to end
// start and end should be 180 degrees apart
void Robot::RayRange(const int start, const int end)
{
  for (int i = start; i <= end; i += 15) //start and end are the degrees to which it should be checking
  {
    const int actual_direction = Localize(i); //Sets the direction that the ray is creating between 0-360*

    Ray(actual_direction); //Sets the ray to be in the direction that it is facing
  }
}



// casts Ray and updates probabilities
// direction should be from 0 to 359 degrees
void Robot::Ray(const int direction)
{
  const unsigned int quartile = Quartile(direction); //Sets the quartile to be in the direction that it is facing

  const SignPair steps = Steps(quartile);

  const bool vertical = (90 == direction) || (270 == direction); 

  const bool diagonal = 0 != direction && (180 != direction && 0 == direction % 45);

  CastType cast_type;

  if (vertical)
  {
    cast_type = Vertical;
  }
  else if (diagonal) 
  {
    cast_type = Diagonal;
  }
  else
  {
    cast_type = Normal;
  }

  Cast(steps, direction, cast_type);
}



void Robot::Cast(const SignPair steps, const int direction, const CastType cast_type)
{
  double ray_distance = 0.0;
  DoubleCoordinateType ray_pos = std::make_pair(0.0, 0.0);
  VertexType read_vertex = occupied_vertex_;
  bool obstructed = false;
  bool x_increment = false;

  while (ray_distance < 50.0 && !obstructed)
  {
    ray_pos = RayIncrement(ray_pos, direction, steps, x_increment, cast_type);

    VertexType vertex;
    TrileanType trilean;
    bool x_increment;
    DesiredVertex(
      read_vertex, 
      ray_pos, 
      steps, 
      cast_type, 
      vertex, 
      trilean, 
      x_increment);

    switch (trilean)
    {
    case Trilean::Unknown:
    {
      obstructed = true;
      break;
    }
    case Trilean::False:
    {
      UpdateMap(vertex, 0.9);
      obstructed = true;
      break;
    }
    case Trilean::True:
    {
      UpdateMap(vertex, -0.7);
      read_vertex = vertex;
      break;
    }
    }

    ray_distance = VectorMagnitude(ray_pos);
  }
}



DoubleCoordinateType Robot::RayIncrement(
  const DoubleCoordinateType ray_pos, 
  const int direction, 
  const SignPair steps, 
  const bool x_increment,
  CastType cast_type)
{
  DoubleCoordinateType ray_increment = ray_pos;

  switch (cast_type)
  {
  case Vertical:
  {
    ray_increment.second += steps.second * 1.0;
    break;
  }
  case Diagonal:
  {
    ray_increment.first += steps.first * 1.0;
    ray_increment.second += steps.second * 1.0;
    break;
  }
  case Normal:
  {
    if (x_increment) {
      ray_increment.first += steps.first * 1.0;

      const double slope = Slope(direction);

      ray_increment.second = slope * ray_increment.first;
    }
    break;
  }
  }

  return ray_increment;
}



// Main helper for Cast()
void Robot::DesiredVertex(
  const VertexType read_vertex,
  const DoubleCoordinateType ray_pos,
  const SignPair steps,
  const CastType cast_type,
  VertexType& vertex,
  TrileanType& trilean,
  bool& boolean)
{

  const CardinalDirectionType desired_direction = DesiredDirection(read_vertex, ray_pos, steps, cast_type);
  const std::pair<EdgeType, bool> desired_edge = DesiredEdge(read_vertex, desired_direction);

  const bool x_increment = XIncrement(desired_direction);

  const std::pair<VertexType, TrileanType> vertex_from_edge = VertexFromEdge(desired_edge);

  vertex = vertex_from_edge.first;
  trilean = vertex_from_edge.second;
  boolean = x_increment;
}



CardinalDirectionType Robot::DesiredDirection(
  const VertexType read_vertex, 
  const DoubleCoordinateType ray_pos, 
  const SignPair steps, 
  const CastType cast_type)
{
  CardinalDirectionType desired_direction;

  switch (cast_type)
  {
  case Vertical:
  {
    desired_direction = DesiredDirectionVertical(steps);
    break;
  }
  case Diagonal:
  {
    desired_direction = DesiredDirectionDiagonal(steps);
    break;
  }
  case Normal:
  {
    desired_direction = DesiredDirectionNormal(read_vertex, ray_pos, steps);
    break;
  }
  default:
    throw;
  }

  return desired_direction;
}



// Either North or South depending on steps
CardinalDirectionType Robot::DesiredDirectionVertical(const SignPair steps)
{
  CardinalDirectionType direction;

  switch (steps.second)
  {
  case Sign::Negative:
  {
    direction = CardinalDirection::North;
    break;
  }
  case Sign::Positive:
  {
    direction = CardinalDirection::South;
    break;
  }
  default:
    throw;
  }

  return direction;
}


// Similar to DesiredDirectionVertical()
CardinalDirectionType Robot::DesiredDirectionDiagonal(const SignPair steps)
{
  CardinalDirectionType direction;

  switch (steps.first)
  {
  case Sign::Positive:
  {
    switch (steps.second)
    {
    case Sign::Negative:
    {
      direction = CardinalDirection::NorthEast;
      break;
    }
    case Sign::Positive:
    {
      direction = CardinalDirection::SouthEast;
      break;
    }
    default:
      throw;
    }
    
    break;
  }
  case Sign::Negative:
  {
    switch (steps.second)
    {
    case Sign::Negative:
    {
      direction = CardinalDirection::NorthWest;
      break;
    }
    case Sign::Positive:
    {
      direction = CardinalDirection::SouthWest;
      break;
    }
    default:
      throw;
    }
    
    break;
  }
  default:
    throw;
  }

  return direction;
}



//Gets the desired direction from where it wants to ray cast
CardinalDirectionType Robot::DesiredDirectionNormal(
  const VertexType read_vertex, 
  const DoubleCoordinateType ray_pos, 
  const SignPair steps)
{
  CardinalDirectionType direction;

  const CoordinateType read_pos = RelativeReadPos(read_vertex);
  const CoordinateType robot_pos = get_pos();

  const int read_y = read_pos.second;
  const int robot_y = robot_pos.second;
  const double ray_y = ray_pos.second;
  const int proposed_y = read_y + (-1 * steps.second);

  if (ray_y != robot_y && ray_y == proposed_y)
  {
    direction = DesiredDirectionDiagonal(steps);
  }
  else
  {
    direction = DesiredDirectionAxis(read_y, ray_y, steps);
  }

  return direction;
}




CardinalDirectionType Robot::DesiredDirectionAxis(const int read_y, const double ray_y, const SignPair steps)
{
  CardinalDirectionType direction;

  const bool horizontal = Horizontal(read_y, ray_y, steps.second);

  if (horizontal)
  {
    if (Sign::Negative == steps.first)
    {
      direction = CardinalDirection::West;
    }
    else if (Sign::Positive == steps.first)
    {
      direction = CardinalDirection::East;
    }
    else
    {
      throw;
    }
  }
  else
  {
    if (Sign::Negative == steps.second)
    {
      direction = CardinalDirection::North;
    }
    else if (Sign::Positive == steps.second)
    {
      direction = CardinalDirection::South;
    }
    else
    {
      throw;
    }
  }

  return direction;
}



std::pair<EdgeType, bool> Robot::DesiredEdge(const VertexType vertex, const CardinalDirectionType desired_direction)
{ //Returns the desired edge of the pair and tells it where it should be facing for the proper edge
  std::pair<EdgeType, bool> desired_edge;
  
  desired_edge.second = false;

  const auto available_edges = boost::out_edges(vertex, map_.get_map());

  for (auto iter = available_edges.first; iter != available_edges.second; iter++)
  {
    // CardinalDirection edge_direction = boost::get(CardinalDirection, map.get_map(), *iter);
    CardinalDirectionType edge_direction = map_.get_map()[*iter];

    if (edge_direction == desired_direction)
    {
      desired_edge.first = *iter;
      desired_edge.second = true;
    }
  }

  return desired_edge;
}




std::pair<VertexType, TrileanType> Robot::VertexFromEdge(const std::pair<EdgeType, bool> edge)
{
  std::pair<VertexType, TrileanType> vertex_from_edge;

  if (edge.second) 
  {
    vertex_from_edge.first = boost::target(edge.first, map_.get_map());

    if (IsFree(vertex_from_edge.first))
    {
      vertex_from_edge.second = Trilean::True;
    }
    else
    {
      vertex_from_edge.second = Trilean::False;
    }
  }
  else
  {
    vertex_from_edge.first = 0;
    vertex_from_edge.second = Trilean::Unknown;
  }

  return vertex_from_edge;
}



void Robot::UpdateMap(const VertexType vertex, const double sensor_reading)
{
  
  map_.AddToVertex(vertex, sensor_reading);
  
}

