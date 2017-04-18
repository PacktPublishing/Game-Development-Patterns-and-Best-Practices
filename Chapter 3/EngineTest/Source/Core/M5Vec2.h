/******************************************************************************/
/*!
\file   M5Vec2.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Prototypes for the M5Vec2 Struct

*/
/******************************************************************************/
#ifndef M5_VEC2_H
#define M5_VEC2_H

/*! A 2D vector for a 2D game, use a separate variable for Z-Order. 
Can be used C style with static functions or C++ with methods.*/
struct M5Vec2
{
  /*Default constructor for vec2 Class*/
  M5Vec2(float xx = 0, float yy = 0);
  //Operators
  /*Adds two vectors*/
  M5Vec2  operator+(const M5Vec2& rhs) const;
  /*Subtracts two vectors*/
  M5Vec2  operator-(const M5Vec2& rhs) const;
  /*Negates a vector*/
  M5Vec2 operator-(void) const;
  /*Scales a vector*/
  M5Vec2  operator*(float scale)       const;
  /*Adds a vector to this vector*/
  M5Vec2& operator+=(const M5Vec2& rhs);
  /*Subtracts a vector from this vector*/
  M5Vec2& operator-=(const M5Vec2& rhs);
  /*Scales this vector*/
  M5Vec2& operator*=(float scale);
  /*Negates this vector*/
  M5Vec2& operator-(void);
  /*Tests if two vectors are equal*/
  bool    operator==(const M5Vec2& rhs) const;
  /*Tests if two vectors are not equal*/
  bool    operator!=(const M5Vec2& rhs) const;

  /*Normalizes this vector*/
  void Normalize(void);
  /*Allows user to quickly set x and y*/
  void  Set(float xx = 0.f, float yy = 0.f);
  /*Performs the dot product on two vectors*/
  float Dot(const M5Vec2& rhs) const;
  /*Gets the Z component of the cross product of two vectors*/
  float CrossZ(const M5Vec2& rhs) const;
  /*Gets the length of the vector*/
  float Length(void) const;
  /*Gets the squared length of the vector*/
  float LengthSquared(void) const;
  /*Treats the vector as a point and gets the distace to another pointer*/
  float Distance(const M5Vec2& point) const;
  /*Gets the squared distance between two points*/
  float DistanceSquared(const M5Vec2& point) const;
  /*Checks if this is the zero vector*/
  bool  IsZero(void) const;

  //Non member functions*******************************************************
  /*Allows user to quickly set x and y*/
  static void Set(M5Vec2& result, float x, float y);
  /*Negates a vector*/
  static void Negate(M5Vec2& result, const M5Vec2& toNegate);
  /*Adds two vectors together*/
  static void Add(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2);
  /*Subtracts two vectors*/
  static void Sub(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2);
  /*Scales a vector*/
  static void Scale(M5Vec2& result, const M5Vec2& toScale, float scale);
  /*Normalizes a vector*/
  static void Normalize(M5Vec2& result, const M5Vec2& toNormalize);
  /*Gets the projection vector of vec1 onto vec2*/
  static void Project(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2);
  /*Gets the perpendicular projection vector of vec1 onto vec2*/
  static void PerpProject(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2);
  /*Linearly interpolates a vector based on time*/
  static void Lerp(M5Vec2& result, const M5Vec2& vec1, const M5Vec2& vec2,
    float time);
  /*Gets the Z component of the cross product */
  static float CrossZ(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Calculates the dot product of two vectors*/
  static float Dot(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Get the Length of a vector*/
  static float Length(const M5Vec2& vec);
  /*Gets the squared length of the vector*/
  static float LengthSquared(const M5Vec2& vec);
  /*Get the Distance between two points.*/
  static float Distance(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Gets the squared distance between two points*/
  static float DistanceSquared(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Tests if two vectors are equal*/
  static bool IsEqual(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Tests if two vectors are not equal*/
  static bool IsNotEqual(const M5Vec2& vec1, const M5Vec2& vec2);
  /*Test if this is the zero vector*/
  static bool IsZero(const M5Vec2& vec);

  //friend function************************************************************
  /*Allows users to scale a vector*/
  friend M5Vec2 operator*(float scale, const M5Vec2& rhs);

  float x;/*!< The x coordinate of the vector*/
  float y;/*!< The y coordinate of the vector*/

};




#endif