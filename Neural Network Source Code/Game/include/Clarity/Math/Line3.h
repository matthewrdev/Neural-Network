#ifndef CLARITY_LINE3_H
#define CLARITY_LINE3_H

/** @file Line3.h
 *
 *  This file contains the Line3 class definition.
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


#include <Clarity/Math/Vector3.h>

namespace Clarity
{
   /**
   * This class represents a line in 3D space.
   */
   class  Line3
   {
   public:
      /**
       * Construct a default line segment.  The default line will use the unit 
       * y vector as a normal and have a distance of 0.  Thus it represents 
       * the x-axis.
       */
      Line3();

      /**
       * Construct a line segment from a normal and distance from the origin 
       * to the line along the normal.
       * 
       * @param normal
       *    A vector normal to the line.
       * @param distance
       *    The distance from the origin to the line along the normal.
       */
      Line3(const Vector3 &normal, float distance);

      /**
       * Construct a line segment from two points on the line.  The points may
       * not be the same.  The line will be in the direction from tail to 
       * head.
       * 
       * @param tail
       *    The tail end point of the line segment.
       * @param head
       *    The head end point of the line segment.
       */
      Line3(const Vector3 &tail, const Vector3 &head);

      /**
       * Set a line segment from a normal and distance from the origin to the 
       * line along the normal.
       * 
       * @param normal
       *    A vector normal to the line.
       * @param distance
       *    The distance from the origin to the line along the normal.
       */
      void FromNormalDistance(const Vector3 &normal, float distance);

      /**
       * Set a line segment from two points on the line.  The points may not 
       * be the same.  The line will be in the direction from tail to head.
       * 
       * @param tail
       *    The tail end point of the line segment.
       * @param head
       *    The head end point of the line segment.
       */
      void FromPoints(const Vector3 &tail, const Vector3 &head);

      /**
       * Destructor.
       */
      ~Line3();

      /**
       * Get the unit vector parallel to the line.
       *
       * @returns
       *    The unit vector parallel to the line.
       */
      const Vector3 &GetDirection() const;

      /**
       * Get the normal to the line.
       *
       * @returns
       *    The normal to the line.
       */
      const Vector3 &GetNormal() const;

      /**
       * Get the distance from the origin to the line along the normal.
       *
       * @returns
       *    The distance from the origin to the line along the normal.
       */
      float GetDistance() const;

      /**
       * Get the slope (rise/run) of the line.
       *
       * @returns
       *    The slope of the line.
       */
      float GetSlope() const;

      /**
       * Calculate the shortest distance from this line to point.
       *
       * @param point
       *    Caculate the shortest distance from this point to the line.
       * 
       * @returns
       *    The shortest distance from the supplied point to the line.
       */
      float DistanceToPoint(const Vector3 &point) const;

      /**
       * Calculate the shortest distance from this line to point.
       *
       * @param lineNormal
       *    A unit vector normal to the line
       * @param lineDistance
       *    The distance along the perpendicular to the origin.
       * @param point
       *    Calculate the shortest distance from the supplied line to this point.
       *
       * @returns
       *    The shortest distance from the supplied line to the supplied point.
       */
      static float DistanceToPoint(
         const Vector3 &lineNormal, 
         float lineDistance, 
         const Vector3 &point);

   private:
      Vector3 m_normal;
      float m_distance;

      mutable Vector3 m_direction;
      mutable bool m_directionDirty;
   };
}

#endif
