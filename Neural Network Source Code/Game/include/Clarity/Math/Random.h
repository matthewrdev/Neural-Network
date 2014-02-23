#ifndef CLARITY_RANDOM_H
#define CLARITY_RANDOM_H

/** @file Random.h
 *
 *  This file contains utility functions for generating random numbers.
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
#include <Clarity/Math/AABox.h>

namespace Clarity
{
   // ------------------------------------------------------------------------
   // RandFloat
   // ------------------------------------------------------------------------
   // Generate float between 0 and 1
   // ------------------------------------------------------------------------
   inline float RandFloat()
   {
      return ((float)rand()/RAND_MAX);
   }

   // ------------------------------------------------------------------------
   // RandFloatSigned
   // ------------------------------------------------------------------------
   // Generate float between -1 and 1
   // ------------------------------------------------------------------------
   inline float RandFloatSigned()
   {
      return ((float)rand()/RAND_MAX)*2.0f-1.0f;
   }

   // ------------------------------------------------------------------------
   // RandFloatRange
   // ------------------------------------------------------------------------
   // Generate float between min and max
   // ------------------------------------------------------------------------
   inline float RandFloatRange(float min, float max)
   {
      return RandFloat() * (max - min) + min;
   }

   // ------------------------------------------------------------------------
   // RandFloatRange
   // ------------------------------------------------------------------------
   // Rotate the supplied direction vector by a random angle between 
   // -halfAngle and +halfAngle.  The angle supplied is in radians.
   // ------------------------------------------------------------------------
    Vector2 RandomiseDirectionVector(const Vector2 &direction, float halfAngle);
}

#endif
