#include "sign.h"

std::ostream& operator<<(std::ostream& os, const SignType sign)
{
  os << "Sign::";

  switch (sign)
  {
  case Sign::Positive:
  {
    os << "Positive";
    break;
  }
  case Sign::Negative:
  {
    os << "Negative";
    break;
  }
  default:
    throw;
  }

  return os;
}

int operator+(const SignType sign, const int number)
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
    break;
  }
  default:
    throw;
  }

  return sum;
}

int operator+(const int number, const SignType sign)
{
  return operator+(sign, number);
}

double operator+(const SignType sign, const double number)
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
    break;
  }
  default:
    throw;
  }

  return sum;
}

double operator+(const double number, const SignType sign)
{
  return operator+(sign, number);
}

int operator*(const SignType sign, const int number)
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
    break;
  }
  default:
    throw;
  }

  return product;
}

int operator*(const int number, const SignType sign)
{
  return operator*(sign, number);
}

double operator*(const SignType sign, const double number)
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
    break;
  }
  default:
    throw;
  }

  return product;
}

double operator*(const double number, const SignType sign)
{
  return operator*(sign, number);
}
