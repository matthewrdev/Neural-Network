//****************************************************************************
//**
//**    $Workfile: Clarity_Math.cpp $
//**
//**    This source file is part of Clarity.
//**    Clarity is a game engine designed for teaching.
//**    For the latest info, see http://members.optusnet.com.au/dfreya
//**
//**    Copyright (c) 2007 Dale Freya
//**
//**    This library is free software; you can redistribute it and/or
//**    modify it under the terms of the GNU Lesser General Public
//**    License as published by the Free Software Foundation; either
//**    version 2.1 of the License, or (at your option) any later version.
//**
//**    This library is distributed in the hope that it will be useful,
//**    but WITHOUT ANY WARRANTY; without even the implied warranty of
//**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//**    Lesser General Public License for more details.
//**
//**    You should have received a copy of the GNU Lesser General Public
//**    License along with this library; if not, write to the Free Software
//**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//**    or go to http://www.gnu.org/copyleft/lesser.txt.
//**
//**    This work is partially based on OGRE 
//**        (Object-oriented Graphics Rendering Engine)
//**        For the latest info, see http://www.ogre3d.org/
//**        OGRE is also covered by the GNU Lesser General Public License.
//**
//**    $Author: Dfreya $
//**    $Date: 29/12/06 6:15p $ 
//**    $Revision: 5 $
//**
//****************************************************************************

#include <Clarity/Math/Math.h>
#include <Clarity/Math/AARect.h>
#include <Clarity/Math/Circle.h>
#include <Clarity/Math/Ray2.h>
#include <Clarity/Math/LineSegment2.h>

#include <limits>

namespace Clarity
{
   namespace
   {
      // ---------------------------------------------------------------------
      // Safe Pointer Set Helper
      // ---------------------------------------------------------------------
      template<class T> void SetPtrValue(T *lhs, const T &rhs)
      {
         if (lhs != NULL)
         {
            *lhs = rhs;
         }
      }
   }

   const float POS_INFINITY = std::numeric_limits<float>::infinity();
   const float NEG_INFINITY = -std::numeric_limits<float>::infinity();
   const float PI = static_cast<float>(4.0 * atan(1.0));
   const float TWO_PI = static_cast<float>(2.0 * PI);
   const float HALF_PI = static_cast<float>(0.5 * PI);
   const float RADIANS_PER_DEGREE = PI / static_cast<float>(180.0);
   const float DEGREES_PER_RADIAN = static_cast<float>(180.0) / PI;
   const float EPSILON = 1e-06f;

   float Cos(float fValue)
   {
      return static_cast<float>(cos(fValue));
   }

   float Sin(float fValue)
   {
      return static_cast<float>(sin(fValue));
   }

   float Tan(float fValue)
   {
      return static_cast<float>(tan(fValue));
   }

   float ACos(float fValue)
   {
      return static_cast<float>(acos(fValue));
   }

   float ASin(float fValue)
   {
      return static_cast<float>(asin(fValue));
   }

   float ATan(float fValue)
   {
      return static_cast<float>(atan(fValue));
   }

   float ATan2(float fY, float fX)
   {
      return static_cast<float>(atan2(fY, fX));
   }

   float Ceil(float fValue)
   {
      return static_cast<float>(ceil(fValue));
   }

   float Floor(float fValue)
   {
      return static_cast<float>(floor(fValue));
   }

   float Round(float fValue)
   {
      return Floor(fValue + 0.5f);
   }

   float Exp(float fValue)
   {
      return static_cast<float>(exp(fValue));
   }

   float Log(float fValue)
   {
      return static_cast<float>(log(fValue));
   }

   float Pow(float fBase, float fExponent)
   {
      return static_cast<float>(pow(fBase, fExponent));
   }

   float Abs(float fValue)
   {
      return static_cast<float>(fabs(fValue));
   }

   float Sign(float fValue)
   {
      if (fValue > 0.0f)
      {
         return 1.0f;
      }

      if (fValue < 0.0)
      {
         return -1.0f;
      }

      return 0.0;
   }

   float Sqr(float fValue)
   {
      return fValue * fValue;
   }

   float Sqrt(float fValue)
   {
      return static_cast<float>(sqrt(fValue));
   }

   float InvSqrt(float fValue)
   {
      return static_cast<float>(1.0 / sqrt(fValue));
   }

   float DegreesToRadians(float degrees)
   {
      return degrees * RADIANS_PER_DEGREE;
   }

   float RadiansToDegrees(float radians)
   {
      return radians * DEGREES_PER_RADIAN;
   }

   // Circle Intersection

   bool Intersects(const Circle &circle1, const Circle &circle2)
   {
      const Vector2 &centre1(circle1.GetCentre());
      float radius1(circle1.GetRadius());

      const Vector2 &centre2(circle2.GetCentre());
      float radius2(circle2.GetRadius());

      return Intersects(centre1, radius1, centre2, radius2);
   }

   bool Intersects(const Circle &circle, const Vector2 &point)
   {
      float radius(circle.GetRadius());
      const Vector2 &centre(circle.GetCentre());

      return ((point - centre).MagnitudeSquared() <= radius * radius);
   }

   bool Intersects(const Circle &circle, const Ray2 &ray, float *distance)
   {
      return Intersects(ray, circle, distance);
   }

   bool Intersects(const Circle &circle, const AARect &rect)
   {
      if (rect.IsNull()) 
      {
         return false;
      }

      // Use splitting planes
      const Vector2 &center = circle.GetCentre();
      float radius = circle.GetRadius();
      const Vector2 &min = rect.GetMinimum();
      const Vector2 &max = rect.GetMaximum();

      // just test facing planes, early fail if circle is totally outside
      if (center.x < min.x && 
         min.x - center.x > radius)
      {
         return false;
      }

      if (center.x > max.x && 
         center.x  - max.x > radius)
      {
         return false;
      }

      if (center.y < min.y && 
         min.y - center.y > radius)
      {
         return false;
      }

      if (center.y > max.y && 
         center.y  - max.y > radius)
      {
         return false;
      }

      // Must intersect
      return true;
   }


   bool Intersects(
      const Vector2 &centre1, float radius1, 
      const Vector2 &centre2, float radius2)
   {
      float radiusSum(radius1 + radius2);
      return (centre1 - centre2).MagnitudeSquared() <= (radiusSum * radiusSum);
   }


   // Rectangle Intersection
   bool Intersects(const AARect &rect1, const AARect &rect2)
   {
      // Early-fail for nulls
      if (rect1.IsNull() || rect2.IsNull())
      {
         return false;
      }

      const Vector2 &maximum1(rect1.GetMaximum());
      const Vector2 &minimum2(rect2.GetMinimum());

      // Use up to 4 separating planes
      if (maximum1.x < minimum2.x || maximum1.y < minimum2.y)
      {
         return false;
      }

      const Vector2 &minimum1(rect1.GetMinimum());
      const Vector2 &maximum2(rect2.GetMaximum());

      if (minimum1.x > maximum2.x || minimum1.y > maximum2.y)
      {
         return false;
      }

      // otherwise, must be intersecting
      return true;
   }

   bool Intersects(const AARect &rect, const Vector2 &point)
   {
      const Vector2 &minimum(rect.GetMinimum());
      const Vector2 &maximum(rect.GetMaximum());

      return(point.x >= minimum.x  &&  point.x <= maximum.x  && 
         point.y >= minimum.y  &&  point.y <= maximum.y);
   }

   bool Intersects(const AARect &rect, const Ray2 &ray, float *distance)
   {
      return Intersects(ray, rect, distance);
   }

   bool Intersects(const AARect &rect, const Circle &circle)
   {
      return Intersects(circle, rect);
   }

   // Ray Intersection
   bool Intersects(const Ray2 &ray, const AARect &rect, float *distance)
   {
      if (rect.IsNull()) 
      {
         SetPtrValue(distance, 0.0f);
         return false;
      }

      float lowt = 0.0f;
      float t;
      bool hit = false;
      Vector2 hitpoint;
      const Vector2 &rectMin = rect.GetMinimum();
      const Vector2 &rectMax = rect.GetMaximum();
      const Vector2 &rayOrig = ray.GetOrigin();
      const Vector2 &rayDir = ray.GetDirection();

      // Check origin inside first
      if (rayOrig.x > rectMin.x && rayOrig.y > rectMin.y && rayOrig.x < rectMax.x && rayOrig.y < rectMax.y)
      {
         SetPtrValue(distance, 0.0f);
         return true;
      }

      // Check each face in turn, only check closest 3
      // Min x
      if (rayOrig.x < rectMin.x && rayDir.x > 0)
      {
         t = (rectMin.x - rayOrig.x) / rayDir.x;

         if (t > 0)
         {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayOrig + rayDir * t;
            if (hitpoint.y >= rectMin.y && hitpoint.y <= rectMax.y /* && (!hit || t < lowt) */)
            {
               if (distance == NULL)
               {
                  return true;
               }

               hit = true;
               lowt = t;
            }
         }
      }
      // Max x
      if (rayOrig.x > rectMax.x && rayDir.x < 0)
      {
         t = (rectMax.x - rayOrig.x) / rayDir.x;
         if (t > 0)
         {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayOrig + rayDir * t;
            if (hitpoint.y >= rectMin.y && hitpoint.y <= rectMax.y &&
               (!hit || t < lowt))
            {
               if (distance == NULL)
               {
                  return true;
               }

               hit = true;
               lowt = t;
            }
         }
      }
      // Min y
      if (rayOrig.y < rectMin.y && rayDir.y > 0)
      {
         t = (rectMin.y - rayOrig.y) / rayDir.y;
         if (t > 0)
         {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayOrig + rayDir * t;
            if (hitpoint.x >= rectMin.x && hitpoint.x <= rectMax.x &&
               (!hit || t < lowt))
            {
               if (distance == NULL)
               {
                  return true;
               }

               hit = true;
               lowt = t;
            }
         }
      }
      // Max y
      if (rayOrig.y > rectMax.y && rayDir.y < 0)
      {
         t = (rectMax.y - rayOrig.y) / rayDir.y;
         if (t > 0)
         {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayOrig + rayDir * t;
            if (hitpoint.x >= rectMin.x && hitpoint.x <= rectMax.x &&
               (!hit || t < lowt))
            {
               if (distance == NULL)
               {
                  return true;
               }

               hit = true;
               lowt = t;
            }
         }
      }

      SetPtrValue(distance, lowt);
      return hit;
   }

   bool Intersects(const Ray2 &ray, const Circle &circle, float *distance)
   {
      const Vector2 &rayDir = ray.GetDirection();

      // Adjust ray origin relative to circle center
      const Vector2 &rayOrig = ray.GetOrigin() - circle.GetCentre();
      float radius = circle.GetRadius();

      // Check origin inside first
      if (rayOrig.MagnitudeSquared() <= radius * radius)
      {
         SetPtrValue(distance, 0.0f);
         return true;
      }

      // Mmm, quadratics
      // Build coeffs which can be used with std quadratic solver
      // ie t = (-b +/- sqrt(b * b + 4ac)) / 2a
      float a = Vector2::DotProduct(rayDir, rayDir);
      float b = 2 * Vector2::DotProduct(rayOrig, rayDir);
      float c = Vector2::DotProduct(rayOrig, rayOrig) - radius * radius;

      // Calc determinant
      float d = (b * b) - (4 * a * c);
      if (d < 0)
      {
         // No intersection
         SetPtrValue(distance, 0.0f);
         return false;
      }
      else
      {
         // BTW, if d=0 there is one intersection, if d > 0 there are 2
         // But we only want the closest one, so that's ok, just use the 
         // '-' version of the solver

         float negB(-b);
         float sqrtD(Sqrt(d));
         float twoA(2 * a);

         float t = (negB - sqrtD) / twoA;

         if (t < 0)
         {
            t = (negB + sqrtD) / twoA;
         }

         if (t > 0)
         {
            SetPtrValue(distance, t);
            return true;
         }

         return false;
      }
   }

   bool Intersects(const LineSegment2 &lineSegment, const Circle &circle)
   {
      Ray2 ray(lineSegment.GetTail(), lineSegment.GetDirection());

      float distance;
      bool rayIntersects = Intersects(ray, circle, &distance);

      if (!rayIntersects)
      {
         return false;
      }

      if (distance > lineSegment.GetLength())
      {
         return false;
      }

      return true;
   }


   bool Intersects(const LineSegment2 &lineSegment, bool singleSided, const Ray2 &ray, float *distance)
   {
      if (singleSided && Vector2::DotProduct(ray.GetDirection(), lineSegment.GetNormal()) >= 0.0f)
      {
         // Ray is pointing in the same direction as the line normal
         return false;
      }

      const Vector2 &P0 = ray.GetOrigin();
      const Vector2 &D0 = ray.GetDirection();
      const Vector2 &P1 = lineSegment.GetTail();
      const Vector2 &D1 = lineSegment.GetVector();

      Vector2 perpD0 = Perp(D0);
      Vector2 perpD1 = Perp(D1);

      if (Dot(perpD1, D0) != 0.0f)
      {
         Vector2 P1MinusP0 = P1 - P0;
         float s = Dot(perpD1, P1MinusP0) / Dot(perpD1,D0);
         float t = Dot(perpD0, P1MinusP0) / Dot(perpD1,D0);
         bool intersects = s >= 0.0f && 0.0f <= t && t <= 1.0f;

         if (intersects)
         {
            if (distance)
            {
               // We've probably already calculated the nearest point in terms of s & t but
               // I can't figure it out.
               
               *distance = s; // ((lineSegment.GetTail() + lineSegment.GetDirection() * t) - ray.GetOrigin()).Magnitude();
               // *distance = (nearestPoint - ray.GetOrigin()).Magnitude();
            }

            return true;
         }
      }

      return false;
   }


   int IntersectionPoints(const Circle &circleA, const Circle &circleB, Vector2 &point1, Vector2 &point2)
   {
      const Vector2 &centreA(circleA.GetCentre());
      const Vector2 &centreB(circleB.GetCentre());
      float radiusA(circleA.GetRadius());
      float radiusB(circleB.GetRadius());

      Vector2 aToB(centreB - centreA);

      float distSq = aToB.MagnitudeSquared();

      if (distSq == 0.0f)
      {
         // circles have the same centre
         // either 0 or infinite number of intersection points
         return 0;
      }

      float dist = Sqrt(distSq);

      if (dist > radiusA + radiusB || dist < Abs(radiusA - radiusB))
      {
         // Circles are not intersecting or one is contained within the other
         return 0;
      }

      float distInv = 1.0f / dist;

      float radiusASq(radiusA * radiusA);
      float radiusBSq(radiusB * radiusB);

      float a = (radiusASq - radiusBSq + distSq) * (0.5f * distInv);
      float h = Sqrt(radiusASq - a * a);

      Vector2 aToBDir(aToB * distInv);
      Vector2 m(centreA + a * aToBDir);

      Vector2 aToBNorm(-aToBDir.y, aToBDir.x);

      if (h == 0.0f)
      {
         point1 = m;
         return 1;
      }
      else
      {
         point1 = m + h * aToBNorm;
         point2 = m - h * aToBNorm;
         return 2;
      }
   }

   int TangentIntersects(const Circle &circle, const Vector2 &external, Vector2 &point1, Vector2 &point2)
   {
      Vector2 externalToCentreA(circle.GetCentre() - external);
      Vector2 externalToCentreAMid(externalToCentreA * 0.5f);

      Vector2 centreB(external + externalToCentreAMid);
      float radiusB(externalToCentreAMid.Magnitude());

      Circle circleB(centreB, radiusB);
      
      return IntersectionPoints(circle, circleB, point1, point2);
   }


   int TangentIntersects(const AARect &rect, const Vector2 &external, Vector2 &point1, Vector2 &point2)
   {
      const Vector2 *corners = rect.GetAllCorners();

      // 1*------------*2
      //  |            |
      //  |            |
      // 0*------------*3

      if (external.x < rect.GetMinimum().x)
      {
         // left

         if (external.y < rect.GetMinimum().y)
         {
            // bottom left
            point1 = corners[3];
            point2 = corners[1];
         }
         else if (external.y <= rect.GetMaximum().y)
         {
            // left
            point1 = corners[0];
            point2 = corners[1];
         }
         else
         {
            // top left
            point1 = corners[2];
            point2 = corners[0];
         }
      }
      else if (external.x <= rect.GetMaximum().x)
      {
         // middle

         if (external.y < rect.GetMinimum().y)
         {
            // bottom
            point1 = corners[0];
            point2 = corners[3];
         }
         else if (external.y <= rect.GetMaximum().y)
         {
            // inside
            return 0;
         }
         else
         {
            // top
            point1 = corners[1];
            point2 = corners[2];
         }
      }
      else
      {
         // right

         if (external.y < rect.GetMinimum().y)
         {
            // bottom right
            point1 = corners[0];
            point2 = corners[2];
         }
         else if (external.y <= rect.GetMaximum().y)
         {
            // right
            point1 = corners[2];
            point2 = corners[3];
         }
         else
         {
            // top right
            point1 = corners[1];
            point2 = corners[3];
         }

      }
      return 2;
   }
}


//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
