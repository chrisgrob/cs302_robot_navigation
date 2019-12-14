#pragma once

#include <iostream>

namespace CardinalDirection
{
enum CardinalDirectionType //Enum for what direction the robot is facing, can only face 8 directions
{ //Depending on the number that it is the direction can later be used for the direction of the robot and the raycast{
  North,
  East,
  South,
  West,
  NorthEast,
  SouthEast,
  SouthWest,
  NorthWest,
};
}

using CardinalDirection::CardinalDirectionType;

std::ostream& operator<<(std::ostream& os, const CardinalDirectionType cardinal_direction);
