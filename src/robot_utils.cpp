#include "robot_utils.h"

// Expects angle to be between 0-360 degrees, call localize on
// your angle first
unsigned int Quartile(const int degrees) //Checks which quartile the degree is in
{
  unsigned int quartile;

  if (degrees >= 0 && degrees < 90) //First quartile
  {
    quartile = 0;
  }
  else if (degrees >= 90 && degrees < 180) //Second quartile
  {
    quartile = 1;
  }
  else if (degrees >= 180 && degrees < 270) //3rd quartile
  {
    quartile = 2;
  }
  else if (degrees >= 270 && degrees < 360) //4th quartile
  {
    quartile = 3;
  }
  else
  {
    throw; //This shouldn't happen if we properly made it between 0-360 from other function
  }

  return quartile;
}



SignPair Steps(const unsigned int quartile) //Makes the first and second value equal to whether or not it is positive or negative as a result of the quartile
{
  SignPair steps;

  if (quartile == 0)
  {
    steps.first = Positive;
    steps.second = Negative;
  }
  else if (quartile == 1)
  {
    steps.first = Negative;
    steps.second = Negative;
  }
  else if (quartile == 2)
  {
    steps.first = Negative;
    steps.second = Positive;
  }
  else if (quartile == 3)
  {
    steps.first = Positive;
    steps.second = Positive;
  }
  else
  {
    throw;
  }

  return steps;
}



bool Horizontal(const int read_y, const float ray_y, const Sign step_y)
{
  bool horizontal = false;

  const int proposed_y = read_y + step_y;

  if (step_y == Positive)
  {
    if (ray_y > proposed_y)
    {
      horizontal = false;
    }
    else if (ray_y < proposed_y)
    {
      horizontal = true;
    }
  }
  else if (step_y == Negative)
  {
    if (ray_y < proposed_y)
    {
      horizontal = false;
    }
    else if (ray_y > proposed_y)
    {
      horizontal = true;
    }
  }

  return horizontal;
}



std::pair<VertexType, Trilean> DesiredVertex(
  const CoordinateType read_pos, 
  const FloatCoordinateType ray_pos,
  const SignPair steps, 
  const OccupancyGridMap& map)
{
  std::pair<VertexType, Trilean> desired_vertex;

  const VertexType this_vertex = map.Vertex(read_pos);

  const CardinalDirection desired_direction = DesiredDirection(read_pos.second, ray_pos.second, steps);
  std::cout << desired_direction << std::endl;
  const std::pair<EdgeType, bool> desired_edge = DesiredEdge(this_vertex, desired_direction, map);

  desired_vertex = DesiredVertexHelper(desired_edge, map);

  return desired_vertex;
}



std::pair<VertexType, Trilean> DesiredVertexHelper(
  const std::pair<EdgeType, bool> desired_edge, 
  const OccupancyGridMap& map)
{
  std::pair<VertexType, Trilean> desired_vertex;

  if (desired_edge.second)
  {
    desired_vertex.first = boost::target(desired_edge.first, map.get_map());

    if (HasEdges(desired_vertex.first, map))
    {
      desired_vertex.second = True;
    }
    else
    {
      desired_vertex.second = False;
    }
  }
  else
  {
    desired_vertex.second = Unknown;
  }

  return desired_vertex;
}



CardinalDirection DesiredDirection(const int read_y, const double ray_y, const SignPair steps) //Gets the desired direction from where it wants to ray cast
{
  CardinalDirection direction;

  if (ray_y == read_y)
  {
    std::cout << "No I got executed" << std::endl;
    direction = DesiredDirectionDiagonal(steps);
  }
  else
  {
    std::cout << "I got executed" << std::endl;
    bool horizontal = Horizontal(read_y, ray_y, steps.second);
    direction = DesiredDirectionHorizontal(horizontal, steps);
  }

  return direction;
}



CardinalDirection DesiredDirectionDiagonal(const SignPair steps) //Based off of where it is facing how will it increment
{
  CardinalDirection direction;

  if (Positive == steps.first)
  {
    if (Positive == steps.second) 
    {
      direction = NorthEast;
    }
    else if (Negative == steps.second)
    {
      direction = SouthEast;
    }
  }
  else if (Negative == steps.first)
  {
    if (Positive == steps.second)
    {
      direction = NorthWest;
    }
    else if (Negative == steps.second)
    {
      direction = SouthWest;
    }
  }
  
  return direction;
}


CardinalDirection DesiredDirectionHorizontal(const bool horizontal, const SignPair steps) //Same as diagonal except horizontal
{
  CardinalDirection direction;

  if (horizontal)
  {
    if (steps.first == Negative)
    {
      direction = West;
    }
    else if (steps.first == Positive)
    {
      direction = East;
    }
    else
    {
      throw;
    }
  }
  else
  {
    if (steps.second == Negative)
    {
      direction = South;
    }
    else if (steps.second == Positive)
    {
      direction = North;
    }
    else
    {
      throw;
    }
  }

  return direction;
}



CardinalDirection DesiredDirectionVertical(const SignPair steps) //Same but with vertical
{
  CardinalDirection direction; 

  if (Positive == steps.second)
  {
    direction = North;
  }
  else if (Negative == steps.second)
  {
    direction = South;
  }

  return direction;
}




std::pair<EdgeType, bool> DesiredEdge(const VertexType vertex, const CardinalDirection desired_direction, const OccupancyGridMap& map)
{ //Returns the desired edge of the pair and tells it where it should be facing for the proper edge
  std::pair<EdgeType, bool> desired_edge;

  const auto available_edges = boost::out_edges(vertex, map.get_map());

  for (auto iter = available_edges.first; iter != available_edges.second; iter++)
  {
    // CardinalDirection edge_direction = boost::get(CardinalDirection, map.get_map(), *iter);
    CardinalDirection edge_direction = map.get_map()[*iter];

    if (edge_direction == desired_direction)
    {
      desired_edge.first = *iter;
      desired_edge.second = true;
    }
  }

  return desired_edge;
}



bool HasEdges(const VertexType vertex, const OccupancyGridMap& map) //Checking if the vertex has edges, useful for determining the path and the ability for the robot to move, raycast, etc.
{
  bool has_edges = true;

  const auto edge_range = boost::out_edges(vertex, map.get_map());

  if (edge_range.first == edge_range.second)
  {
    has_edges = false;
  }

  return has_edges;
}

