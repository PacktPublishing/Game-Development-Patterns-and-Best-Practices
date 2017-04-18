/******************************************************************************/
/*!
file    M5Mtx44.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Implementation of my Mtx44 Functions
*/
/******************************************************************************/
#include "M5Mtx44.h"
#include "M5Math.h"
#include "M5Debug.h"

#include <cmath> //sqrt, fabs
#include <cstring>//memcpy

/******************************************************************************/
/*!
Sets all of the values to zero.

\param result
The Mtx44 to store the result in.
*/
/******************************************************************************/
void M5Mtx44::MakeZero(M5Mtx44& result)
{
  std::memset(&result, 0, sizeof(result));
}
/******************************************************************************/
/*!
Sets a Mtx44 to the identity matrix.

\param result
The Mtx44 to store the result in.
*/
/******************************************************************************/
void M5Mtx44::MakeIdentity(M5Mtx44& result)
{
  std::memset(&result, 0, sizeof(result));
  result.m[0][0] = 1.0f;
  result.m[1][1] = 1.0f;
  result.m[2][2] = 1.0f;
  result.m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Multiplies two Matrices together and store the result in result.

\attention
result should be the same pointer as first or second.

\param result
The Mtx44 to store the result in.

\param first
The Mtx44 on the left side.

\param second
The Mtx44 on the right side.
*/
/******************************************************************************/
void M5Mtx44::Multiply(M5Mtx44& result, const M5Mtx44& first, const M5Mtx44& second)
{
  result.m[0][0] = first.m[0][0] * second.m[0][0] +
    first.m[0][1] * second.m[1][0] +
    first.m[0][2] * second.m[2][0] +
    first.m[0][3] * second.m[3][0];

  result.m[1][0] = first.m[1][0] * second.m[0][0] +
    first.m[1][1] * second.m[1][0] +
    first.m[1][2] * second.m[2][0] +
    first.m[1][3] * second.m[3][0];

  result.m[2][0] = first.m[2][0] * second.m[0][0] +
    first.m[2][1] * second.m[1][0] +
    first.m[2][2] * second.m[2][0] +
    first.m[2][3] * second.m[3][0];

  result.m[3][0] = first.m[3][0] * second.m[0][0] +
    first.m[3][1] * second.m[1][0] +
    first.m[3][2] * second.m[2][0] +
    first.m[3][3] * second.m[3][0];

  /*************************************************************************/
  result.m[0][1] = first.m[0][0] * second.m[0][1] +
    first.m[0][1] * second.m[1][1] +
    first.m[0][2] * second.m[2][1] +
    first.m[0][3] * second.m[3][1];

  result.m[1][1] = first.m[1][0] * second.m[0][1] +
    first.m[1][1] * second.m[1][1] +
    first.m[1][2] * second.m[2][1] +
    first.m[1][3] * second.m[3][1];

  result.m[2][1] = first.m[2][0] * second.m[0][1] +
    first.m[2][1] * second.m[1][1] +
    first.m[2][2] * second.m[2][1] +
    first.m[2][3] * second.m[3][1];

  result.m[3][1] = first.m[3][0] * second.m[0][1] +
    first.m[3][1] * second.m[1][1] +
    first.m[3][2] * second.m[2][1] +
    first.m[3][3] * second.m[3][1];

  /*************************************************************************/
  result.m[0][2] = first.m[0][0] * second.m[0][2] +
    first.m[0][1] * second.m[1][2] +
    first.m[0][2] * second.m[2][2] +
    first.m[0][3] * second.m[3][2];

  result.m[1][2] = first.m[1][0] * second.m[0][2] +
    first.m[1][1] * second.m[1][2] +
    first.m[1][2] * second.m[2][2] +
    first.m[1][3] * second.m[3][2];

  result.m[2][2] = first.m[2][0] * second.m[0][2] +
    first.m[2][1] * second.m[1][2] +
    first.m[2][2] * second.m[2][2] +
    first.m[2][3] * second.m[3][2];

  result.m[3][2] = first.m[3][0] * second.m[0][2] +
    first.m[3][1] * second.m[1][2] +
    first.m[3][2] * second.m[2][2] +
    first.m[3][3] * second.m[3][2];

  /*************************************************************************/
  result.m[0][3] = first.m[0][0] * second.m[0][3] +
    first.m[0][1] * second.m[1][3] +
    first.m[0][2] * second.m[2][3] +
    first.m[0][3] * second.m[3][3];

  result.m[1][3] = first.m[1][0] * second.m[0][3] +
    first.m[1][1] * second.m[1][3] +
    first.m[1][2] * second.m[2][3] +
    first.m[1][3] * second.m[3][3];

  result.m[2][3] = first.m[2][0] * second.m[0][3] +
    first.m[2][1] * second.m[1][3] +
    first.m[2][2] * second.m[2][3] +
    first.m[2][3] * second.m[3][3];

  result.m[3][3] = first.m[3][0] * second.m[0][3] +
    first.m[3][1] * second.m[1][3] +
    first.m[3][2] * second.m[2][3] +
    first.m[3][3] * second.m[3][3];
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a translation of the x and y axis. Z should
used only for zOrder.

\param result
The Mtx44 to store the result in.

\param transX
The x position in the world.

\param transY
The y position in the world.

\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTranslate(M5Mtx44& result, float transX, float transY,
  float zOrder)
{
  result.MakeIdentity();
  result.m[3][0] = transX;
  result.m[3][1] = transY;
  result.m[3][2] = zOrder;
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a scale of the x and y axis.

\param result
The Mtx44 to store the result in.

\param scaleX
The scale in the x direction.

\param scaleY
The scale in the y direction.
*/
/******************************************************************************/
void M5Mtx44::MakeScale(M5Mtx44& result, float scaleX, float scaleY)
{
  std::memset(&result, 0, sizeof(result));
  result.m[0][0] = scaleX;
  result.m[1][1] = scaleY;
  result.m[2][2] = result.m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Creates a 4x4 Matrix that represents a counter clock wise Rotation about the z 
axis.  The angle is specified in radians.

\param result
The Mtx44 to store the matrix in.

\param radians
The angle in radians of the rotation about the z axis.
*/
/******************************************************************************/
void M5Mtx44::MakeRotateZ(M5Mtx44& result, float radians)
{
  float sinAngle = std::sin(radians);
  float cosAngle = std::cos(radians);

  std::memset(&result, 0, sizeof(result));
  result.m[0][0] = result.m[1][1] = cosAngle;
  result.m[1][0] = -sinAngle;
  result.m[0][1] = sinAngle;
  result.m[2][2] = result.m[3][3] = 1.f;
}
/******************************************************************************/
/*!
Creates a 4x4 Matrix that represents a scale rotation and translation of the
given values multiplied in the correct order.

\param result
The Mtx44 to store the transform in.

\param scaleX
The scale in the x direction.

\param scaleY
The scale in the y direction;

\param radians
The rotation of the axis specified in radians.

\param transX
The x position in the world.

\param transY
The y position in the world.

\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTransform(M5Mtx44& result, float scaleX, float scaleY,
  float radians,
  float transX, float transY,
  float zOrder)
{
  float sinAngle = std::sin(radians);
  float cosAngle = std::cos(radians);

  /*Set the first ROW*/
  result.m[0][0] = scaleX * cosAngle;
  result.m[0][1] = scaleX * sinAngle;
  result.m[0][2] = 0.f;
  result.m[0][3] = 0.f;

  /*Set the second ROW*/
  result.m[1][0] = scaleY * -sinAngle;
  result.m[1][1] = scaleY * cosAngle;
  result.m[1][2] = 0.f;
  result.m[1][3] = 0.f;

  /*Set the third ROW*/
  result.m[2][0] = 0.f;
  result.m[2][1] = 0.f;
  result.m[2][2] = 1.0f;
  result.m[2][3] = 0.f;

  /*Set the Fourth ROW*/
  result.m[3][0] = transX;
  result.m[3][1] = transY;
  result.m[3][2] = zOrder;
  result.m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Tests if two matrix 4x4s are equal within an epsilon value.

\param mtx1
The first matrix to test

\param mtx2
The second matrix to test

\return
True if the matrices are the same, false otherwise.
*/
/******************************************************************************/
bool M5Mtx44::IsEqual(const M5Mtx44& mtx1, const M5Mtx44& mtx2)
{
  int x, y;
  for (y = 0; y < M5_ROWS; ++y)
  {
    for (x = 0; x < M5_COLS; ++x)
    {
      if (!M5Math::IsFloatEqual(mtx1.m[y][x], mtx2.m[y][x]))
        return false;
    }
  }

  return true;
}
/******************************************************************************/
/*!
Sets all matrix values to 0
*/
/******************************************************************************/
void M5Mtx44::MakeZero(void)
{
  std::memset(this, 0, sizeof(*this));
}
/******************************************************************************/
/*!
Creates a 4x4 representation of the indentity matrix.
*/
/******************************************************************************/
void M5Mtx44::MakeIdentity(void)
{
  std::memset(this, 0, sizeof(*this));
  m[0][0] = 1.0f;
  m[1][1] = 1.0f;
  m[2][2] = 1.0f;
  m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a translation of the x and y axis. Z should
used only for zOrder.

\param transX
The x position in the world.

\param transY
The y position in the world.

\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTranslate(float transX, float transY, float zOrder)
{
  MakeIdentity();
  m[3][0] = transX;
  m[3][1] = transY;
  m[3][2] = zOrder;
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a translation of the x and y axis. Z should
used only for zOrder.

\param trans
The x and y position in the world.


\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTranslate(const M5Vec2& trans, float zOrder)
{
  MakeTranslate(trans.x, trans.y, zOrder);
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a scale of the x and y axis.

\param scaleX
The scale in the x direction.

\param scaleY
The scale in the y direction.
*/
/******************************************************************************/
void M5Mtx44::MakeScale(float scaleX, float scaleY)
{
  std::memset(this, 0, sizeof(*this));
  m[0][0] = scaleX;
  m[1][1] = scaleY;
  m[2][2] = m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Creates 4x4 matrix that represents a scale of the x and y axis.

\param scale
A vector that holds the x and y scale values

*/
/******************************************************************************/
void M5Mtx44::MakeScale(const M5Vec2& scale)
{
  MakeScale(scale.x, scale.y);
}
/******************************************************************************/
/*!
Creates a 4x4 Matrix that represents a counter clock wise Rotation about the z
axis.  The angle is specified in radians.

\param radians
The angle in radians of the rotation about the z axis.
*/
/******************************************************************************/
void M5Mtx44::MakeRotateZ(float radians)
{
  float sinAngle = std::sin(radians);
  float cosAngle = std::cos(radians);

  std::memset(this, 0, sizeof(*this));
  m[0][0] = m[1][1] = cosAngle;
  m[1][0] = -sinAngle;
  m[0][1] = sinAngle;
  m[2][2] = m[3][3] = 1.f;
}
/******************************************************************************/
/*!
Quickly makes a tranfrom matrix from tranlate, rotate and scale data without 
the need of multiplication.

\param scaleX
The scale in the x direction.

\param scaleY
The scale in the y direction;

\param radians
The rotation of the axis specified in radians.

\param transX
The x position in the world.

\param transY
The y position in the world.

\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTransform(float scaleX, float scaleY, float radians,
  float transX, float transY, float zOrder)
{
  float sinAngle = std::sin(radians);
  float cosAngle = std::cos(radians);

  /*Set the first ROW*/
  m[0][0] = scaleX * cosAngle;
  m[0][1] = scaleX * sinAngle;
  m[0][2] = 0.f;
  m[0][3] = 0.f;

  /*Set the second ROW*/
  m[1][0] = scaleY * -sinAngle;
  m[1][1] = scaleY * cosAngle;
  m[1][2] = 0.f;
  m[1][3] = 0.f;

  /*Set the third ROW*/
  m[2][0] = 0.f;
  m[2][1] = 0.f;
  m[2][2] = 1.0f;
  m[2][3] = 0.f;

  /*Set the Fourth ROW*/
  m[3][0] = transX;
  m[3][1] = transY;
  m[3][2] = zOrder;
  m[3][3] = 1.0f;
}
/******************************************************************************/
/*!
Quickly makes a tranfrom matrix from tranlate, rotate and scale data without
the need of multiplication.

\param scale
The scale vector

\param radians
The rotation of the axis specified in radians.

\param trans
The translation vector.

\param zOrder
The zOrder of the object.  This should be small, such as between 0 and 1.
*/
/******************************************************************************/
void M5Mtx44::MakeTransform(const M5Vec2& scale, float radians,
  const M5Vec2& trans, float zOrder)
{
  MakeTransform(scale.x, scale.y, radians, trans.x, trans.y, zOrder);
}
/******************************************************************************/
/*!
Multiplies two matricies together and returns a new one.

\param rhs
The matrix to multiply with.

\return
A new matrix that is the product of this and rhs.
*/
/******************************************************************************/
M5Mtx44 M5Mtx44::operator*(const M5Mtx44& rhs) const
{
  M5Mtx44 result;
  Multiply(result, *this, rhs);
  return result;
}
/******************************************************************************/
/*!
Multiplies a matrix with this matrix.

\param rhs
The matrix to multiply with

\attention Because of the way matrix multipilcation works, this function 
must still make a copy of this matrix before doing multiplication.  

\return
This matrix after being multiplied.
*/
/******************************************************************************/
M5Mtx44& M5Mtx44::operator*=(const M5Mtx44& rhs)
{
  M5Mtx44 copy = *this;
  Multiply(*this, copy, rhs);
  return *this;
}
/******************************************************************************/
/*!
Tests if two matrix 4x4s are equal within an epsilon value.

\param rhs
The matrix to test


\return
True if the matrices are the same, false otherwise.
*/
/******************************************************************************/
bool M5Mtx44::operator==(const M5Mtx44& rhs) const
{
  int x, y;
  for (y = 0; y < M5_ROWS; ++y)
  {
    for (x = 0; x < M5_COLS; ++x)
    {
      if (!M5Math::IsFloatEqual(m[y][x], rhs.m[y][x]))
        return false;
    }
  }

  return true;
}
/******************************************************************************/
/*!
Tests if two matrix 4x4s are not equal

\param rhs
The matrix to test

\return
True if the matrices are the not same, false otherwise.
*/
/******************************************************************************/
bool M5Mtx44::operator!=(const M5Mtx44& rhs) const
{
  return !(*this == rhs);
}
