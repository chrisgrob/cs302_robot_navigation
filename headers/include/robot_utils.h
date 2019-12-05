#pragma once

#include "project_utils.h"
#include "occupancy_grid_map.h"

unsigned int Quartile(const int degrees); //Returns an int for the quartile of wherever the vector is
SignPair Steps(const unsigned int quartile); //Returns the sign pair in relation to the quartile
bool Horizontal(const int read_y, const float ray_y, const Sign step_y); //Determines whether it can step horizontally or not
std::pair<VertexType, Trilean> DesiredVertex(
  const CoordinateType read_pos, 
  const FloatCoordinateType ray_pos, 
  const SignPair steps, 
  const OccupancyGridMap& map
); //The desired vertex for where on the map the ray casting is occurring
std::pair<VertexType, Trilean> DesiredVertexHelper(const std::pair<EdgeType, bool> desired_edge, const OccupancyGridMap& map);
CardinalDirection DesiredDirection(const int read_y, const double ray_y, const SignPair steps);
CardinalDirection DesiredDirectionDiagonal(const SignPair steps);
CardinalDirection DesiredDirectionHorizontal(const bool horizontal, const SignPair steps);
CardinalDirection DesiredDirectionVertical(const SignPair steps);
std::pair<EdgeType, bool> DesiredEdge(const VertexType vertex, const CardinalDirection desired_direction, const OccupancyGridMap& map);
bool HasEdges(const VertexType vertex, const OccupancyGridMap& map);
