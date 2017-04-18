/******************************************************************************/
/*!
\file   M5Mtx44.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Prototypes for the M5Mtx44 Struct

*/
/******************************************************************************/
#ifndef M5_MTX44_H
#define M5_MTX44_H

#include "M5Vec2.h"

/*! The number of rows in the matrix*/
const int M5_ROWS = 4;
/*! The number of columns in the matrix*/
const int M5_COLS = 4;

/*! A 4D Matrix for a 2D game, z is used for Z-order.  This matrix uses row
vectors.  This means the members of a vector are placed in each row of the
matrix.
\verbatim
|Xx Xy Xz 0 |
|Yx Yy Yz 0 |
|Zx Zy Zz 0 |
|Tx Ty Tz 1 |
\endverbatim
*/
struct M5Mtx44
{
  float m[M5_ROWS][M5_COLS];/*!< Array of 16 floats to represent a 4x4 matrix*/

  //C++ Additions

  //Member functions
  //Sets all of the matrix values to 0
  void MakeZero(void);
  //Sets the matrix to the Identity Matrix
  void MakeIdentity(void);
  //Sets this matrix to a tranlsation matrix with the given values
  void MakeTranslate(float x, float y, float zOrder);
  //Sets this matrix to a tranlsation matrix with the given values
  void MakeTranslate(const M5Vec2& trans, float zOrder);
  //Sets the matrix to a scale matrix with the given values
  void MakeScale(float x, float y);
  //Sets this matrix to a scale matrix with the given values
  void MakeScale(const M5Vec2& scale);
  //Sets this matrix to a Rotation matrix around the Z axix
  void MakeRotateZ(float radians);
  //Sets this Matrix to scale rotate and translation matrix with the give values
  void MakeTransform(float scaleX, float scaleY, float radians,
    float transX, float transY, float zOrder);
  //Sets this Matrix to scale rotate and translation matrix with the give values
  void MakeTransform(const M5Vec2& scale, float radians,
    const M5Vec2& trans, float zOrder);

  //Operators
  //Lets the user mulitply two matricies together
  M5Mtx44 operator*(const M5Mtx44& rhs) const;
  //Lets the user mulitply two matricies together
  M5Mtx44& operator*=(const M5Mtx44& rhs);
  //Tests if two matricies are the same
  bool operator==(const M5Mtx44& rhs) const;
  //Tests if two matrices are not the same
  bool operator!=(const M5Mtx44& rhs) const;


  //Non member functions
  //Makes all matrix values 0
  static void MakeZero(M5Mtx44& result);
  //Sets the given matrix to the Identity matrix
  static void MakeIdentity(M5Mtx44& result);
  //Multiplies two matricies together
  static void Multiply(M5Mtx44& result, const M5Mtx44& first, const M5Mtx44& second);

  //Sets the given matrix to a translate matrix
  static void MakeTranslate(M5Mtx44& result,
    float transX, float transY, float zOrder);
  //Sets the given matrix to a scale matrix
  static void MakeScale(M5Mtx44& result, float scaleX, float scaleY);
  //Sets the given matrix to a Rotation around the Z axis matrix
  static void MakeRotateZ(M5Mtx44& result, float radians);

  //Sets the given matrix to a scale rotate and translate matrix
  static void MakeTransform(M5Mtx44& result, float scaleX, float scaleY,
    float radians,
    float transX, float transY,
    float zOrder);
  //Tests if two matricies are the same
  static bool IsEqual(const M5Mtx44& mtx1, const M5Mtx44& mtx2);


};




#endif