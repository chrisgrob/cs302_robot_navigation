#pragma once

#include <iostream>
#include "project_utils.h"

class OccupancyGridMap
{
private:
  MapType map_;
  const IndexType map_size_;

public:
  OccupancyGridMap();
  OccupancyGridMap(const IndexType map_size, const Obstacle obstacle);
  OccupancyGridMap(const OccupancyGridMap& other);


  void set_map(const MapType map);
  const MapType& get_map() const;

  IndexType get_map_size() const;


  VertexType Vertex(const CoordinateType coordinate) const;

  CoordinateType Coordinate(const VertexType vertex) const;


  bool IsInBounds(const CoordinateType coordinate) const;


  void AddToVertex(const VertexType vertex, const double number);


  void Visualize() const;
  friend std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map);

private:
  void Visualize(std::ostream& os) const;

  bool VertexIsObstacle(const VertexType vertex, const Obstacle obstacle);
  bool VertexIsTop(const VertexType vertex);
  bool VertexIsBottom(const VertexType vertex);
  bool VertexIsLeftEdge(const VertexType vertex);
  bool VertexIsRightEdge(const VertexType vertex);

  void Connection(const VertexType vertex, const CoordinateType coordinate_change);
};
