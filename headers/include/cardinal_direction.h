#pragma once

enum CardinalDirection //Enum for what direction the robot is facing, can only face 8 directions
{ //Depending on the number that it is the direction can later be used for the direction of the robot and the raycast
  North = 0,
  East = 1,
  South = 2,
  West = 3,
  NorthEast = 4,
  SouthEast = 5,
  SouthWest = 6,
  NorthWest = 7,
};

CardinalDirection FromNumber(const int num);
