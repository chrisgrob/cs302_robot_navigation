#include "cardinal_direction.h"

CardinalDirection fromNumber(const int num) {
  if (num == North) {
    return North;
  }
  else if (num == East) {
    return East;
  }
  else if (num == South) {
    return South;
  }
  else if (num == West) {
    return West;
  }
  else {
    throw;
  }
}
