#include "robot_utils.h"

unsigned int Quartile(const int degrees)
{
  unsigned int quartile;

  if (degrees >= 0 && direction < 90)
  {
    quartile = 0;
  }
  else if (degrees >= 90 && degrees < 180)
  {
    quartile = 1;
  }
  else if (degrees >= 180 && degrees < 270)
  {
    quartile = 2;
  }
  else if (degrees >= 270 && degrees < 360)
  {
    quartile = 3;
  }
  else
  {
    throw;
  }

  return quartile;
}



SignPair Steps(const unsigned int quartile)
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

    if (HasEdges(desired_vertex.first))
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



CardinalDirection DesiredDirection(const int read_y, const double ray_y, const SignPair steps)
{
  CardinalDirection direction;

  if (ray_y == read_y)
  {
    direction = DesiredDirectionDiagonal(steps);
  }
  else
  {
    horizontal = Horizontal(read_y, ray_y, steps.second);
    direction = DesiredDirectionHorizontal(horizontal, steps);
  }

  return direction;
}



CardinalDirection DesiredDirectionDiagonal(const SignPair steps)
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
}


CardinalDirection DesiredDirectionHorizontal(const bool horizontal, const SignPair steps)
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



CardinalDirection DesiredDirectionVertical(const SignPair steps)
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
{
  std::pair<EdgeType, bool> desired_edge;

  const EdgeRange available_edges = boost::out_edges(vertex, map.get_map());

  for (EdgeIterator iter = available_edges.first; iter != available_edges.second; iter++)
  {
    CardinalDirection edge_direction = boost::get(CardinalDirection, map.get_map(), *iter);

    if (edge_direction == desired_direction)
    {
      desired_edge.first = *iter;
      desired_edge.second = true;
    }
  }

  return desired_edge;
}



bool HasEdges(const VertexType vertex)
{
  bool has_edges = true;

  const auto edge_range = boost::out(vertex);

  if (edge_range.first == edge_range.second)
  {
    has_edges = false;
  }

  return has_edges;
}

