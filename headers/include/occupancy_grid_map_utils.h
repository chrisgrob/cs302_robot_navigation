#pragma once

#include "project_utils.h"

bool VertexIsObstacle(const VertexType vertex, const Obstacle obstacle, const int map_size); //Checks if the vertex is an obstacle
bool VertexIsTop(const VertexType vertex, const int map_size); //Checks if the vertex is at the top of the map
bool VertexIsBottom(const VertexType vertex, const int map_size); //Checks if vertex is at the bottom of the map
bool VertexIsLeftEdge(const VertexType vertex, const int map_size); //Checks if vertex is at the left edge of the map
bool VertexIsRightEdge(const VertexType vertex, const int map_size); //Cehcks if vertex is at the right edge of the map
