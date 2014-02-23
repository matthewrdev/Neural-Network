#ifndef CLARITY_AABOX_H
#define CLARITY_AABOX_H

/** @file AABox.h
 *
 *  This file contains the AABox class definition.
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
   class Plane;
   class Sphere;

   /**
    * This class represents a 3D box aligned with the x, y and z axes.
    *
	 * Internally it only stores 2 points as the extremeties of
	 * the box, one which is the minima of all 3 axes, and the other
	 * which is the maxima of all 3 axes. This class is typically used
	 * for an axis-aligned bounding box (AABB) for collision and
	 * visibility determination.
    */
   class  AABox
   {
   public:
      /**
       * Constructor
       */
      AABox();

      /**
       * Constructor
       *
       * @param min
       *    The corner of the box at the minimum extent of all three axes.
       * @param max
       *    The corner of the box at the maximum extent of all three axes.
       */
      AABox(const Vector3 &min, const Vector3 &max);

      /**
       * Constructor
       *
       * @param minX
       *    The minimum coordinate of the box along the x-axis.
       * @param minY
       *    The minimum coordinate of the box along the y-axis.
       * @param minZ
       *    The minimum coordinate of the box along the z-axis.
       * @param maxX
       *    The maximum coordinate of the box along the x-axis.
       * @param maxY
       *    The maximum coordinate of the box along the y-axis.
       * @param maxZ
       *    The maximum coordinate of the box along the z-axis.
       */
      AABox(
         float minX, float minY, float minZ,
         float maxX, float maxY, float maxZ);

      /**
       * Destructor
       */
      virtual ~AABox();

      /**
       * Get the corner of the box at the minimum of all three axes.
       *
       * @returns
       *    The corner of the box at the minimum of all three axes.
       */
      const Vector3 &GetMinimum() const;

      /**
       * Get the corner of the box at the maximum of all three axes.
       *
       * @returns
       *    The corner of the box at the maximum of all three axes.
       */
      const Vector3 &GetMaximum() const;

      /**
       * Set the corner of the box at the minimum of all three axes.
       *
       * @param vec
       *    The minimum corner of the box.
       */
      void SetMinimum(const Vector3 &vec);

      /**
       * Set the corner of the box at the minimum of all three axes.
       *
       * @param x
       *    The x coordinate of the minimum corner of the box.
       * @param y
       *    The y coordinate of the minimum corner of the box.
       * @param z
       *    The z coordinate of the minimum corner of the box.
       */
      void SetMinimum(float x, float y, float z);

      /**
       * Set the corner of the box at the maximum of all three axes.
       *
       * @param vec
       *    The maximum corner of the box.
       */
      void SetMaximum(const Vector3 &vec);

      /**
       * Set the corner of the box at the maximum of all three axes.
       *
       * @param x
       *    The x coordinate of the maximum corner of the box.
       * @param y
       *    The y coordinate of the maximum corner of the box.
       * @param z
       *    The z coordinate of the maximum corner of the box.
       */
      void SetMaximum(float x, float y, float z);

      /**
       * Set both minimum and maximum extents at once.
       *
       * @param min
       *    The minimum corner of the box.
       * @param max
       *    The maximum corner of the box.
       */
      void SetExtents(const Vector3 &min, const Vector3 &max);

      /**
       * Set both minimum and maximum extents at once.
       *
       * @param minX
       *    The x-coordinate of the minimum corner of the box.
       * @param minY
       *    The y-coordinate of the minimum corner of the box.
       * @param minZ
       *    The z-coordinate of the minimum corner of the box.
       * @param maxX
       *    The x-coordinate of the maximum corner of the box.
       * @param maxY
       *    The x-coordinate of the maximum corner of the box.
       * @param maxZ
       *    The x-coordinate of the maximum corner of the box.
       */
      void SetExtents(
         float minX, float minY, float minZ,
         float maxX, float maxY, float maxZ);

      /**
       * Get an array containing all 8 corner points.
       *
       * Having all corner points can be useful for collision with non-
       * aligned objects.
       *
       * If the order of these corners is important, they are as
       * follows: The 4 points of the minimum Z face (note that
       * because Ogre uses right-handed coordinates, the minimum Z is
       * at the 'back' of the box) starting with the minimum point of
       * all, then anticlockwise around this face (if you are looking
       * onto the face from outside the box). Then the 4 points of the
       * maximum Z face, starting with maximum point of all, then
       * anticlockwise around this face (looking onto the face from
       * outside the box). Like this:
       *
       * 1-----2
       * /|    /|
       * / |   / |
       * 5-----4  |
       * |  0--|--3
       * | /   | /
       * |/    |/
       * 6-----7
       *
       * @returns
       *    An array containing the 8 corner points of the box.
       */
      const Vector3* GetAllCorners() const;

      /**
      * Merges the passed in box into the current box. The result is the box 
      * which encompasses both.
      *
      * @param rhs
      *    The box to merge with the current box.
      */
      void Merge(const AABox &rhs);

      /** 
      * Extend the box to encompass the specified point (if needed).
      *
      * @param point
      *     The point to include within the volume of the box.
      */
      void Merge(const Vector3 &point);

       /**
       * Transforms the box according to the matrix supplied.
       * 
       * By calling this method you get the axis-aligned box which
       * surrounds the transformed version of this box. Therefore each
       * corner of the box is transformed by the matrix, then the
       * extents are mapped back onto the axes to produce another
       * AABB. Useful when you have a local AABB for an object which
       * is then transformed.
       *
       * @param matrix
       *    The matrix used to transform the the box.
       */
      void Transform(const Matrix4 &matrix);

      /**
       * Sets the box to a null value.  That is the box has zero volume.
       */
      void SetNull();

      /**
       * Determine if the box is null.  That is the box has zero volume.
       *
       * @returns 
       *    Whether the box is null.
       */
      bool IsNull() const;

      /**
       * Scales the box by the vector given.
       *
       * @param s
       *       The vector to scale the box by.
       */
      void Scale(const Vector3 &s);

      /**
       * Determine whether this box intersects another.
       *
       * @param b2
       *    The second box to test against this one for intersection.
       *
       * @returns
       *    Whether the supplied box intersects this box.
       */
      bool Intersects(const AABox &b2) const;

      /**
       * Test whether the vector defines a point within this box.
       *
       * @param v
       *    The vector to test against the box.
       *
       * @returns
       *    Whether the point defined by the supplied vector is contained 
       *    within the box.
       */
      bool Intersects(const Vector3 &v) const;

      /**
       * Get the centre of the box.
       *
       * @returns
       *    The centre of the box.
       */
      Vector3 GetCenter() const;

   private:
      void UpdateCorners();

      Vector3 m_minimum;
      Vector3 m_maximum;
      bool m_null;
      Vector3 m_corners[8];
   };

   /**
    * Output an axis aligned box to a stream.
    *
    * @param lhs
    *    The output stream.
    * @param rhs
    *    The box to write to the stream.
    */
   std::ostream &operator<<(std::ostream &lhs, const AABox &rhs);
}

#endif
