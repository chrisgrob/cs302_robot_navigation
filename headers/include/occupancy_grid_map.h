#pragma once

#include <iostream>
#include "project_utils.h"
#include "occupancy_grid_map_utils.h"

class OccupancyGridMap
{
private:
  MapType map_; //Generates a type map
  const int map_size_;  //Size of the map, by default should be 10000

public:
  OccupancyGridMap();
  OccupancyGridMap(const Obstacle obstacle);
  OccupancyGridMap(const OccupancyGridMap& other);


  int VertexCount() const; //Gets the vertex count for the total Map
  int EdgeCount() const; //Edge count for the map


  void set_map(const MapType map); //Sets the map to be equal to the other map
  const MapType& get_map() const;//Gets the map

  int get_map_size() const; //returns map size


  VertexType Vertex(const CoordinateType pos) const;//Returns a vertex based off of the coordinate position

  CoordinateType Coordinate(const VertexType vertex) const; //Returns a coordinate based off of a vertex


  bool IsInBounds(const int x_pos, const int y_pos) const; //Checks to see if the position is in bounds


  void UpdateMap(const int x_pos, const int y_pos); //Updates map based off of the x and y position


  void Visualize() const;
  friend std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map); //Outputs the map when using os << map

private:
  void Visualize(std::ostream& os) const; //Visualize the map 

};
