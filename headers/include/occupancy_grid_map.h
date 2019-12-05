#pragma once

#include <iostream>
#include <iomanip>
#include "project_utils.h"

class OccupancyGridMap
{
private:
  MapType map_; // map of type MapType
  IndexType map_size_; // size of the map(dynamic), should be set to 10000 for project

public:
  OccupancyGridMap();
  OccupancyGridMap(const IndexType map_size, const Obstacle obstacle);
  OccupancyGridMap(const OccupancyGridMap& other);


  // setters and getters for map
  void set_map(const MapType map);
  const MapType& get_map() const;

  // getter for map size
  IndexType get_map_size() const;

  // Translates coordinate position into a vertex
  VertexType Vertex(const CoordinateType coordinate) const;

  CoordinateType Coordinate(const VertexType vertex) const; //Returns a coordinate based off of a vertex


  // Checks to see if the position is in bounds
  bool IsInBounds(const CoordinateType coordinate) const;

  // Add a number to a vertex's logodd, can be positive/negative
  void AddToVertex(const VertexType vertex, const double number);


  void VisualizeObstacles() const;
  friend std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map); //Outputs the map when using os << map

private:
  void Visualize(std::ostream& os) const; //Visualize the map 

  bool VertexIsObstacle(const VertexType vertex, const Obstacle obstacle);
  bool VertexIsTop(const VertexType vertex);
  bool VertexIsBottom(const VertexType vertex);
  bool VertexIsLeftEdge(const VertexType vertex);
  bool VertexIsRightEdge(const VertexType vertex);

  void Connection(const VertexType vertex, const CoordinateType coordinate_change, const CardinalDirection direction);
};
