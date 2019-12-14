#include "cardinal_direction.h"

std::ostream& operator<<(std::ostream& os, const CardinalDirection cardinal_direction)
{
  os << "CardinalDirection::";

  switch (cardinal_direction)
  {
  case CardinalDirection::North:
  {
    os << "North";
    break;
  }
  case CardinalDirection::East:
  {
    os << "East";
    break;
  }
  case CardinalDirection::South:
  {
    os << "South";
    break;
  }
  case CardinalDirection::West:
  {
    os << "West";
    break;
  }
  case CardinalDirection::NorthEast:
  {
    os << "NorthEast";
    break;
  }
  case CardinalDirection::SouthEast:
  {
    os << "SouthEast";
    break;
  }
  case CardinalDirection::SouthWest:
  {
    os << "SouthWest";
    break;
  }
  case CardinalDirection::NorthWest:
  {
    os << "NorthWest";
    break;
  }
  default:
    throw;
  }

  return os;
}
