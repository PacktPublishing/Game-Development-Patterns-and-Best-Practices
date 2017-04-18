/******************************************************************************/
/*!
file   M5Vec2.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Implementation of my Vec2 Functions
*/
/******************************************************************************/
#include "M5Vec2.h"
#include "M5Math.h"
#include "M5Debug.h"

#include <cmath> //sqrt, fabs
#include <cstring>//memcpy



/******************************************************************************/
/*!
Sets the values of the vector to the given values.

\param [in] xx
The value of x.

\param [in] yy
The value of y.
*/
/******************************************************************************/
M5Vec2::M5Vec2(float xx /*= 0*/, float yy /*= 0*/) :x(xx), y(yy) 
{
}
/******************************************************************************/
/*!
Sets the values of the vector to the given values.

\param result
The vector to set.

\param x
The x value to copy.

\param y
The y value to copy.
*/
/******************************************************************************/
void M5Vec2::Set(M5Vec2& result, float x, float y)
{
  result.x = x;
  result.y = y;
}
/******************************************************************************/
/*!
Negates (changes the sign of) of the x, y  of the M5Vec2. It is ok
to have both pointers be the same object.

\param result
To location to store the result in.

\param toNegate
The vector or point to Negate.
*/
/******************************************************************************/
void M5Vec2::Negate(M5Vec2& result, const M5Vec2& toNegate)
{
  result.x = toNegate.x * -1.f;
  result.y = toNegate.y * -1.f;
}
/******************************************************************************/
/*!
Function to quickly set the values of x and y.

\param xx
The x value to set.

\param yy
The y value to set.

\return none
*/
/******************************************************************************/
void M5Vec2::Set(float xx /*= 0.f*/, float yy /*= 0.f*/)
{
  x = xx;
  y = yy;
}
/******************************************************************************/
/*!
This Adds x, y of the two vectors together.

\param result
The resulting vector or point.

\param vec1
The first vector or point to add.

\param vec2
The second vector or point to add.
*/
/******************************************************************************/
void M5Vec2::Add(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2)
{
  result.x = vec1.x + vec2.x;
  result.y = vec1.y + vec2.y;
}
/******************************************************************************/
/*!
This subtracts x, y of the two vectors/points together. This will subtract
the second from the first:
result = first - second;

\param result
The location to store the result in.

\param vec1
The M5Vec2 to subtract from.

\param vec2
The M5Vec2 to subtract.
*/
/******************************************************************************/
void M5Vec2::Sub(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2)
{
  result.x = vec1.x - vec2.x;
  result.y = vec1.y - vec2.y;
}
/******************************************************************************/
/*!
This scales the x, y of a vector by a specified value.

\param result
The location to store the result in.

\param toScale
The M5Vec2 to scale.

\param scale
The value to scale by.
*/
/******************************************************************************/
void M5Vec2::Scale(M5Vec2& result, const M5Vec2& toScale, float scale)
{
  result.x = toScale.x * scale;
  result.y = toScale.y * scale;
}
/******************************************************************************/
/*!
Calculates the z value of the cross product between these two vectors.

\param vec1
The first M5Vec2 to cross.

\param vec2
The second M5Vec2 to cross.

\return
The z value of the cross product between the two vectors.
*/
/******************************************************************************/
float M5Vec2::CrossZ(const M5Vec2& vec1, const M5Vec2& vec2)
{
  return (vec1.x * vec2.y) - (vec2.x * vec1.y);
}
/******************************************************************************/
/*!
Normalized a vector.  It is safe if both vectors are the the same object.

\attention
This function will crash if you normalize the zero vector.

\param result
A pointer to a vector to store the result.

\param toNormalize
A vector to Normalize.

*/
/******************************************************************************/
void M5Vec2::Normalize(M5Vec2& result, const M5Vec2& toNormalize)
{
  result = toNormalize;
  result.Normalize();
}
/******************************************************************************/
/*!
Calculates the projection vector of vec1 onto vec2.

\param result
A pointer to a vector to store the result.


\param vec1
The vector you are projecting.

\param vec2
The vector you are projecting onto.
*/
/******************************************************************************/
void M5Vec2::Project(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2)
{
  /*Projection is (v.w)/(w.w)*w */

  float dotProduct = vec1.Dot(vec2);   /*Get the dot product*/
  float lengthSquared = vec2.Dot(vec2);/*Get the length squared*/

  M5DEBUG_ASSERT(!M5Math::IsFloatEqual(lengthSquared, 0.0f),
    "Trying to Project onto the zero vector");

  /*Scale the vector;*/
  result = vec2;
  result *= (dotProduct / lengthSquared);
}
/******************************************************************************/
/*!
Calculates the perpendicular projection vector of first onto second.

\attention
This vector plus Project(first, second), will result in first.

\param result
A pointer to a vector to store the result.

\param vec1
The vector you are projecting.

\param vec2
The vector you are projecting onto.
*/
/******************************************************************************/
void M5Vec2::PerpProject(M5Vec2&result, const M5Vec2&vec1, const M5Vec2&vec2)
{
  /*Perpendictual Projection is v -(v.w)/(w.w)*w */
  M5Vec2 projection;
  M5Vec2::Project(projection, vec1, vec2);
  M5Vec2::Sub(result, vec1, projection);
}
/******************************************************************************/
/*!
Calculates a linear interpolation between to vectors/points.

\param result
A pointer to a vector to store the result.

\param vec1
The first vector.  A time of 0 will give you this vector as a result.

\param vec2
The first vector.  A time of 1 will give you this vector as a result.

\param time
The interpolation time.  Doesn't have to be between 0 and 1.
*/
/******************************************************************************/
void M5Vec2::Lerp(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2, float time)
{
  M5Vec2 difference = vec2;

  difference -= vec1;
  result.x = vec1.x + difference.x * time;
  result.y = vec1.y + difference.y * time;
}
/******************************************************************************/
/*!
Calculates the Dot Product of two vectors.

\param vec1
A pointer to the first vector.

\param vec2
A pointer to the second vector.

\return
The Dot product of the two vectors.
*/
/******************************************************************************/
float M5Vec2::Dot(const M5Vec2& vec1, const M5Vec2& vec2)
{
  return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}
/******************************************************************************/
/*!
Returns the length of the vector.

\param vec
A pointer to the vector to check.

\return
The length of the vector.
*/
/******************************************************************************/
float M5Vec2::Length(const M5Vec2& vec)
{
  /*Use sqrt to get length*/
  return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}
/******************************************************************************/
/*!
Returns the length of the vector squared.

\param vec
A pointer to the vector to check.

\return
The length of the vector squared.
*/
/******************************************************************************/
float M5Vec2::LengthSquared(const M5Vec2& vec)
{
  /*Do dot product with itself to get length squared.*/
  return vec.x*vec.x + vec.y*vec.y;
}
/******************************************************************************/
/*!
Returns the distance between two points.

\attention
The function is meant to be used with points, not vectors.

\param vec1
A pointer to the first point.

\param vec2
A pointer to the second point.

\return
The distance between to points.
*/
/******************************************************************************/
float M5Vec2::Distance(const M5Vec2& vec1, const M5Vec2& vec2)
{
  /*Get the Square root of the squared version.*/
  return std::sqrt(vec1.DistanceSquared(vec2));
}
/******************************************************************************/
/*!
Returns the squared distance between two points.

\attention
The function is meant to be used with points, not vectors.

\param vec1
A pointer to the first point.

\param vec2
A pointer to the second point.

\return
The squared distance between to points.
*/
/******************************************************************************/
float M5Vec2::DistanceSquared(const M5Vec2& vec1, const M5Vec2& vec2)
{
  M5Vec2 diff = vec2;
  /*Get the vector between them*/
  diff -= vec1;
  /*Get the length of that vector squared*/
  return diff.x*diff.x + diff.y*diff.y;
}
/******************************************************************************/
/*!
Tests if two M5Vec2 are equal.

\param vec1
The first M5Vec2 to test.

\param vec2
The second M5Vec2 to test.

\return
True if the M5Vec2 are the same, false otherwise.
*/
/******************************************************************************/
bool M5Vec2::IsEqual(const M5Vec2& vec1, const M5Vec2& vec2)
{
  return (vec1 == vec2);
}
/******************************************************************************/
/*!
Tests if two M5Vec2 are not equal.

\param vec1
A pointer to the first M5Vec2 to test.

\param vec2
A pointer to the second M5Vec2 to test.

\return
True if the M5Vec2 are not the same, false otherwise.
*/
/******************************************************************************/
bool M5Vec2::IsNotEqual(const M5Vec2& vec1, const M5Vec2& vec2)
{
  return vec1 != vec2;
}
/******************************************************************************/
/*!
Tests if the x, y members are zero

\param vec
A pointer to the M5Vec2 to test.

\return
Returns true if the x, y are zero. False otherwise
*/
/******************************************************************************/
bool M5Vec2::IsZero(const M5Vec2& vec)
{
  return vec.IsZero();
}
/******************************************************************************/
/*!
Adds 2 vectors together.  Allows for vec1 = vec2 + vec3;

\param rhs
The vector to add.

\return
A new vector that is the sum of this and rhs.
*/
/******************************************************************************/
M5Vec2 M5Vec2::operator+(const M5Vec2& rhs) const
{
  M5Vec2 toReturn;
  toReturn.Set(x + rhs.x, y + rhs.y);
  return toReturn;
}
/******************************************************************************/
/*!
Subtracts 2 vectors.  Allows for vec1 = vec2 - vec3;

\param rhs
The vector to subtract.

\return
A new vector that is the difference of this and rhs.
*/
/******************************************************************************/
M5Vec2 M5Vec2::operator-(const M5Vec2& rhs) const
{
  M5Vec2 toReturn;
  toReturn.Set(x - rhs.x, y - rhs.y);
  return toReturn;
}
/******************************************************************************/
/*!
Negates (changes the sign of) of the x, y  of the M5Vec2. It is ok
to have both pointers be the same object.

\return
A new vector that is the negated version of this.
*/
/******************************************************************************/
M5Vec2 M5Vec2::operator-(void) const
{
  M5Vec2 toReturn;
  toReturn.Set(x * -1, y * -1);
  return toReturn;
}
/******************************************************************************/
/*!
Scales a vector.  Allows for vec1 = vec2 * 2;

\param scale
The float to scale by

\return
A new vector that is scaled by the float
*/
/******************************************************************************/
M5Vec2 M5Vec2::operator*(float scale) const
{
  M5Vec2 toReturn;
  toReturn.Set(x * scale, y * scale);
  return toReturn;
}
/******************************************************************************/
/*!
Scales this vector.  Allows for vec1 *= 2;

\param scale
The value to scale by

\return
This vector after being scaled by the float
*/
/******************************************************************************/
M5Vec2& M5Vec2::operator*=(float scale)
{
  x *= scale;
  y *= scale;
  return *this;
}
/******************************************************************************/
/*!
Adds a vector to this vector.  Allows for vec1 += vec2;

\param rhs
The vector to add

\return
This vector after being added to rhs
*/
/******************************************************************************/
M5Vec2& M5Vec2::operator+=(const M5Vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}
/******************************************************************************/
/*!
Subtracts a vector from this vector.  Allows for vec1 -= vec2;

\param rhs
The vector to subract

\return
This vector after being subtracted from
*/
/******************************************************************************/
M5Vec2& M5Vec2::operator-=(const M5Vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}
/******************************************************************************/
/*!
Negates a vector.  Allows for -vec1;

\return
This vector after being negated
*/
/******************************************************************************/
M5Vec2& M5Vec2::operator-(void)
{
  x *= -1.f;
  y *= -1.f;
  return *this;
}
/******************************************************************************/
/*!
Test for Equality.  Allows for vec1 == vec2

\param rhs
The vector to test with

\return
Returns true if the vectors are the same. False otherwise
*/
/******************************************************************************/
bool M5Vec2::operator==(const M5Vec2& rhs) const
{
  return (M5Math::IsFloatEqual(x, rhs.x) && M5Math::IsFloatEqual(y, rhs.y));
}
/******************************************************************************/
/*!
Test for Inequality.  Allows for vec1 != vec2

\param rhs
The vector to test with

\return
Returns false if the vectors are the same. True otherwise
*/
/******************************************************************************/
bool M5Vec2::operator!=(const M5Vec2& rhs) const
{
  return !M5Math::IsFloatEqual(x, rhs.x) || !M5Math::IsFloatEqual(y, rhs.y);
}
/******************************************************************************/
/*!
Normalize this vector.

\attention
This function will crash if you normalize the zero vector.
*/
/******************************************************************************/
void M5Vec2::Normalize(void)
{
  float length = this->Length();

  M5DEBUG_ASSERT(!M5Math::IsFloatEqual(length, 0.f),
    "Normalizing the zero vector");

  x /= length;
  y /= length;
}
/******************************************************************************/
/*!
Performs the DotProduct on two vectors.

\param rhs
The vector to dot with.

\return
The dot product of the two vectors.
*/
/******************************************************************************/
float M5Vec2::Dot(const M5Vec2& rhs) const
{
  return x * rhs.x + y * rhs.y;
}
/******************************************************************************/
/*!
Calculates the z value of the cross product.  The z value uses only the x and y
components.  This can be used to calculate the sin of the of the angle, or
the area between the vectors.

\param rhs
The vector to cross.

\return
The z component of the cross product.
*/
/******************************************************************************/
float M5Vec2::CrossZ(const M5Vec2& rhs) const
{
  return (x * rhs.y) - (rhs.x * y);
}
/******************************************************************************/
/*!
Gets the length of the vector.

\return
The length of the vector.
*/
/******************************************************************************/
float M5Vec2::Length(void) const
{
  return std::sqrt(x*x + y*y);
}
/******************************************************************************/
/*!
Gets the squared length of the vector.

\return
The squared length of the vector.
*/
/******************************************************************************/
float M5Vec2::LengthSquared(void) const
{
  return x*x + y*y;
}
/******************************************************************************/
/*!
Treats the vectors as points and gets the distance between them.

\param point
The point to get the distance to.

\return
The distance between the points.
*/
/******************************************************************************/
float M5Vec2::Distance(const M5Vec2& point) const
{
  M5Vec2 diff = *this;
  /*Get the vector between them*/
  diff -= point;
  /*Get the length of that vector squared*/
  return std::sqrt(diff.x*diff.x + diff.y*diff.y);
}
/******************************************************************************/
/*!
Treats the vectors as points and gets the squared distance between them.

\param point
The point to get the distance to.

\return
The squared distance between the points.
*/
/******************************************************************************/
float M5Vec2::DistanceSquared(const M5Vec2& point) const
{
  M5Vec2 diff = *this;
  /*Get the vector between them*/
  diff -= point;
  /*Get the length of that vector squared*/
  return diff.x*diff.x + diff.y*diff.y;
}
/******************************************************************************/
/*!
Tests if the x, y members are zero

\return
Returns true if the x, y are zero. False otherwise
*/
/******************************************************************************/
bool M5Vec2::IsZero(void) const
{
  /*Test if they are really close to zero*/
  return (std::abs(x) < M5Math::EPSILON && std::abs(y) < M5Math::EPSILON);
}
/******************************************************************************/
/*!
Scales a Vecor by a float.  Allows for vec1 = 2.f * vec2.

\param scale
The float to scale by

\param rhs
The vector to scale.

\return
A new vector scaled by the float.
*/
/******************************************************************************/
M5Vec2 operator*(float scale, const M5Vec2& rhs)
{
  return rhs * scale;
}
std::istream& operator >> (std::istream& is, M5Vec2& rhs)
{
	is >> rhs.x;
	is >> rhs.y;
	return is;
}
std::ostream& operator<<(std::ostream& os, const M5Vec2& rhs)
{
	os << rhs.x << " " << rhs.y << " ";
	return os;
}
