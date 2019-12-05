#include "project_utils.h"


// Simple parameterized c-tor
Obstacle::Obstacle(const int x_min_p, const int x_max_p, const int y_min_p, const int y_max_p)
  : x_min(x_min_p), x_max(x_max_p), y_min(y_min_p), y_max(y_max_p)
{ //Sets an obstacle based off of a minimum and maximum x and y range
}

int Localize(const int direction) //Makes the direction always equal to a value between 0-360
{
  int new_direction = direction; 

  while (new_direction >= 360) //Check if the direction is over 360
  {
    new_direction -= 360; //Subtract it by 360
  }

  while (new_direction < 0) //Check if the direction is less than 360
  {
    new_direction += 360; //Add it by 360
  }

  return new_direction; //returns the correct direction
}



double ToRadians(const int degrees) //Conversion to make the degree be equal to radians
{
  return (double)degrees * pi / 180.0; // degrees*π/180 = radians
}



double VectorMagnitude(const DoubleCoordinateType vector)
{
  return sqrt(pow(vector.first, 2.0) + pow(vector.second, 2.0)); //Returns the magnitude of the vector --> sqrt/x^2+y^2 = |v|
}



double Slope(const int degrees) //returns the slope considering the degree angle of it
{
  const double radians = ToRadians(degrees);

  return tan(radians); //tan(Θ) = slope of the vector
}
