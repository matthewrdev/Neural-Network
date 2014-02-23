#ifndef CLARITY_CIRCLE_H
#define CLARITY_CIRCLE_H

/** @file Circle.h
 *
 *  This file contains the Circle class definition.
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
    * A circle primitive, mostly used for bounds checking. 
    *
    * A circle in math texts is normally represented by the function
    * x^2 + y^2 = r^2 (for circle's centered on the origin). Clarity
    * stores circles simply as a centre point and a radius.
    */
   class  Circle
   {
   public:
      /**
       * Construct unit circle around the origin.
       */
      Circle();

      /**
       * Construct a circle defined by a given centre and radius.
       *
       * @param centre 
       *    The centre point of the circle.
       * @param radius 
       *    The radius of the circle.
       */
      Circle(const Vector2 &centre, float radius);

      /**
       * Get the radius of the circle.
       *
       * @returns
       *    The radius of the circle.
       */
      float GetRadius() const;

      /**
       * Set the radius of the circle.
       * 
       * @param radius
       *    The radius of the circle.
       */
      void SetRadius(float radius);

      /**
       * Returns the centre point of the circle.
       *
       * @returns
       *    The centre of the circle.
       */
      const Vector2 &GetCentre() const;

      /**
       * Sets the centre point of the circle.
       *
       * @param centre
       *    The centre of the circle.
       */
      void SetCentre(const Vector2 &centre);

   private:
      float m_radius;
      Vector2 m_centre;
   };

}

#endif
