#include "cardinal_direction.h"

CardinalDirection FromNumber(const int num) //Sets the direction depending on the number that was inserted into it
{
  if (num == North)
  {
    return North;
  }
  else if (num == East)
  {
    return East;
  }
  else if (num == South)
  {
    return South;
  }
  else if (num == West)
  {
    return West;
  }
  else if (num == NorthEast)
  {
    return NorthEast;
  }
  else if (num == SouthEast)
  {
    return SouthEast;
  }
  else if (num == SouthWest)
  {
    return SouthWest;
  }
  else if (num == NorthWest)
  {
    return NorthWest;
  }
  else
  {
    throw;
  }
}
