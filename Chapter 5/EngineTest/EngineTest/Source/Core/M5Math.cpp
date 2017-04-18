/******************************************************************************/
/*!
file     M5Math.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class: GAM 150
\par    Assignment: Simple 2D Game Engine
\date   2012/11/29

This file contains math functions that are useful in a game.
*/
/******************************************************************************/
#include "M5Math.h"
#include "M5Debug.h"
#include <cmath>
#include <cstring> /*memcpy*/

namespace M5Math
{
/******************************************************************************/
/*!
Converts an angle in degrees to an angle in radians.

\param degrees
An angle in degrees.

\return
An angle in radians
*/
/******************************************************************************/
float DegreeToRadian(float degrees)
{
  return (PI / 180.f) * degrees;
}
/******************************************************************************/
/*!
Converts an angle in radians to an angle in degrees.

\param radians
An angle in radians

\return
An angle in degrees.
*/
/******************************************************************************/
float RadianToDegree(float radians)
{
  return (180.f / PI) * radians;
}
/******************************************************************************/
/*!
If x is smaller than low, x equals low. If x is larger than high, x equals
high. Otherwise x is unchanged.

\param x
The value to clamp.

\param low
The lowest possible value to clamp to.

\param high
The highest possible value to clamp to.

\return
A number between low and high (inclusive).
*/
/******************************************************************************/
float Clamp(float x, float low, float high)
{
  if (x < low)
    x = low;
  else if (x > high)
    x = high;

  return x;
}
/******************************************************************************/
/*!
If x is lower than low, x is set to high. If x is higher than high, x is
set to low.  Otherwise x is unchanged.

\param x
The value to wrap.

\param low
The lowest possible value to wrap.

\param high
The highest possible value to wrap.

\return
A number between low and high (inclusive).
*/
/******************************************************************************/
float Wrap(float x, float low, float high)
{
  if (x < low)
    x = high;
  else if (x > high)
    x = low;

  return x;
}
/******************************************************************************/
/*!
Returns the smaller value of x and y;

\param x
The first value to check.

\param y
The second value to check.

\return
The smaller value of x and y.
*/
/******************************************************************************/
float Min(float x, float y)
{
  return (x < y) ? x : y;
}
/******************************************************************************/
/*!
Returns the larger value of x and y;

\param x
The first value to check.

\param y
The second value to check.

\return
The larger value of x and y.
*/
/******************************************************************************/
float Max(float x, float y)
{
  return (x > y) ? x : y;
}
/******************************************************************************/
/*!
Returns true if x is in the range of low and high (inclusive).

\param x
The number to check.

\param low
The lowest number in the range.

\param high
The highest number in the range.

\return
True if x is in the range, false otherwise.
*/
/******************************************************************************/
bool IsInRange(float x, float low, float high)
{
  bool xEqualsLow  = IsFloatEqual(x, low);
  bool xEqualsHigh = IsFloatEqual(x, high);

  return ((x > low || xEqualsLow) && (x < high || xEqualsHigh));
}
/******************************************************************************/
/*!
Tests if two variables are equal within an EPSILON value.

\param x
The first number to check.

\param y
The second number to check.

\return
True if the values are equal within M5_MATH_EPSILON, false otherwise.
*/
/******************************************************************************/
bool IsFloatEqual(float x, float y)
{
  return (std::abs(x - y) < EPSILON);
}
/******************************************************************************/
/*!
Test if a given integer is a power of two or not. This only works for positive
non zero numbers.

\param x
The number to check.

\return
True if the number is a power of two.  False otherwise.
*/
/******************************************************************************/
bool IsPowerOf2(int x)
{
  /*make sure it is a positive number
  Then, since a power of two only has one bit turned on, if we subtract 1 and
  then and them together no bits should be turned on.*/
  return ((x > 0) && !(x & (x - 1)));
}
/******************************************************************************/
/*!
Given a number x.  This function will return the next largest power of two.

\param x
The number to get the next largest power of two.

\return
The next largest power of two.
*/
/******************************************************************************/
int GetNextPowerOf2(int x)
{
  /*Turn on all of the bits lower than the highest on bit.  Then add one.  It
  will be a power of two.*/
  /*--x;*/
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  ++x;
  return x;
}
/******************************************************************************/
/*!
The linear interpolation of start to end based on the input time.

\param start
the value to start on

\param end
The ending value

\param time
An interpolation time.  0 will give start and 1 will give end.

\return
The interpolated value.
*/
/******************************************************************************/
int Lerp(int start, int end, float time)
{
  int diff = end - start;
  return static_cast<int>(start + diff * time);
}
/******************************************************************************/
/*!
The linear interpolation of start to end based on the input time.

\param start
the value to start on

\param end
The ending value

\param time
An interpolation time.  0 will give start and 1 will give end.

\return
The interpolated value.
*/
/******************************************************************************/
char  Lerp(char start, char end, float time)
{
  char diff = end - start;
  return static_cast<char>(start + diff * time);
}
/******************************************************************************/
/*!
The linear interpolation of start to end based on the input time.

\param start
the value to start on

\param end
The ending value

\param time
An interpolation time.  0 will give start and 1 will give end.

\return
The interpolated value.
*/
/******************************************************************************/
float Lerp(float start, float end, float time)
{
  float diff = end - start;
  return start + diff * time;
}
}//end namespace M5Math



