#pragma once

#include <iostream>

enum class CardinalDirection //Enum for what direction the robot is facing, can only face 8 directions
{ //Depending on the number that it is the direction can later be used for the direction of the robot and the raycast
  North,
  East,
  South,
  West,
  NorthEast,
  SouthEast,
  SouthWest,
  NorthWest,
};

std::ostream& operator<<(std::ostream& os, const CardinalDirection cardinal_direction);
