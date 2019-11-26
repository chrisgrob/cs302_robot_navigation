#pragma once

enum CardinalDirection
{
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
