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

typedef boost::adjacency_list<boost::vecS, boost::vecS,
  boost::directedS,
  double,
  CardinalDirection
> MapType; //Creates an adjacency list using a series of RVs to determine whether the give spot is empty or not


//Typedefs for different edges and vertices of the map
typedef MapType::vertex_descriptor VertexType;
typedef MapType::edge_descriptor EdgeType;

typedef MapType::vertex_iterator VertexIterator;
typedef MapType::edge_iterator EdgeIterator;

typedef std::pair<VertexIterator, VertexIterator> VertexRange;
typedef std::pair<EdgeIterator, EdgeIterator> EdgeRange;

typedef int IndexType;


const double pi = 3.14159265358979323846; //value of pi


struct Obstacle //Creates an obstacle based off the min and max x positiona nd the min and max y position
{
  Obstacle(const int x_min_p, const int x_max_p, const int y_min_p, const int y_max_p);

  int x_min;
  int x_max;
  int y_min;
  int y_max;
};

typedef std::pair<int, int> CoordinateType; //Creates the coordinate type
typedef std::pair<double, double> DoubleCoordinateType; //Same as the other, except with doubles
typedef std::pair<Sign, Sign> SignPair; //Creates a sign pair

int Localize(const int direction); //Localizes the direction to be within 0-360
float ToRadians(const int degrees); //Changes degrees to radians
float VectorMagnitude(const FloatCoordinateType vector); //Returns the magnitude of the vector
double Slope(const int degrees); //Determines the slop of the vector given the degrees
