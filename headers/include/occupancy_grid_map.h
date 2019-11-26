#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/properties.hpp"
#include "boost/property_map/property_map.hpp"
#include "boost/graph/named_function_params.hpp"

struct BinaryRV
{
  BinaryRV();

  float prob_taken;
  float prob_empty;
};

struct EdgeData
{
  // Nothing?
};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
  boost::undirectedS,
  BinaryRV,
  boost::property<boost::edge_weight_t, float>
> MapType;

struct Obstacle
{
  Obstacle(const size_t obsXMin, const size_t obsXMax, const size_t obsYMin, const size_t obsYMax);

  size_t x_min;
  size_t x_max;
  size_t y_min;
  size_t y_max;
};

class OccupancyGridMap
{
public:
  OccupancyGridMap();
  OccupancyGridMap(const Obstacle obstacle);
  OccupancyGridMap(const OccupancyGridMap& other);

  size_t VertexCount() const;
  size_t EdgeCount() const;

  size_t Index(const size_t x_pos, const size_t y_pos) const;
  std::pair<size_t, size_t> Coordinate(const size_t index) const;
  MapType::vertex_descriptor VertexDescriptor(const size_t index) const;

  bool IsInBounds(const size_t x_pos, const size_t y_pos) const;

  void UpdateMap(const size_t x_pos, const size_t y_pos);

  void Visualize() const;
  friend std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map);

private:
  MapType map;
  const size_t map_size;

  void Visualize(std::ostream& os) const;
};

bool PointIsObstacle(const size_t index, const Obstacle obstacle, const size_t map_size);
bool PointIsBottom(const size_t index, const size_t map_size);
bool PointIsLeftEdge(const size_t index, const size_t map_size);
bool PointIsRightEdge(const size_t index, const size_t map_size);
bool AttemptConnection(const size_t this_index, const size_t other_index, const Obstacle obstacle, MapType& map)