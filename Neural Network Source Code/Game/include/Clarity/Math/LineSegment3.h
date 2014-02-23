#ifndef CLARITY_LINESEGMENT3_H
#define CLARITY_LINESEGMENT3_H

/** @file LineSegment3.h
 *
 *  This file contains the LineSegment3 class definition.
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
#include <Clarity/Math/Line3.h>
#include <iosfwd>

namespace Clarity
{
   class LineSegment2;

   /**
    * This class represents a line segment in 3D space.
    */
   class  LineSegment3
   {
   public:
      /**
       * Construct a line segment.
       * 
       * @param tail
       *    The tail end point of the line segment.
       * @param head
       *    The head end point of the line segment.
       */
      LineSegment3(const Vector3 &tail, const Vector3 &head);

      /**
       * Construct a line segment from a 2D line segment.
       *
       * @param lineSegment
       *    The 2D line segment from which to construct the 3D line segment.
       * @param tailZ
       *    The z coordinate of the tail of the new 3D line segment.
       * @param headZ
       *    The z coordinate of the head of the new 3D line segment.
       */
      LineSegment3(const LineSegment2 &lineSegment2, float tailZ, float headZ);

      /**
       * Destructor.
       */
      ~LineSegment3();

      /**
       * Get the tail end point of the line segment.
       *
       * @returns
       *    The tail end point of the line segment.
       */
      const Vector3 &GetTail() const;

      /**
       * Get the head end point of the line segment.
       *
       * @returns 
       *    The head end point of the line segment.
       */
      const Vector3 &GetHead() const;

      /**
       * Get a vector from the tail to the head.
       *
       * @returns
       *    A vector from the tail to the head of the line segment.
       */
      const Vector3 &GetVector() const;

      /**
       * Get a unit vector in the direction from the tail to the head.
       *
       * @returns
       *    A unit vector in the direction from the tail to the head.
       */
      const Vector3 &GetDirection() const;

      /**
       * Get a vector normal to this line segment.
       *
       * @returns
       *    A vector normal to this line segment.
       */
      const Vector3 &GetNormal() const;

      /**
       * Get the length of the line segement.
       *
       * @returns
       *    The length of the line segment.
       */
      float GetLength() const;

      /**
       * Get the squared length of the line segement.  Faster than get length
       * and can be used to compare relative lengths.
       *
       * @returns
       *    The squared length of the line segment.
       */
      float GetLengthSquared() const;

      /**
       * Find the mid point of the line segment.
       *
       * @returns
       *    A vector representing the point that is the mid point of the line 
       *    segment.
       */
      Vector3 Midpoint() const;

      /**
       * Transform this line segment by the given matrix to generate a new 
       * line segment.
       *
       * @param transform
       *    The matrix used to transform the line segment.
       *
       * @returns
       *    A transformed copy of the line segment.
       */
      LineSegment3 Transform(const Matrix4 &transform) const;

      /**
       * Set the tail and head end points of the line segment.
       *
       * @param tail
       *    The tail of the line segment.
       * @param head
       *    The head of the line segment.
       */
      void Set(const Vector3 &tail, const Vector3 &head);

      /**
       * Get the line that this segment lies on.
       *
       * @returns
       *    The line that this line segment lies on.
       */
      const Line3 &GetLine() const;

      /**
       * Finds a point on the line segment closer than any other point on the 
       * line segment to startingPoint.
       *
       * @param startingPoint
       *    Find the point on the line segment nearest to this point.
       *
       * @returns
       *    The point on the line segment nearest the starting point.
       */
      Vector3 FindNearestPoint(const Vector3 &startingPoint) const;

      /**
       * Returns the closest point on the line segment to a given displacement
       * where the tail of the line is displacement zero and the head is the
       * length of the line.  Note that the displacement will always be on the
       * line but not necessarily within the bounds of the line segment.
       *
       * @param displacement
       *    The displacement along the line.
       *
       * @returns
       *    A vector representing the point on the line that is displacment 
       *    units away from the tail.
       */
      Vector3 GetClosestPointFromDisplacement(float displacement) const;

   private:
      void MarkAsDirty() const;

      Vector3 m_tail;
      Vector3 m_head;

      mutable Line3 m_line;
      mutable bool m_lineDirty;

      mutable float m_length;
      mutable bool m_lengthDirty;

      mutable float m_lengthSquared;
      mutable bool m_lengthSquaredDirty;

      mutable Vector3 m_vector;
      mutable bool m_vectorDirty;
   };

   /**
   * Output a 3D line segment to a stream.
   *
   * @param os
   *     Write the line segment to this output stream.
   * @param rhs
   *     Write this line segment to the output stream.
   *
   * @returns
   *     The supplied output stream.
   */
    std::ostream &operator<<(std::ostream &os, const LineSegment3 &rhs);
}

#endif
