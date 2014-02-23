#ifndef CLARITY_DIRECTION_H
#define CLARITY_DIRECTION_H

/** @file Direction.h
 *
 *  This file contains the Direction enumeration and related functions.
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
#include <cassert>

namespace Clarity
{
   /**
    * A compass direction.
    */
   enum Direction
   {
      EAST,       /**< East */
      SOUTH_EAST, /**< South East */
      SOUTH,      /**< South */
      SOUTH_WEST, /**< South West */
      WEST,       /**< West */
      NORTH_WEST, /**< North West */
      NORTH,      /**< North */
      NORTH_EAST  /**< North East */
   };

   /**
    * This table maps a direction to the next clockwise direction.
    */
   extern const Direction NEXT_DIRECTION_TABLE[];

   /**
    * This table maps a direction to the next anticlockwise direction.
    */
   extern const Direction PREV_DIRECTION_TABLE[];

   /**
    * This table maps a cardinal direction to the next clockwise cardinal 
    * direction.  The cardinal directions are EAST, SOUTH, WEST and NORTH.
    */
   extern const Direction NEXT_CARDINAL_DIRECTION_TABLE[];

   /**
    * This table maps a cardinal direction to the next anticlockwise cardinal 
    * direction.  The cardinal directions are EAST, SOUTH, WEST and NORTH.
    */
   extern const Direction PREV_CARDINAL_DIRECTION_TABLE[];

   /**
    * This table maps a direction to the next clockwise diagonal
    * direction.  The diagonal directions are SOUTH_EAST, SOUTH_WEST, 
    * NORTH_WEST and NORTH_EAST.
    */
   extern const Direction NEXT_DIAGONAL_DIRECTION_TABLE[];

   /**
    * This table maps a direction to the next anticlockwise diagonal 
    * direction.  The diagonal directions are SOUTH_EAST, SOUTH_WEST, 
    * NORTH_WEST and NORTH_EAST.
    */
   extern const Direction PREV_DIAGONAL_DIRECTION_TABLE[];

   /**
    * This table maps a direction to whether the direction is a cardinal 
    * direction.
    */
   extern const bool CARDINAL_DIRECTION_TABLE[];

   /**
    * This table maps a direction to a unit vector.
    */
   extern const Vector2 VECTOR_DIRECTION_TABLE[];

   /**
    * This table maps a direction to a vector such that the cardinal 
    * directions are unit length and the diagonal directions form the corners 
    * of a box around the origin.
    */
   extern const Vector2 VECTOR_BOX_DIRECTION_TABLE[];

   /**
    * Determine if a direction is valid.
    *
    * @returns Whether the direction is valid.
    */
    inline bool IsValidDirection(int direction)
   {
      return direction >= EAST && direction <= NORTH_EAST;
   }

   /**
    * Get the next direction clockwise to the supplied direction.
    *
    * @returns The next direction clockwise.
    */
    inline int NextDirection(int current)
   {
      assert(IsValidDirection(current));
      return NEXT_DIRECTION_TABLE[current];
   }

   /**
    * Get the next direction anticlockwise to the supplied direction.
    *
    * @returns The next direction anticlockwise.
    */
    inline int PrevDirection(int current)
   {
      assert(IsValidDirection(current));
      return PREV_DIRECTION_TABLE[current];
   }

   /**
    * Get the next cardinal direction clockwise to the supplied direction.
    *
    * @returns The next cardinal direction clockwise.
    */
    inline int NextCardinalDirection(int current)
   {
      assert(IsValidDirection(current));
      return NEXT_CARDINAL_DIRECTION_TABLE[current];
   }

   /**
    * Get the next cardinal direction anticlockwise to the supplied direction.
    *
    * @returns The next cardinal direction anitclockwise.
    */
    inline int PrevCardinalDirection(int current)
   {
      assert(IsValidDirection(current));
      return PREV_CARDINAL_DIRECTION_TABLE[current];
   }

   /**
    * Determine if the supplied direction is a cardinal direction.
    *
    * @returns True if the supplied direction is a cardinal direction.
    */
    inline bool IsCardinalDirection(int direction)
   {
      assert(IsValidDirection(direction));
      return CARDINAL_DIRECTION_TABLE[direction];
   }

   /**
    * Get the next diagonal direction clockwise to the supplied direction.
    *
    * @returns The next diagonal direction clockwise.
    */
    inline int NextDiagonalDirection(int current)
   {
      assert(IsValidDirection(current));
      return NEXT_DIAGONAL_DIRECTION_TABLE[current];
   }

   /**
    * Get the next diagonal direction anticlockwise to the supplied direction.
    *
    * @returns The next diagonal direction anitclockwise.
    */
    inline int PrevDiagonalDirection(int current)
   {
      assert(IsValidDirection(current));
      return PREV_DIAGONAL_DIRECTION_TABLE[current];
   }

   /**
    * Determine if the supplied direction is a diagonal direction.
    *
    * @returns True if the supplied direction is a diagonal direction.
    */
    inline bool IsDiagonalDirection(int direction)
   {
      assert(IsValidDirection(direction));
      return !CARDINAL_DIRECTION_TABLE[direction];
   }


   /**
    * Convert the supplied direction to a unit vector.
    *
    * @returns A unit vector corresponding to the supplied direction.
    */
    inline const Vector2 &DirectionToVector(int direction)
   {
      assert(IsValidDirection(direction));
      return VECTOR_DIRECTION_TABLE[direction];
   }

   /**
    * Convert the supplied direction to a vector such that the cardinal 
    * directions are unit length and the diagonal directions form the corners 
    * of a box around the origin.
    *
    * @returns 
    *    A vector in the direction supplied with length mapped to a box
    *    around the origin such that cardinal directions create vectors
    *    of unit length and diagonal vectors form the corners of the box.
    */
    inline const Vector2 &DirectionToBoxVector(int direction)
   {
      assert(IsValidDirection(direction));
      return VECTOR_BOX_DIRECTION_TABLE[direction];
   }

   /**
    * Returns the closest direction given a supplied vector.
    *
    * @returns 
    *    The direction closest to the supplied vector.
    */
    int ToDirection(const Vector2 &vector);

   /**
    * Returns the closest cardinal direction given a supplied vector.
    *
    * @returns 
    *    The cardinal direction closest to the supplied vector.
    */
    int ToCardinalDirection(const Vector2 &vector);

   /**
    * Get a string representing a given direction.
    *
    * @returns 
    *    A string representing the supplied direction.
    */
    const std::string &DirectionToString(int direction);

   /**
    * Returns a direction one step away from the current direction which is 
    * closer to the desired direction.  If the current direction is the 
    * desired direction or opposite to the desired direction, then the 
    * current direction is returned.
    *
    * @param current
    *    The current direction.
    * @param
    *    The desired direction.
    *
    * @returns 
    *    A direction one step away from current which is closer to desired.
    *
    * @see
    *    IsOppositeDirection()
    */
    int NextClosestDirection(int current, int desired);

   /**
    * Deterine whether two directions are opposite to each other.
    *
    * @param direction1
    *    The first direction to compare.
    * @param direction2
    *    The second direction to compare.
    *
    * @returns 
    *    Whether the two supplied directions are opposite to each other.
    */
    bool IsOppositeDirection(int direction1, int direction2);
}

#endif
