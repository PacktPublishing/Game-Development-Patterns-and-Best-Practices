/******************************************************************************/
/*!
file    M5Intersect.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    2D Game Engine
\date   2016/08/7

This file has functions to test intersection  and distance.
*/
/******************************************************************************/
#include "M5Intersect.h"
#include "M5Math.h"
#include <cmath> //For sqrt

namespace M5Distance
{
/******************************************************************************/
/*!
Get the distance from a point to a circle.

\param pPoint
The location of the point.

\param pCircleCenter
The location of the circle center

\param radius
The radius of the circle

\return
The distance from the point to the circle.  A negative distance means the
point is in the circle.
*/
/******************************************************************************/
float PointCircle(const M5Vec2& pPoint, const M5Vec2& pCircleCenter,
  float radius)
{
  return M5Vec2::Distance(pPoint, pCircleCenter) - radius;
}
/******************************************************************************/
/*!
Gets the distance from a point to a rect.

\param pPoint
The location of the point.

\param rectCenter
The location of the rect center.

\param width
The width of the rect.

\param height
The height of the rect.

\return
The distance from the point to the rect. A negative distance means
the point is in the rect.
*/
/******************************************************************************/
float PointRect(const M5Vec2& pPoint, const M5Vec2& rectCenter,
  float width, float height)
{
  /*We are given the full width and height, but we only need half*/
  float distance;
  float halfWidth = width / 2.f;
  float halfHeight = height / 2.f;

  M5Vec2 pointInRectSpace;
  M5Vec2 closestOnRect;

  /*Move the point into rect space.  Shift the point and treat it like the rect
  is at the origin.  This way the calculation only need halfSize and no offset
  */
  M5Vec2::Sub(pointInRectSpace, pPoint, rectCenter);

  /*Find the closest point on the rect*/
  closestOnRect.x = M5Math::Clamp(pointInRectSpace.x, -halfWidth, halfWidth);
  closestOnRect.y = M5Math::Clamp(pointInRectSpace.y, -halfHeight, halfHeight);

  distance = M5Vec2::Distance(pointInRectSpace, closestOnRect);

  /*Check if the point is in the rect*/
  if ((pointInRectSpace.x <  halfWidth) &&
    (pointInRectSpace.x > -halfWidth) &&
    (pointInRectSpace.y <  halfHeight) &&
    (pointInRectSpace.y > -halfHeight))
  {
    /*Swap the sign*/
    distance *= -1.f;
  }

  return distance;
}
/******************************************************************************/
/*!
Gets the distance from a point to a line segment.

\param pPoint
The location of the point.

\param pLineStart
The start location of the line segment.

\param pLineEnd
The end location of the line segment.

\return
The distance from the line to the point

*/
/******************************************************************************/
float PointLine(const M5Vec2& pPoint, const M5Vec2&pLineStart,
  const M5Vec2& pLineEnd)
{
  M5Vec2 lineVec;/*The vector of the line*/
  M5Vec2 normLineVec;/*for the normalized Line vector*/
  M5Vec2 pointVec;/*The vector from lineStart to the point*/
  float segmentLength;
  float projectedLength;
  float distanceToLineSquared;

  /*Get line vector*/
  M5Vec2::Sub(lineVec, pLineEnd, pLineStart);
  /*Get the vector to the point*/
  M5Vec2::Sub(pointVec, pPoint, pLineStart);

  /*Get segment length*/
  segmentLength = M5Vec2::Length(lineVec);

  /*If the segment is very very small, considerate a point*/
  if (segmentLength <= M5Math::EPSILON)
    return M5Vec2::Length(pointVec);

  /*If the line is more than just a point, project the point onto the line
  and get the length of the projected vector*/

  /*First normalize the line vector*/
  M5Vec2::Normalize(normLineVec, lineVec);

  /*Then project*/
  projectedLength = M5Vec2::Dot(pointVec, normLineVec);

  /*If the projected length is before the start of the segment,
  the closest point is the start*/
  if (projectedLength <= 0.f)
    return M5Vec2::Length(pointVec);
  else if (projectedLength >= segmentLength)
  {
    return M5Vec2::Distance(pPoint, pLineEnd);
  }

  /*If we got here, the projection vector is within the line segment
  Now we can use Pythagorean theorem to get the unknown side of the
  triangle.*/
  distanceToLineSquared = M5Vec2::LengthSquared(pointVec) -
    (projectedLength * projectedLength);

  /*if the floating point error causes the length to be less than zero or
  */
  if (distanceToLineSquared < 0.f ||
    std::abs(distanceToLineSquared) <= M5Math::EPSILON)
  {
    return 0.f;
  }

  /*Otherwise just get distance*/
  return std::sqrt(distanceToLineSquared);
}
/******************************************************************************/
/*!
Gets the distance between two circles.

\param pCircleCenter0
The center of the first circle.

\param radius0
The radius of the first circle.

\param pCircleCenter1
The center of the second circle.

\param radius1
The radius of the second circle.

\return
The distance between the two circles.  A value of zero or negative means they
are intersecting.
*/
/******************************************************************************/
float CircleCircle(const M5Vec2& pCircleCenter0, float radius0,
  const M5Vec2& pCircleCenter1, float radius1)
{
  return PointCircle(pCircleCenter0, pCircleCenter1, radius0 + radius1);
}
/******************************************************************************/
/*!
Gets the distance from a circle to a rectangle.

\param pCircleCenter
The center of the circle.

\param radius
The radius of the circle.

\param rectCenter
The center of the rectangle.

\param width
The width of the rect.

\param height
The height of the rect.

\return
The distance between the circle and rectangle.  A value of zero or negative
means they are intersecting.
*/
/******************************************************************************/
float CircleRect(const M5Vec2& pCircleCenter, float radius,
  const M5Vec2& rectCenter, float width,
  float height)
{
  return PointRect(pCircleCenter, rectCenter, width, height) - radius;
}
/******************************************************************************/
/*!
Gets the distance from a circle to a line segment.

\param circleCenter
The center of the circle.

\param radius
The radius of the circle.

\param lineStart
The start location of the line.

\param lineEnd
The end location of the line.

\return
The distance from the circle to the line segment. A value of zero or negative
means they are intersecting.
*/
/******************************************************************************/
float CircleLine(const M5Vec2& circleCenter, float radius,
  const M5Vec2& lineStart,
  const M5Vec2& lineEnd)
{
  return PointLine(circleCenter, lineStart, lineEnd) - radius;
}
/******************************************************************************/
/*!
Gets the distance between two rectangles.

\param rectCenter0
The center of the first rectangle.

\param width0
The width of the first rectangle.

\param height0
The height of the first rectangle.

\param rectCenter1
The center of the second rectangle.

\param width1
The width of the second rectangle.

\param height1
The height of the second rectangle.

\return
The distance between the two rectangles. A value of zero or negative means
they are intersecting.
*/
/******************************************************************************/
float RectRect(const M5Vec2& rectCenter0, float width0, float height0,
  const M5Vec2& rectCenter1, float width1, float height1)
{
  return PointRect(rectCenter0, rectCenter1, width0 + width1,
    height0 + height1);
}
}//end namespace M5Distance

namespace M5Intersect
{
/******************************************************************************/
/*!
Tests for intersection between a point and a circle.

\param point
The location of the point.

\param circleCenter
The location of the center of the circle.

\param radius
The radius of the circle.

\return
True if the point is in the circle.  False otherwise.
*/
/******************************************************************************/
bool PointCircle(const M5Vec2& point, const M5Vec2& circleCenter, float radius)
{
  return M5Vec2::DistanceSquared(point, circleCenter) - (radius*radius) <=
    M5Math::EPSILON;
}
/******************************************************************************/
/*!
Tests for intersection between a point and a rectangle.

\param point
The location of the point.

\param rectCenter
The location of the center of the rect.

\param width
The width of the rectangle.

\param height
The height of the rectangle.

\return
True if the point and rect are intersecting.  False otherwise.
*/
/******************************************************************************/
bool PointRect(const M5Vec2& point, const M5Vec2& rectCenter, float width, 
  float height)
{
  /*We need the have sizes of the rect*/
  float halfWidth = width / 2.f;
  float halfHeight = height / 2.f;

  /*Move the point into rect space.  Treat the rect like it is at the origin*/
  M5Vec2 pointInRectSpace;
  M5Vec2::Sub(pointInRectSpace, point, rectCenter);

  /*If the point in the rect space is inside the extents of the rect
  Then it is inside the rect*/
  return ((pointInRectSpace.x <  halfWidth) &&
    (pointInRectSpace.x > -halfWidth) &&
    (pointInRectSpace.y <  halfHeight) &&
    (pointInRectSpace.y > -halfHeight));

}
/******************************************************************************/
/*!
Test for intersection between two circles.

\param circleCenter0
The location of the center of the first circle.

\param radius0
The radius of the first circle.

\param circleCenter1
The location of the center of the second circle.

\param radius1
The radius of the second circle.

\return
True if the circles are intersecting, false otherwise.
*/
/******************************************************************************/
bool CircleCircle(const M5Vec2& circleCenter0, float radius0,
  const M5Vec2& circleCenter1, float radius1)
{
  return PointCircle(circleCenter0, circleCenter1,
    radius0 + radius1);
}
/******************************************************************************/
/*!
Tests for intersection between a circle and a rectangle.

\param circleCenter
The location of the center of the circle.

\param radius
The radius of the circle.

\param rectCenter
The center of the rect.

\param width
The width of the rectangle.

\param height
The height of the rectangle.

\return
TRUE if the circle and rect are intersecting, false otherwise.
*/
/******************************************************************************/
bool CircleRect(const M5Vec2& circleCenter, float radius,
  const M5Vec2& rectCenter, float width,
  float height)
{
  //I can do better, get closest point on the rect and test if dist squared is
  //greater than radius squared
  return M5Distance::CircleRect(circleCenter, radius, rectCenter,
    width, height) <= M5Math::EPSILON;
}
/******************************************************************************/
/*!
Tests intersection between a circle and a line segment.

\param circleCenter
The center of the circle.

\param radius
The radius of the circle.

\param lineStart
The location of the start of the line.

\param lineEnd
The location of the end of the line.

\return
True if the circle and the line are intersecting, false otherwise.
*/
/******************************************************************************/
bool CircleLine(const M5Vec2& circleCenter, float radius,
  const M5Vec2& lineStart,
  const M5Vec2& lineEnd)
{
  //I can do better
  return M5Distance::CircleLine(circleCenter, radius, lineStart, lineEnd) <=
    M5Math::EPSILON;
}
/******************************************************************************/
/*!
Test for intersection between to rectangles

\param rectCenter0
The center of the first rect.

\param width0
The width of the first rectangle.

\param height0
The height of the first rectangle.

\param rectCenter1
The center of the second rectangle.

\param width1
The width of the second rectangle.

\param height1
The height of the second rectangle.

\return
True if the two rectangles are intersecting, false otherwise.
*/
/******************************************************************************/
bool RectRect(const M5Vec2& rectCenter0,
  float width0, float height0,
  const M5Vec2& rectCenter1,
  float width1, float height1)
{
  return PointRect(rectCenter0, rectCenter1, width0 + width1,
    height0 + height1);
}
}//end namespace M5Intersect

