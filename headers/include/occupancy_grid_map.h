#pragma once

#include <iostream>
#include "project_utils.h"
#include "occupancy_grid_map_utils.h"

class OccupancyGridMap
{
private:
  MapType map_;
  const int map_size_;

public:
  OccupancyGridMap();
  OccupancyGridMap(const Obstacle obstacle);
  OccupancyGridMap(const OccupancyGridMap& other);


  int VertexCount() const;
  int EdgeCount() const;


  void set_map(const MapType map);
  const MapType& get_map() const;

  int get_map_size() const;


  VertexType Vertex(const CoordinateType pos) const;

  CoordinateType Coordinate(const VertexType vertex) const;


  bool IsInBounds(const int x_pos, const int y_pos) const;


  void UpdateMap(const int x_pos, const int y_pos);


  void Visualize() const;
  friend std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map);

private:
  void Visualize(std::ostream& os) const;

};
