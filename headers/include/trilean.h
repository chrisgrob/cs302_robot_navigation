#pragma once

enum class Trilean // Like a boolean except an identify whether or not the value is not known
  // defined because it was useful for a function to return a value of one of three states
{
  False = 0,
  True = 1,
  Unknown = 2,
};
