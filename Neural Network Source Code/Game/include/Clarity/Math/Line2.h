#ifndef CLARITY_LINE2_H
#define CLARITY_LINE2_H

/** @file Line2.h
*
*  This file contains the Line2 class definition.
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

namespace Clarity
{
   /**
   * This class represents a line in 2D space.
   */
   class  Line2
   {
   public:
      /**
      * Construct a default line segment.  The default line will use the unit 
      * y vector as a normal and have a distance of 0.  Thus it represents 
      * the x-axis.
      */
      Line2();

      /**
      * Construct a line from a normal and distance from the origin 
      * to the line along the normal.
      *
      * @param normal
      *   A vector normal to the line.
      * @param distance
      *   The distance from the origin to the line along the normal.
      */
      Line2(const Vector2 &normal, float distance);

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
      Line2(const Vector2 &tail, const Vector2 &head);

      /**
      * Set a line segment from a normal and distance from the origin to the 
      * line along the normal.
      *
      * @param normal
      *   A vector normal to the line.
      * @param distance
      *   The distance from the origin to the line along the normal.
      */
      void FromNormalDistance(const Vector2 &normal, float distance);

      /**
      * Set a line segment from two points on the line.  The points may not 
      * be the same.  The line will be in the direction from tail to head.
      *
      * @param tail
      *     The tail end point of the line segment.
      * @param head
      *     The head end point of the line segment.
      */
      void FromPoints(const Vector2 &tail, const Vector2 &head);

      /**
      * Destructor.
      */
      ~Line2();

      /**
      * Get a unit vector in the direction of the line.
      *
      * @returns
      *     A unit vector in the direction of the line.
      */
      const Vector2 &GetDirection() const;

      /**
      * Get a unit vector normal to the line.
      *
      * @returns
      *     A unit vector normal to the line.
      */
      const Vector2 &GetNormal() const;

      /**
      * Get the distance from the origin to the line along the normal.
      *
      * @returns the distance from the origin to the line along the normal.
      */
      float GetDistance() const;

      /**
      * Get the slope (rise/run) of the line.
      *
      * @returns
      *     The slope of the line.
      */
      float GetSlope() const;

      /**
      * Calculate the shortest distance from this line to the supplied point.
      *
      * @param point
      *     Calculate the shortest distance from this point to the line.
      *
      * @returns
      *     The shortest distance from the supplied point to the line.
      */
      float DistanceToPoint(const Vector2 &point) const;

      /**
      * Calculate the shortest distance from a line to a point.
      *
      * @param lineNormal
      *     A unit vector normal to the line
      * @param lineDistance
      *     The distance from the line to the origin along the normal.
      * @param point
      *     Calculate the shortest distance from this point to the line.
      *
      * @returns
      *     The shortest distance from the given line to the given point.
      */
      static float DistanceToPoint(
         const Vector2 &lineNormal, 
         float lineDistance, 
         const Vector2 &point);

   private:
      Vector2 m_normal;
      float m_distance;

      mutable Vector2 m_direction;
      mutable bool m_directionDirty;
   };
}

#endif
