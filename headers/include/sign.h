#pragma once

#include <iostream>

namespace Sign
{
enum SignType { //Simple enum to help determine if the number is positive or negative, based off of previous quadrants on the map
  Positive,
  Negative,
};
}

using Sign::SignType;

std::ostream& operator<<(std::ostream& os, const SignType sign);

int operator+(const SignType sign, const int number);
int operator+(const int number, const SignType sign);
double operator+(const SignType sign, const double number);
double operator+(const double number, const SignType sign);
int operator*(const SignType sign, const int number);
int operator*(const int number, const SignType sign);
double operator*(const SignType sign, const double number);
double operator*(const double number, const SignType sign);
