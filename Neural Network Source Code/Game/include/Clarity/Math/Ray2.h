#ifndef CLARITY_RAY2_H
#define CLARITY_RAY2_H

/** @file Ray2.h
 *
 *  This file contains the Ray2 class definition.
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

#include <Clarity/Math/Vector2.h>
#include <iosfwd>

namespace Clarity
{
   class Circle;
   class AARect;

   // ========================================================================
   // Ray2
   // ========================================================================
   // ========================================================================
   class  Ray2
   {
   public:
      // ---------------------------------------------------------------------
      // Ray2
      // ---------------------------------------------------------------------
      // Construct a ray.
      // 
      // origin
      //    The origin of the ray.
      // direction
      //    The direction of the ray.
      // ---------------------------------------------------------------------
      Ray2(const Vector2 &origin, const Vector2 &direction);

      // ---------------------------------------------------------------------
      // ~Ray2
      // ---------------------------------------------------------------------
      // Destruct a ray.
      // ---------------------------------------------------------------------
      /* virtual */ ~Ray2();

      // ---------------------------------------------------------------------
      // GetOrigin
      // ---------------------------------------------------------------------
      // Get the origin of the ray.
      // ---------------------------------------------------------------------
      const Vector2 &GetOrigin() const;

      // ---------------------------------------------------------------------
      // GetDirection
      // ---------------------------------------------------------------------
      // Get the direction of the ray.
      // ---------------------------------------------------------------------
      const Vector2 &GetDirection() const;

      // ---------------------------------------------------------------------
      // Transform
      // ---------------------------------------------------------------------
      // Transform this ray by the given matrix to generate a new 
      // ray.
      // ---------------------------------------------------------------------
      Ray2 Transform(const Matrix3 &transform) const;

      // ---------------------------------------------------------------------
      // GetPoint
      // ---------------------------------------------------------------------
		// Gets the position of a point t units along the ray.
      // ---------------------------------------------------------------------
		Vector2 GetPoint(float t) const;

      // ---------------------------------------------------------------------
      // Set
      // ---------------------------------------------------------------------
      // Set the origin and direction of the ray.
      // ---------------------------------------------------------------------
      void Set(const Vector2 &origin, const Vector2 &direction);

   private:
      Vector2 m_origin;
      Vector2 m_direction;
   };

    Vector2 operator*(const Ray2 &ray, float distance);
    Vector2 operator*(float distance, const Ray2 &ray);

    std::ostream &operator<<(std::ostream &os, const Ray2 &rhs);
}

#endif
