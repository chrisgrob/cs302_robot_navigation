#include "project_utils.h"

// Initial probabilities are 50/50
BinaryRV::BinaryRV() : prob_taken(0.5), prob_empty(0.5) {}


// Simple parameterized c-tor
Obstacle::Obstacle(const int x_min_p, const int x_max_p, const int y_min_p, const int y_max_p)
  : x_min(x_min_p), x_max(x_max_p), y_min(y_min_p), y_max(y_max_p)
{
}

int Localize(const int direction)
{
  int new_direction = direction;

  while (new_direction >= 360)
  {
    new_direction -= 360;
  }

  while (new_direction < 0)
  {
    new_direction += 360;
  }

  return new_direction;
}



float ToRadians(const int degrees)
{
  return (float)degrees * pi / 180.0f;
}



float VectorMagnitude(const FloatCoordinateType vector)
{
  return sqrt(pow(vector.first, 2.0) + pow(vector.second, 2.0));
}



double Slope(const int degrees)
{
  const double radians = ToRadians(degrees);

  return tan(radians);
}