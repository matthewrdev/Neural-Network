#ifndef CLARITY_MATH_H
#define CLARITY_MATH_H

/** @file Math.h
*
*  This file contains the math constants and functions.
*
*  This source file is part of Clarity.
*  Clarity is a game engine designed for teaching.
*  For the latest info, see http://members.optusnet.com.au/dfreya
*
*  Copyright (c) 2007 Dale Freya
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*  or go to http://www.gnu.org/copyleft/lesser.txt.
*
*/

#include <iostream>


namespace Clarity
{
   class Ray2;
   class Circle;
   class AARect;
   class LineSegment2;
   struct Vector2;

    extern const float POS_INFINITY;        /**< Positive infinity */
    extern const float NEG_INFINITY;        /**< Negative infinity */
    extern const float PI;                  /**< PI */
    extern const float TWO_PI;              /**< PI x 2 */
    extern const float HALF_PI;             /**< PI x 0.5 */
    extern const float RADIANS_PER_DEGREE;  /**< Multiply by to convert from degrees to radians */
    extern const float DEGREES_PER_RADIAN;  /**< Multiply by to convert from radians to degrees */
    extern const float EPSILON;             /**< Very small value.  Used for tolerances. */

   /**
   * Cosine trigonometric function.
   *
   * @param x
   *     The angle in radians on which to perform a cosine operation.
   *
   * @returns
   *     The cosine of the supplied angle.
   */
    float Cos(float x);

   /**
   * Sine trigonometric function.
   *
   * @param x
   *     The angle in radians on which to perform a sine operation.
   *
   * @returns
   *     The sine of the supplied angle.
   */
    float Sin(float x);

   /**
   * Tangent trigonometric function.
   *
   * @param x
   *     The angle in radians on which to perform a tangent operation.
   *
   * @returns
   *     The tangent of the supplied angle.
   */
    float Tan(float x);

   /**
   * Arccosine (inverse cosine) trigonometric function.
   *
   * @param x
   *     The ratio on which to perform a arccosine operation.
   *
   * @returns
   *     The arccosine of the supplied ratio.
   */
    float ACos(float x);

   /**
   * Arcsine (inverse sine) trigonometric function.
   *
   * @param x
   *     The ratio on which to perform a arcsine operation.
   *
   * @returns
   *     The arcsine of the supplied ratio.
   */
    float ASin(float x);

   /**
   * Arctangent (inverse tangent) trigonometric function.
   *
   * @param x
   *     The ratio on which to perform a arctangent operation.
   *
   * @returns
   *     The arctangent of the supplied ratio.
   */
    float ATan(float x);

   /**
   * Arctangent (inverse tangent) trigonometric function with quadrant 
   * compuatation.  It is similar to calculating the arctangent of y/x, 
   * except that the signs of both arguments are used to determine the 
   * quadrant of the result.  This function is used to find the direction 
   * rom one point to another in 2-dimensional Euclidean space.
   *
   * @param fY
   *     The Y coordinate of a point in two dimensional space.
   * @param fX
   *     The X coordinate of a point in two dimensional space.
   *    
   * @returns
   *     The arctangent of the fY/fX adjusted by quadrant.
   */
    float ATan2(float fY, float fX);

   /**
   * Compute the smallest integral value that is not less than x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The smallest integral value that is not less than x.
   */
    float Ceil(float x);

   /**
   * Compute the largest integral value that is not greater than x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The largest integral value that is not greater than x.
   */
    float Floor(float x);

   /**
   * Compute the integral value closest to x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The integral value closest to x.
   */
    float Round(float x);

   /**
   * Compute the exponential function of x, which is the e number raised to 
   * the power x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The exponential function of x.
   */
    float Exp(float x);

   /**
   * Compute the natural logarithm of x.
   *
   * The natural logarithm is the base-e logarithm, the inverse of the 
   * natural exponential function (exp). For base-10 logarithms, a specific 
   * function log10 exists.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The natural logarithm of x.
   */
    float Log(float x);

   /**
   * Computes base raised to the power exponent.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     Base raised to the power exponent.
   */
    float Pow(float base, float exponent);

   /**
   * Computes the absolute value of parameter x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The absolute value of x.
   */
    float Abs(float x);

   /**
   * Computes the sign of x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     - x < 0  => -1
   *     - x = 0  =>  0
   *     - x > 0  => +1
   */
    float Sign(float x);

   /**
   * Computes the square of x.
   *
   * @param x
   *     A floating point number.
   *    
   * @returns
   *     The square of x.
   */
    float Sqr(float x);

   /**
   * Computes the square root of x.
   *
   * @param x
   *     A non-negative floating point number.
   *    
   * @returns
   *     The square root of x.
   */
    float Sqrt(float x);

   /**
   * Computes the inverse square root of x.
   *
   * @param x
   *     A non-negative floating point number.
   *    
   * @returns
   *     The inverse square root of x.
   */
    float InvSqrt(float x);

   /**
   * Converts an angle from degrees to radians.
   *
   * @param degrees
   *     An angle in degrees.
   *    
   * @returns
   *     The given angle in radians.
   */
    float DegreesToRadians(float degrees);

   /**
   * Converts an angle from radians to degrees.
   *
   * @param radians
   *     An angle in radians.
   *    
   * @returns
   *     The given angle in degrees.
   */
    float RadiansToDegrees(float radians);


   /**
   * Performs an intersection test between two circles.
   *
   * @param circle1
   *     One of the circles to test for intersection.
   * @param circle2
   *     One of the circles to test for intersection.
   *    
   * @returns
   *     Whether the circles intersect.
   */
    bool Intersects(const Circle &circle1, const Circle &circle2);

   /**
   * Performs an intersection test between a circle and a point.
   *
   * @param circle
   *     The circle to test for intersection.
   * @param point
   *     The point to test for intersection.
   *    
   * @returns
   *     Whether the point is inside the area of the circle.
   */
    bool Intersects(const Circle &circle, const Vector2 &point);

   /**
   * Performs an intersection test between a circle and a ray.
   *
   * @param circle
   *     The circle to test for intersection.
   * @param ray
   *     The ray to test for intersection.
   * @param distance
   *     Optional parameter to store the distance at which the ray intersects 
   *     the circle.  This parameter is only set if it is non-null and an 
   *     intersection occurs.
   *    
   * @returns
   *     Whether the ray intersects the circle.
   */
    bool Intersects(const Circle &circle, const Ray2 &ray, float *distance = NULL);

   /**
   * Performs an intersection test between a circle and an axis aligned rectangle.
   *
   * @param circle
   *     The circle to test for intersection.
   * @param rect
   *     The axis aligned rectangle to test for intersection.
   *    
   * @returns
   *     Whether the circle and rectangle intersect.
   */
    bool Intersects(const Circle &circle, const AARect &rect);

   /**
   * Performs an intersection test between two circles.
   *
   * @param centre1
   *     The centre of the first circle to test for intersection.
   * @param radius1
   *     The radius of the first circle to test for intersection.
   * @param centre2
   *     The centre of the second circle to test for intersection.
   * @param radius2
   *     The radius of the second circle to test for intersection.
   *    
   * @returns
   *     Whether the circles intersect.
   */
    bool Intersects(const Vector2 &centre1, float radius1, const Vector2 &centre2, float radius2);

   /**
   * Performs an intersection test between two axis aligned rectangles.
   *
   * @param rect1
   *     The first rectangle to test for intersection.
   * @param rect2
   *     The second rectangle to test for intersection.
   *    
   * @returns
   *     Whether the rectangles intersect.
   */
    bool Intersects(const AARect &rect1, const AARect &rect2);

   /**
   * Performs an intersection test between an axis aligned rectangle and a point.
   *
   * @param rect
   *     The rectangle to test for intersection.
   * @param point
   *     The point to test for intersection.
   *    
   * @returns
   *     Whether the point in contained within the area of the rectangle.
   */
    bool Intersects(const AARect &rect, const Vector2 &point);

   /**
   * Performs an intersection test between an axis aligned rectangle and a ray.
   *
   * @param rect
   *     The rectangle to test for intersection.
   * @param ray
   *     The ray to test for intersection.
   * @param distance
   *     This distance along the ray at which an intersection occurs.  This
   *     parameter is only set if it is non-null and an intersection occurs.
   *    
   * @returns
   *     Whether the ray intersects the rectangle.
   */
    bool Intersects(const AARect &rect, const Ray2 &ray, float *distance = NULL);

   /**
   * Performs an intersection test between an axis aligned rectangle and a circle.
   *
   * @param rect
   *     The rectangle to test for intersection.
   * @param circle
   *     The circle to test for intersection.
   *    
   * @returns
   *     Whether the rectangle intersects the circle.
   */
    bool Intersects(const AARect &rect, const Circle &circle);

   /**
   * Performs an intersection test between an axis aligned rectangle and a ray.
   *
   * @param ray
   *     The ray to test for intersection.
   * @param rect
   *     The rectangle to test for intersection.
   * @param distance
   *     This distance along the ray at which an intersection occurs.  This
   *     parameter is only set if it is non-null and an intersection occurs.
   *    
   * @returns
   *     Whether the ray intersects the rectangle.
   */
    bool Intersects(const Ray2 &ray, const AARect &rect, float *distance = NULL);

   /**
   * Performs an intersection test between a circle and a ray.
   *
   * @param ray
   *     The ray to test for intersection.
   * @param circle
   *     The circle to test for intersection.
   * @param distance
   *     Optional parameter to store the distance at which the ray intersects 
   *     the circle.  This parameter is only set if it is non-null and an 
   *     intersection occurs.
   *    
   * @returns
   *     Whether the ray intersects the circle.
   */
    bool Intersects(const Ray2 &ray, const Circle &circle, float *distance = NULL);

   /**
   * Performs an intersection test between a double sided line segment and a circle.
   *
   * @param lineSegment
   *     The line segment to test for intersection.
   * @param circle
   *     The circle to test for intersection.
   *
   * @returns
   *     Whether the double sided line segment intersects the circle.
   */
    bool Intersects(const LineSegment2 &lineSegment, const Circle &circle);

   /**
   * Performs an intersection test between a line segment and a ray.
   *
   * @param lineSegment
   *     The line segment to test for intersection.
   * @param singleSided
   *     True if the ray must be headed opposite the normal direction of the 
   *     line segment to intersect.
   * @param ray
   *     The ray to test for intersection.
   * @param distance
   *     Optional parameter to store the distance at which the ray intersects 
   *     the line segment.  This parameter is only set if it is non-null and an 
   *     intersection occurs.
   *
   * @returns
   *     Whether the line segment intersects the circle.
   */
    bool Intersects(const LineSegment2 &lineSegment, bool singleSided, const Ray2 &ray, float *distance);

   /**
    * Calculate the points of intersection of two circles.  There may be
    * zero, one or two points of intersection.
    *
    * @param circle1
    *    The first circle.
    * @param circle2
    *    The second circle.
    * @param point1
    *    This parameter stores the first point of intersection.
    * @param point2
    *    This parameter stores the second point of intersection.
    *
    * @returns
    *    The number of points of intersection.
    */
    int IntersectionPoints(const Circle &cA, const Circle &cB, Vector2 &point1, Vector2 &point2);

   /**
    * For a circle, calculate the points of intersection of the two tangents 
    * from an external point.
    *
    * @param circle
    *    The circle.
    * @param external
    *    The external point.
    * @param point1
    *    This parameter stores the first point of intersection.
    * @param point2
    *    This parameter stores the second point of intersection.
    *
    * @returns
    *    The number of intersects stored.
    */
    int TangentIntersects(const Circle &circle, const Vector2 &external, Vector2 &point1, Vector2 &point2);

   /**
    * For an axis aligned rectangle, calculate the points of intersection 
    * of the two tangents from an external point.
    *
    * @param rect
    *    The rectangle.
    * @param external
    *    The external point.
    * @param point1
    *    This parameter stores the first point of intersection.
    * @param point2
    *    This parameter stores the second point of intersection.
    *
    * @returns
    *    The number of intersects stored.
    */
    int TangentIntersects(const AARect &rect, const Vector2 &external, Vector2 &point1, Vector2 &point2);
}

#endif
