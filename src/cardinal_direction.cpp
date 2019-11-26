#include "cardinal_direction.h"

CardinalDirection FromNumber(const int num)
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
