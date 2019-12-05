#include "robot.h"

// Expects angle to be between 0-360 degrees, call localize on
// your angle first
unsigned int Robot::Quartile(const int degrees) //Checks which quartile the degree is in
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



SignPair Robot::Steps(const unsigned int quartile) //Makes the first and second value equal to whether or not it is positive or negative as a result of the quartile
{
  SignPair steps;

  if (quartile == 0)
  {
    steps.first = Sign::Positive;
    steps.second = Sign::Negative;
  }
  else if (quartile == 1)
  {
    steps.first = Sign::Negative;
    steps.second = Sign::Negative;
  }
  else if (quartile == 2)
  {
    steps.first = Sign::Negative;
    steps.second = Sign::Positive;
  }
  else if (quartile == 3)
  {
    steps.first = Sign::Positive;
    steps.second = Sign::Positive;
  }
  else
  {
    throw;
  }

  return steps;
}



bool Robot::Horizontal(const int read_y, const float ray_y, const Sign step_y)
{
  bool horizontal = false;

  const int proposed_y = read_y + step_y;

  if (Sign::Positive == step_y)
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
  else if (Sign::Negative == step_y)
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



std::pair<VertexType, Trilean> Robot::DesiredVertex(
  const CoordinateType read_pos, 
  const FloatCoordinateType ray_pos,
  const SignPair steps)
{
  std::pair<VertexType, Trilean> desired_vertex;

  const VertexType this_vertex = map_.Vertex(read_pos);

  const CardinalDirection desired_direction = DesiredDirection(read_pos.second, ray_pos.second, steps);
  const std::pair<EdgeType, bool> desired_edge = DesiredEdge(this_vertex, desired_direction);

  desired_vertex = DesiredVertexHelper(desired_edge);

  return desired_vertex;
}



std::pair<VertexType, Trilean> Robot::DesiredVertexHelper(const std::pair<EdgeType, bool> desired_edge)
{
  std::pair<VertexType, Trilean> desired_vertex;

  if (desired_edge.second)
  {
    desired_vertex.first = boost::target(desired_edge.first, map_.get_map());

    if (HasEdges(desired_vertex.first))
    {
      desired_vertex.second = Trilean::True;
    }
    else
    {
      desired_vertex.second = Trilean::False;
    }
  }
  else
  {
    desired_vertex.second = Trilean::Unknown;
  }

  return desired_vertex;
}



CardinalDirection Robot::DesiredDirection(const int read_y, const double ray_y, const SignPair steps) //Gets the desired direction from where it wants to ray cast
{
  CardinalDirection direction;

  if (ray_y != pos_.second && ray_y == read_y)
  {
    direction = DesiredDirectionDiagonal(steps);
  }
  else
  {
    bool horizontal = Horizontal(read_y, ray_y, steps.second);
    direction = DesiredDirectionHorizontal(horizontal, steps);
  }

  return direction;
}



CardinalDirection Robot::DesiredDirectionDiagonal(const SignPair steps) //Based off of where it is facing how will it increment
{
  CardinalDirection direction;

  if (Sign::Positive == steps.first)
  {
    if (Sign::Positive == steps.second) 
    {
      direction = CardinalDirection::NorthEast;
    }
    else if (Sign::Negative == steps.second)
    {
      direction = CardinalDirection::SouthEast;
    }
  }
  else if (Sign::Negative == steps.first)
  {
    if (Sign::Positive == steps.second)
    {
      direction = CardinalDirection::NorthWest;
    }
    else if (Sign::Negative == steps.second)
    {
      direction = CardinalDirection::SouthWest;
    }
  }
  
  return direction;
}


CardinalDirection Robot::DesiredDirectionHorizontal(const bool horizontal, const SignPair steps) //Same as diagonal except horizontal
{
  CardinalDirection direction;

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
      direction = CardinalDirection::South;
    }
    else if (Sign::Positive == steps.second)
    {
      direction = CardinalDirection::North;
    }
    else
    {
      throw;
    }
  }

  return direction;
}



CardinalDirection Robot::DesiredDirectionVertical(const SignPair steps) //Same but with vertical
{
  CardinalDirection direction; 

  if (Sign::Positive == steps.second)
  {
    direction = CardinalDirection::North;
  }
  else if (Sign::Negative == steps.second)
  {
    direction = CardinalDirection::South;
  }

  return direction;
}




std::pair<EdgeType, bool> Robot::DesiredEdge(const VertexType vertex, const CardinalDirection desired_direction)
{ //Returns the desired edge of the pair and tells it where it should be facing for the proper edge
  std::pair<EdgeType, bool> desired_edge;

  const auto available_edges = boost::out_edges(vertex, map_.get_map());

  for (auto iter = available_edges.first; iter != available_edges.second; iter++)
  {
    // CardinalDirection edge_direction = boost::get(CardinalDirection, map.get_map(), *iter);
    CardinalDirection edge_direction = map_.get_map()[*iter];

    if (edge_direction == desired_direction)
    {
      desired_edge.first = *iter;
      desired_edge.second = true;
    }
  }

  return desired_edge;
}



bool Robot::HasEdges(const VertexType vertex) //Checking if the vertex has edges, useful for determining the path and the ability for the robot to move, raycast, etc.
{
  bool has_edges = true;

  const auto edge_range = boost::out_edges(vertex, map_.get_map());

  if (edge_range.first == edge_range.second)
  {
    has_edges = false;
  }

  return has_edges;
}

