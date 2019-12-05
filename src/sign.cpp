#include "sign.h"

int operator+(const Sign sign, const int number)
{
  int sum;

  switch (sign)
  {
  case Sign::Positive:
  {
    sum = number + 1;
    break;
  }
  case Sign::Negative:
  {
    sum = number - 1;
  }
  default:
    throw;
  }

  return sum;
}

int operator+(const int number, const Sign sign)
{
  return operator+(sign, number);
}

double operator+(const Sign sign, const double number)
{
  double sum;

  switch (sign)
  {
  case Sign::Positive:
  {
    sum = number + 1.0;
    break;
  }
  case Sign::Negative:
  {
    sum = number - 1.0;
  }
  default:
    throw;
  }

  return sum;
}

double operator+(const double number, const Sign sign)
{
  return operator+(sign, number);
}

int operator*(const Sign sign, const int number)
{
  int product;

  switch (sign)
  {
  case Sign::Positive:
  {
    product = number;
    break;
  }
  case Sign::Negative:
  {
    product = -1 * number;
  }
  default:
    throw;
  }

  return product;
}

int operator*(const int number, const Sign sign)
{
  return operator+(sign, number);
}

double operator*(const Sign sign, const double number)
{
  double product;

  switch (sign)
  {
  case Sign::Positive:
  {
    product = number;
    break;
  }
  case Sign::Negative:
  {
    product = -1.0 * number;
  }
  default:
    throw;
  }

  return product;
}

double operator*(const double number, const Sign sign)
{
  return operator(sign, number);
}
