#pragma once

#include "project_utils.h"

bool VertexIsObstacle(const VertexType vertex, const Obstacle obstacle, const int map_size);
bool VertexIsTop(const VertexType vertex, const int map_size);
bool VertexIsBottom(const VertexType vertex, const int map_size);
bool VertexIsLeftEdge(const VertexType vertex, const int map_size);
bool VertexIsRightEdge(const VertexType vertex, const int map_size);