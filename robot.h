#pragma once
#ifndef ROBOT_H
#define ROBOT_H
#include "cardinal_direction.h"
#include "PhysicalMap.h"
#include "sign.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

const double pi = 3.14159265358979323846;

class Robot {
  private:
    CardinalDirection orientation_;
    int x_pos_;
    int y_pos_;
    PhysicalMap map_;
  public:
    Robot();

    Robot(const int x_pos, const int y_pos, const CardinalDirection orientation, const PhysicalMap map);
    
    void rayCasting();
    
    void setX(const int num) { x_pos_ = num;}
    void setY(const int num) { y_pos_ = num;}
    void setOrientation(const CardinalDirection orientation) { orientation_ = orientation; }
   
  private:
    void rayRange(const int start, const int end);
    void ray(const int direction);
};

int localize(const int direction);
float toRadians(const int degrees);
float vecMagnitude(const float x, const float y);

#endif //ROBOT_H
