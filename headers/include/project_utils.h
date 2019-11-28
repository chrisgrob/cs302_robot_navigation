#pragma once

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/properties.hpp"
#include "boost/property_map/property_map.hpp"
#include "boost/graph/named_function_params.hpp"

#include <algorithm>
#include <cmath>

#include "sign.h"
#include "cardinal_direction.h"
#include "trilean.h"

struct BinaryRV
{
  BinaryRV();

  double prob_taken;
  double prob_empty;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
  boost::directedS,
  BinaryRV,
  CardinalDirection
> MapType;

typedef MapType::vertex_descriptor VertexType;
typedef MapType::edge_descriptor EdgeType;

typedef MapType::vertex_iterator VertexIterator;
typedef MapType::edge_iterator EdgeIterator;

typedef std::pair<VertexIterator, VertexIterator> VertexRange;
typedef std::pair<EdgeIterator, EdgeIterator> EdgeRange;


struct Obstacle
{
  Obstacle(const int x_min_p, const int x_max_p, const int y_min_p, const int y_max_p);

  int x_min;
  int x_max;
  int y_min;
  int y_max;
};

typedef std::pair<int, int> CoordinateType;
typedef std::pair<float, float> FloatCoordinateType;
typedef std::pair<Sign, Sign> SignPair;

int Localize(const int direction);
float ToRadians(const int degrees);
float VectorMagnitude(const FloatCoordinateType vector);
double Slope(const int degrees);
