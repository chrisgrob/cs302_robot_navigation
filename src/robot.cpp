#include "robot.h"

// Default c-tor
Robot::Robot() : x_pos_(0), y_pos_(0), orientation_(South) {}

// Parameterized c-tor
Robot::Robot(const CoordinateType pos, const CardinalDirection orientation, const OccupancyGridMap map)
  : pos_(pos), orientation_(orientation), map_(map) {}



// setters and getters
void Robot::set_pos(const CoordinateType pos) { pos_ = pos; }
CoordinateType Robot::get_pos() const { return pos_; }

void Robot::set_orientation(const CardinalDirection orientation) { orientation_ = orientation; }
CardinalDirection Robot::get_orientation() const { return orienation_; }

void Robot::set_map(const OccupancyGridMap map) { map_ = map; }
const OccupancyGridMap& Robot::get_map() const { return map_; }



// cast out rays and get sensor readings
void Robot::RayCasting()
{
  if (orientation_ == North)
  {
    RayRange(0, 180);
  }
  else if (orientation_ == East)
  {
    RayRange(-90, 90);
  }
  else if (orientation_ == South)
  {
    RayRange(180, 360);
  }
  else if (orientation_ == West)
  {
    RayRange(90, 270);
  }
  else
  {
    throw;
  }
}

// casts rays from start to end
// start and end should be 180 degrees apart
void Robot::RayRange(const int start, const int end)
{
  for (int i = start; i <= end; i += 15)
  {
    const int actual_direction = Localize(i);

    Ray(actual_direction);
  }
}

// casts Ray and updates probabilities
// direction should be from 0 to 359 degrees
void Robot::Ray(const int direction)
{
  const unsigned int quartile = Quartile(direction);

  const SignPair steps = Steps(quartile);

  const bool vertical = (90 == direction) || (270 == direction);

  const bool diagonal = 0 == direction % 45;

  if (vertical)
  {
    CastVertical(steps);
  }
  else if (diagonal) 
  {
    CastDiagonal(steps);
  }
  else
  {
    Cast(steps, direction);
  }
}

void Robot::Cast(const SignPair steps, const int direction)
{
  const double slope = Slope(direction);

  double ray_distance = 0.0;
  auto ray_pos = std::make_pair((float)x_pos_, (float)y_pos_);
  auto read_pos = std::make_pair(x_pos_, y_pos_);

  while (ray_distance < 50.0)
  {
    ray_pos.first += steps.first * 1.0;
    ray_pos.second = slope * ray_pos.first;

    const std::pair<VertexType, Trilean> desired_vertex = DesiredVertex(read_pos, ray_pos, steps, map_);

    if (desired_vertex.second == Unknown) 
    {
      break;
    }
    if (desired_vertex.second == False) 
    {
      UpdateMap(desired_vertex.first, 0.9);
      break;
    }
    else if (desired_vertex.second == True)
    {
      UpdateMap(desired_vertex.first, 0.7);
      read_pos = map_.Coordinate(desired_vertex.first)
    }
    else
    {
      throw;
    }

    ray_distance = VectorMagnitude(std::make_pair(ray_pos.first - x_pos_, ray_pos.second - y_pos_));
  }
}



void Robot::CastVertical(const SignPair steps)
{
  CoordinateType read_pos = pos_;

  int distance = 0;

  while (distance < 50)
  {
    const CardinalDirection desired_direction = DesiredDirectionVertical(steps);

    const VertexType this_vertex = map_.Vertex(read_pos);

    const std::pair<EdgeType, bool> desired_edge = DesiredEdge(this_vertex, desired_direction, map_);

    const std::pair<VertexType, Trilean> desired_vertex = DesiredVertexHelper(desired_edge, map_);

    if (desired_vertex.second == Unknown)
    {
      break;
    }
    if (desired_vertex.second == False)
    {
      UpdateMap(desired_vertex.first, 0.9);
      break;
    }
    else if (desired_vertex.second == True)
    {
      UpdateMap(desired_vertex.first, 0.7);
      read_pos = map_.Coordinate(desired_vertex.first)
    }
    else
    {
      throw;
    }

    distance++;
  }
}



void Robot::CastDiagonal(const SignPair steps)
{
  CoordinateType read_pos = pos_;

  double distance = 0;

  while (distance < 50)
  {
    const CardinalDirection desired_direction = DesiredDirectionDiagonal(steps);

    const VertexType this_vertex = map_.Vertex(read_pos);

    const std::pair<EdgeType, bool> desired_edge = DesiredEdge(this_vertex, desired_direction, map_);

    const std::pair<VertexType, Trilean> desired_vertex = DesiredVertexHelper(desired_edge, map_);

    if (desired_vertex.second == Unknown)
    {
      break;
    }
    if (desired_vertex.second == False)
    {
      UpdateMap(desired_vertex.first, 0.9);
      break;
    }
    else if (desired_vertex.second == True)
    {
      UpdateMap(desired_vertex.first, -0.7);
      read_pos = map_.Coordinate(desired_vertex.first)
    }
    else
    {
      throw;
    }

    distance += sqrt(2);
  }
}



void UpdateMap(const VertexType vertex, const double sensor_reading)
{

}
