/******************************************************************************/
/*!
\file   M5Intersect.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    2D Game Engine
\date   2016/08/7

Prototypes for intersection and Distance tests

*/
/******************************************************************************/
#ifndef M5_INTERSECTION_H
#define M5_INTERSECTION_H

#include "M5Vec2.h"

//!Functions to test the distance between two objects
namespace M5Distance
{
//!Tests Distance between a point and  a circle
float PointCircle(const M5Vec2& point, const M5Vec2& circleCenter, 
  float radius);
//!Tests Distance between a point and a rectangle
float PointRect(const M5Vec2& point, const M5Vec2& rectCenter, 
  float width, float height);
//!Tests Distance between a point and a line segment
float PointLine(const M5Vec2& point, const M5Vec2& lineStart,
  const M5Vec2& lineEnd);
//!Tests Distance between two circles
float CircleCircle(const M5Vec2& circleCenter0, float radius0,
  const M5Vec2& circleCenter1, float radius1);
//!Tests Distance between a circle and a rectangle
float CircleRect(const M5Vec2& circleCenter, float radius,
  const M5Vec2& rectCenter, float width,
  float height);
//!Tests Distance between a circle and a line segment
float CircleLine(const M5Vec2& circleCenter, float radius,
  const M5Vec2& lineStart,
  const M5Vec2& lineEnd);
//!Tests Distance between two rectangles
float RectRect(const M5Vec2& rectCenter0, float width0, float height0,
  const M5Vec2& rectCenter1,
  float width1, float height1);
}//end namespace Distance


//! Functions to test if two objects are simply intersecting
namespace M5Intersect
{
//! Test if a point intersects a circle
bool PointCircle(const M5Vec2& point, const M5Vec2& circleCenter, 
  float radius);
//! Tests if a point intersects a rectangle
bool PointRect(const M5Vec2& point, const M5Vec2& rectCenter,
  float width, float height);
//! Test if two circles intersect
bool CircleCircle(const M5Vec2& circleCenter0, float radius0,
  const M5Vec2& circleCenter1, float radius1);
//! Test if a circle interects with a rectangle
bool CircleRect(const M5Vec2& circleCenter, float radius,
  const M5Vec2& rectCenter, float width, float height);
//! Test if a circle and a line intersect
bool CircleLine(const M5Vec2& circleCenter, float radius,
  const M5Vec2& lineStart, const M5Vec2& lineEnd);
//! Tests if two rectangles intersect
bool RectRect(const M5Vec2& rectCenter0, float width0, float height0,
  const M5Vec2& rectCenter1, float width1, float height1);
}//end namespace M5Intersect





#endif