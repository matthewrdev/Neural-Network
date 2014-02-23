#ifndef CLARITY_AARECT_H
#define CLARITY_AARECT_H

/** @file AARect.h
 *
 *  This file contains the AARect class definition.
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
    * This class represents a rectangle aligned with the x and y axes.
    *
	 * Internally it only stores 2 points as the extremeties of
	 * the rectangle, one which is the minima both axes, and the other
	 * which is the maxima of 2 axes. This class is typically used
	 * for an axis-aligned bounding rect for collision and visibility 
    * determination.
    *
    * Rectangles can be null.  A null rectangle is invalid.  It can be 
    * thought of as a rectangle with no area.
    */
   class  AARect
   {
   public:
      /**
       * Construct a default unit size rectangle around the origin.
       */
      AARect();

      /**
       * Construct a rectangle from minimum and maximum extents.
       *
       * @param min
       *    The minimum corner of the rectangle.
       * @param max
       *    The maximum corner of the rectangle.
       */
      AARect(const Vector2 &min, const Vector2 &max);

      /**
       * Construct a rectangle from minimum and maximum extents.
       *
       * @param minX
       *    The x component of the minimum corner of the rectangle.
       * @param minY
       *    The y component of the minimum corner of the rectangle.
       * @param maxX
       *    The x component of the maximum corner of the rectangle.
       * @param maxY
       *    The y component of the maximum corner of the rectangle.
       */
      AARect(
         float minX, float minY,
         float maxX, float maxY);

      /**
       * Construct a rectangle of a specified size around the origin.
       *
       * @param size
       *    The size of the rectangle.
       */
      AARect(const Vector2 &size);

      /**
       * Destructor.
       */
      ~AARect();

      /**
       * Get the minimum corner of the rectangle.
       *
       * @returns
       *    The minimum corner of the rectangle.
       */
      const Vector2 &GetMinimum() const;

      /**
       * Get the maximum corner of the rectangle.
       *
       * @returns
       *    The maximum corner of the rectangle.
       */
      const Vector2 &GetMaximum() const;

      /**
       * Gets the size of the rectangle.
       *
       * @returns
       *    A vector where the axes represent the width and height.
       */
      Vector2 GetSize() const;

      /**
       * Gets the width of the rectangle.
       *
       * @returns
       *    The width of the rectangle.
       */
      float GetWidth() const;

      /**
       * Gets the height of the rectangle.
       *
       * @returns
       *    The height of the rectangle.
       */
      float GetHeight() const;

      /**
       * Sets the minimum corner of the rectangle.
       *
       * @param vec
       *    A vector defining the minimum corner of the rectangle.
       */
      void SetMinimum(const Vector2 &vec);

      /**
       * Sets the minimum corner of the rectangle.
       *
       * @param x
       *    The x component of the minimum corner of the rectangle.
       * @param y
       *    The y component of the minimum corner of the rectangle.
       */
      void SetMinimum(float x, float y);

      /**
       * Sets the maximum corner of the rectangle.
       *
       * @param vec
       *    A vector defining the maximum corner of the rectangle.
       */
      void SetMaximum(const Vector2 &vec);

      /**
       * Sets the maximum corner of the rectangle.
       *
       * @param x
       *    The x component of the maximum corner of the rectangle.
       * @param y
       *    The y component of the maximum corner of the rectangle.
       */
      void SetMaximum(float x, float y);

      /**
       * Sets the minimum and maximum extents of the rectangle.
       *
       * @param min
       *    The minimum corner of the box.
       * @param max
       *    The maximum corner of the box.
       */
      void SetExtents(const Vector2 &min, const Vector2 &max);

      /**
       * Sets the minimum and maximum extents of the rectangle.
       *
       * @param minX
       *    The x component of the minimum corner of the box.
       * @param minY
       *    The y component of the minimum corner of the box.
       * @param maxX
       *    The x component of the maximum corner of the box.
       * @param maxY
       *    The y component of the maximum corner of the box.
       */
      void SetExtents(
         float minX, float minY,
         float maxX, float maxY);

      /**
       * Sets the minimum and maximum extents of the rectangle.
       *
       * @param minX
       *    The x component of the minimum corner of the box.
       * @param minY
       *    The y component of the minimum corner of the box.
       * @param maxX
       *    The x component of the maximum corner of the box.
       * @param maxY
       *    The y component of the maximum corner of the box.
       */

      /**
       * Get an array containing the coordinates of all 4 corners of the 
       * rectangle.  The corners are useful for collision vs. non-aligned 
       * objects.
       *
       * The order of these items is: starting with Min(all), then 
       * clockwise around face (looking onto the face).
       *
       * @returns
       *    A pointer to an array of 4 vectors which store the corners.
       */
      const Vector2* GetAllCorners() const;

      /**
       * Merges the passed in rectangle into the current rectangle. The result 
       * is the rectangle which encompasses both.
       *
       * @param rhs
       *    The rectangle to merge with this rectangle.
       */
      void Merge(const AARect &rhs);

      /**
       * Extends the rectangle to encompass the specified point (if needed).
       *
       * @param point
       *    The point which to include in the area of the rectangle.
       */
      void Merge(const Vector2 &point);

      /**
       * Transforms the rectangle according to the matrix supplied.
       * 
       * By calling this method you get the axis-aligned rectangle which
       * surrounds the transformed version of this rectangle. Therefore each
       * corner of the rectangle is transformed by the matrix, then the
       * extents are mapped back onto the axes to produce another
       * AABR. Useful when you have a local AABR for an object which
       * is then transformed.
       *
       * @param matrix
       *    The matrix used to transform the rectangle.
       */
      void Transform(const Matrix3 &matrix);

      /**
       * Transforms the rectangle according to the translation supplied.
       *
       * @param translation
       *    The translation used to translate the rectangle.
       */
      void Translate(const Vector2 &translation);

      /**
       * Sets the rectangle to a null value.
       */
      void SetNull();

      /**
       * Determine if this rectangle is null.
       *
       * @returns
       *    Whether the rectangle is null.
       */
      bool IsNull() const;

      /**
       * Scale the rectangle.
       *
       * @param s
       *    The components of this vector represent how much to scale the 
       *    rectangle along each axis.
       */
      void Scale(const Vector2 &s);

      /**
       * Returns whether or not the area of this rectangle is a subset of the
       * area of the supplied rectangle.  
       *
       * @param rhs
       *    This parameter is used as the possible containing rectangle.
       *
       * @returns
       *    Returns true if the area defined by this rectangle is fully 
       *    overlapped by rhs.
       */
      bool IsSubsetOfRect(const AARect &rhs) const;

      /**
       * Get a vector indicating the point which is the centre of the 
       * rectangle.
       *
       * @returns
       *    A vector indicating the point which is the centre of the 
       *    rectangle.
       */
      Vector2 GetCenter() const;

   private:
      void UpdateCorners();
      Vector2 m_minimum;
      Vector2 m_maximum;
      bool m_null;
      Vector2 m_corners[4];
   };

   /**
    * Print an axis aligned rectangle to a stream.
    *
    * @param lhs
    *    The stream to output the rectangle to.
    * @param rhs
    *    The rectangle to output to the stream.
    */
   std::ostream &operator<<(std::ostream &lhs, const AARect &rhs);
}

#endif
