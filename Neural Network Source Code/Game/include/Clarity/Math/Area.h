#ifndef CLARITY_AREA_H
#define CLARITY_AREA_H

/** @file Area.h
 *
 *  This file contains the Area class definition.
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
   class Circle;
   class AARect;

   /**
    * A definition of an area independant of the location of that area.
    */
   class  Area
   {
   public:
      /**
       * The type of an area.
       */
      enum Type
      {
         TYPE_CIRCLE, /**< A circle area. */
         TYPE_RECT    /**< A rectangular area. */
      };

      /**
       * Construct a default area.  A default area is a circle of radius 1.
       *
       */
      Area();

      /**
       * Construct a circular area.
       *
       * @param radius
       *    The radius of the circle.
       */
      Area(float radius);

      /**
       * Construct a rectangular area.
       *
       * @param width
       *    The width of the rectangular area.
       * @param height
       *    The height of the rectangular area.
       */
      Area(float width, float height);

      /**
       * Get the type of area.
       *
       * @returns
       *    The type of the area.
       */
      Type GetType() const;

      /**
       * Get the minimum bounding radius of the area.
       *
       * @returns
       *    The minimum bounding radius of the area.
       */
      float GetRadius() const;

      /**
       * Get the bounding width of the area.
       *
       * @returns
       *    The bounding width of the area.
       */
      float GetWidth() const;

      /**
       * Get the bounding height of the area.
       *
       * @returns
       *    The bounding height of the area.
       */
      float GetHeight() const;

      /**
       * Set the area to be a circle.
       *
       * @param radius
       *    The radius of the circular area.
       */
      void Set(float radius);

      /**
       * Set the area to be an axis aligned rect.
       *
       * @param width
       *    The width of the rectangular area.
       * @param height
       *    The height of the rectangular area.
       */
      void Set(float width, float height);

      /**
       * Generate a circle from the bounds of the area and a given position.
       *
       * @param position
       *    This is the position of the new circle.
       *
       * @returns
       *    The circle bounding this area translated by the given position.
       */
      Circle MakeCircle(const Vector2 &position = Vector2::ZERO) const;

      /**
       * Generate a rectangle from the bounds of the area and a given position.
       *
       * @param position
       *    This is the position of the new rectangle.
       *
       * @returns
       *    The rectangle bounding this area translated by the given position.
       */      
      AARect MakeAARect(const Vector2 &position = Vector2::ZERO) const;

   private:
      Type m_type;
      float m_radius;
      float m_width;
      float m_height;
   };
}

#endif
