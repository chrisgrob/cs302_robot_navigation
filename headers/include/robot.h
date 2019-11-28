#pragma once

#include "project_utils.h"
#include "occupancy_grid_map.h"
#include "robot_utils.h"

const double pi = 3.14159265358979323846;

class Robot
{
private:
  CardinalDirection orientation_;
  CoordinateType pos_;
  OccupancyGridMap map_;

public:
  Robot();
  Robot(const CoordinateType pos, const CardinalDirection orientation, const OccupancyGridMap map);


  void set_pos(const CoordinateType pos);
  CoordinateType get_pos() const;

  void set_orientation(const CardinalDirection orientation);
  CardinalDirection get_orientation() const;

  void set_map(const OccupancyGridMap map);
  const OccupancyGridMap& get_map() const;
  

  void RayCasting();

private:
  void RayRange(const int start, const int end);
  void Ray(const int direction);
  void Cast(const SignPair steps, const int direction);
  void CastVertical(const SignPair steps);
  void CastDiagonal(const unsigned int quartile);

  void UpdateMap(VertexType vertex, double sensor_reading);

};
