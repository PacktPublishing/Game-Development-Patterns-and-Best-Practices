/******************************************************************************/
/*!
\file   M5Math.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Math Defines and Math Helper Functions

*/
/******************************************************************************/
#ifndef M5_MATH_H
#define M5_MATH_H

//!Basic math helper functions and values
namespace M5Math
{
/*!The smallest value between two floats*/
const float EPSILON = 0.00001f;
/*!The value of PI*/
const float PI = 3.1415926535897932384626433832795f;
/*!The Value of PI/2*/
const float HALF_PI = (PI * .5f);
/*!The value of 2PI*/
const float TWO_PI = (PI * 2.0f);
/*Converts an angle in Radians to Degress*/
float RadianToDegree(float radians);
/*Converts an angle in Degrees to Radians*/
float DegreeToRadian(float degrees);
/*Keeps a value between a low and a high range*/
float Clamp(float x, float low, float high);
/*If x is below the low value it will return the high value
if x is higher than the high value, it will return the low value*/
float Wrap(float x, float low, float high);
/*Returnts the Minimume of two floats*/
float Min(float x, float y);
/*Returns the maximume of two floats*/
float Max(float x, float y);
/*Linearly interpololates between start and end*/
float Lerp(float start, float end, float time);
/*Checks if a value is between a low and high*/
bool  IsInRange(float x, float low, float high);
/*Test is two floats are equal*/
bool  IsFloatEqual(float x, float y);
/*Checks if an int is a power of 2*/
bool  IsPowerOf2(int x);
/*Given a value, this returns the next power of two*/
int   GetNextPowerOf2(int x);
/*Linearly interpolates between start and end*/
int   Lerp(int start, int end, float time);
/*Linearly interpolates between start and end*/
char  Lerp(char start, char end, float time);
}//end namespace M5Math





#endif