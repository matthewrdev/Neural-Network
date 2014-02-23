#ifndef CLARITY_VECTOR4_H
#define CLARITY_VECTOR4_H

/** @file Vector4.h
 *
 *  This file contains the Vector4 class definition.
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


#include <iostream>

namespace Clarity
{
   struct Vector3;
   class Matrix3;
   class Matrix4;

   // ========================================================================
   // Vector4
   // ========================================================================
   // ========================================================================
   struct  Vector4
   {
      // ---------------------------------------------------------------------
      // Components
      // ---------------------------------------------------------------------
      // Vector4 is considered a basic type so exposing the data members is
      // condidered an acceptable violation of encapsulation.
      // ---------------------------------------------------------------------
      float x, y, z, w;

      // ---------------------------------------------------------------------
      // Constants
      // ---------------------------------------------------------------------
      // ZERO
      //    x = 0, y = 0, z = 0
      // UNIT_X
      //    x = 1, y = 0, z = 0
      // UNIT_Y
      //    x = 0, y = 1, z = 0
      // UNIT_Z
      //    x = 0, y = 0, z = 1
      // NEGATIVE_UNIT_X
      //    x = -1, y = 0, z = 0
      // NEGATIVE_UNIT_Y
      //    x = 0, y = -1, z = 0
      // NEGATIVE_UNIT_Z
      //    x = 0, y = 0, z = -1
      // UNIT_SCALE
      //    x = 1, y = 1, z = 1
      // ---------------------------------------------------------------------
      static const Vector4 ZERO;

      // ---------------------------------------------------------------------
      // Vector4
      // ---------------------------------------------------------------------
      // Construct a Vector4.
      // ---------------------------------------------------------------------
      Vector4();
      Vector4(float xIn, float yIn, float zIn, float wIn);
      explicit Vector4(const Vector3 &vector3);

      // ---------------------------------------------------------------------
      // ~Vector4
      // ---------------------------------------------------------------------
      // Destruct a Vector4.
      // ---------------------------------------------------------------------
      ~Vector4();

      // ---------------------------------------------------------------------
      // opeator[](int)
      // ---------------------------------------------------------------------
      // Access a vector element using subscript notation.
      // ---------------------------------------------------------------------
      float operator[](int idx) const;
      float &operator[](int idx);

      // ---------------------------------------------------------------------
      // Set
      // ---------------------------------------------------------------------
      // Set a Vector4 object from component parts.
      // ---------------------------------------------------------------------
      void Set(float xIn, float yIn, float zIn, float wIn);

      // ---------------------------------------------------------------------
      // operator=(Vector3)
      // ---------------------------------------------------------------------
      // Assign a Vector3 to this vector 4.  w is given the value 1.
      // ---------------------------------------------------------------------
      Vector4 &operator=(const Vector3 &vector3);

      // ---------------------------------------------------------------------
      // Transform(Matrix4)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied.
      // ---------------------------------------------------------------------
      Vector4 Transform(const Matrix4 &lhs) const;
   };

   // ---------------------------------------------------------------------
   // ostream<<(Vector4)
   // ---------------------------------------------------------------------
   // Output to a stream.
   // ---------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &lhs, const Vector4 &rhs);
}

#endif
