#pragma once

#include "cardinal_direction.h"
#include "occupancy_grid_map.h"
#include "sign.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

const double pi = 3.14159265358979323846;

class Robot
{
private:
  CardinalDirection orientation_;
  size_t x_pos_;
  size_t y_pos_;
  OccupancyGridMap map_;

public:
  Robot();
  Robot(const size_t x_pos, const size_t y_pos, const CardinalDirection orientation, const OccupancyGridMap map);


  void RayCasting();


  void set_x(const size_t x_pos);
  size_t get_x() const;

  void set_y(const size_t y_pos);
  size_t get_y() const;

  void set_orientation(const CardinalDirection orientation);
  size_t get_orientation() const;

private:
  void RayRange(const int start, const int end);
  void Ray(const int direction);

};

int Localize(const int direction);
float ToRadians(const int degrees);
float VectorMagnitude(const float x, const float y);
