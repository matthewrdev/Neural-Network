#ifndef CLARITY_VECTOR2_H
#define CLARITY_VECTOR2_H


/** @file Vector2.h
 *
 *  This file contains the Vector2 class definition.
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
   class Matrix2;
   class Matrix3;

   // ========================================================================
   // Vector2
   // ========================================================================
   // ========================================================================
   struct  Vector2
   {
      // ---------------------------------------------------------------------
      // ProjectionMode
      // ---------------------------------------------------------------------
      // An enumerated type used to specified how to convert from a 3D vector
      // to a 2D vector.
      //
      // PROJECTION_MODE_FROM_HOMOGENEOUS
      //    The 3D vector is in homogeneous coordinates.
      // PROJECTION_MODE_ORTHOGRAPHIC
      //    The 3D vector is in Euclidean space and we want to drop the z
      //    component to do a simple orthographic projection.
      // ---------------------------------------------------------------------
      enum ProjectionMode
      {
         PROJECTION_MODE_FROM_HOMOGENEOUS,
         PROJECTION_MODE_ORTHOGRAPHIC
      };

      // ---------------------------------------------------------------------
      // Components
      // ---------------------------------------------------------------------
      // Vector2 is considered a basic type so exposing the data members is
      // condidered an acceptable violation of encapsulation.
      // ---------------------------------------------------------------------
      float x, y;

      // ---------------------------------------------------------------------
      // Constants
      // ---------------------------------------------------------------------
      // ZERO
      //    x = 0, y = 0
      // UNIT_X
      //    x = 1, y = 0
      // UNIT_Y
      //    x = 0, y = 1
      // NEGATIVE_UNIT_X
      //    x = -1, y = 0
      // NEGATIVE_UNIT_Y
      //    x = 0, y = -1
      // UNIT_SCALE
      //    x = 1, y = 1
      // ---------------------------------------------------------------------
      static const Vector2 ZERO;
      static const Vector2 UNIT_X;
      static const Vector2 UNIT_Y;
      static const Vector2 NEGATIVE_UNIT_X;
      static const Vector2 NEGATIVE_UNIT_Y;
      static const Vector2 UNIT_SCALE;

      // ---------------------------------------------------------------------
      // Vector2
      // ---------------------------------------------------------------------
      // Default constructor.  Elements set to the zero vector.
      // ---------------------------------------------------------------------
      Vector2();

      // ---------------------------------------------------------------------
      // Vector2
      // ---------------------------------------------------------------------
      // Construct a 2d vector from its elements.
      // ---------------------------------------------------------------------
      Vector2(float xIn, float yIn);

      // ---------------------------------------------------------------------
      // Vector2
      // ---------------------------------------------------------------------
      // Construct a 2d vector from a 3d vector.
      //
      // homogeneous
      //    Peforms a projection from homegenous coordinates if this parameter
      //    is true.  x' = x/z, y' = y/z.  In this case, z cannot be zero.
      //    If this value is false, the z component is merely dropped.
      // ---------------------------------------------------------------------
      Vector2(const Vector3 &rhs, ProjectionMode projectionMode);

      // ---------------------------------------------------------------------
      // ~Vector2
      // ---------------------------------------------------------------------
      // Destruct a Vector2.
      // ---------------------------------------------------------------------
      ~Vector2();

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
      // Set a Vector2 object from component parts.
      // ---------------------------------------------------------------------
      void Set(float xIn, float yIn);

      // ---------------------------------------------------------------------
      // operator*=(Vector2)
      // ---------------------------------------------------------------------
      // Perform a componentwise multiply assignment.
      // ---------------------------------------------------------------------
      Vector2 &operator*=(const Vector2 &rhs);

      // ---------------------------------------------------------------------
      // operator/=(Vector2)
      // ---------------------------------------------------------------------
      // Perform a componentwise division assignment.
      //
      // PRE: rhs.x != 0 && rhs.y != 0 && rhs.z != 0
      // ---------------------------------------------------------------------
      Vector2 &operator/=(const Vector2 &rhs);

      // ---------------------------------------------------------------------
      // operator+=(Vector2)
      // ---------------------------------------------------------------------
      // Perform a componentwise addition assignment.
      // ---------------------------------------------------------------------
      Vector2 &operator+=(const Vector2 &rhs);

      // ---------------------------------------------------------------------
      // operator-=(Vector2)
      // ---------------------------------------------------------------------
      // Perform a componentwise subtraction assignment.
      // ---------------------------------------------------------------------
      Vector2 &operator-=(const Vector2 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(float)
      // ---------------------------------------------------------------------
      // Multiply assign the vector by a scalar.
      // ---------------------------------------------------------------------
      Vector2 &operator*=(float rhs);

      // ---------------------------------------------------------------------
      // operator/=(float)
      // ---------------------------------------------------------------------
      // Divide assign the vector by a scalar.
      //
      // PRE: rhs != 0
      // ---------------------------------------------------------------------
      Vector2 &operator/=(float rhs);

      // ---------------------------------------------------------------------
      // Transform(Matrix2)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied.
      // ---------------------------------------------------------------------
      Vector2 Transform(const Matrix2 &lhs) const;

      // ---------------------------------------------------------------------
      // Transform(Matrix3)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied, projecting the result 
      // back into w = 1.
      //
      // This means that the initial w is considered to be 1.0, and then all 
      // the two elements of the resulting 2-D vector are divided by the 
      // resulting w.
      // ---------------------------------------------------------------------
      Vector2 Transform(const Matrix3 &lhs) const;

      // ---------------------------------------------------------------------
      // TransformVector(Matrix3)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied but only uses the 
      // rotation/scale elements of the matrix, not the translation.
      // ---------------------------------------------------------------------
      Vector2 TransformVector(const Matrix3 &lhs) const;

      // ---------------------------------------------------------------------
      // Magnitude
      // ---------------------------------------------------------------------
      // Returns the length (magnitude) of the vector.
      // This operation requires a square root and is expensive in
      // terms of CPU operations. If you don't need to know the exact
      // length (e.g. for just comparing lengths) use MagnitudeSquared()
      // instead.
      // ---------------------------------------------------------------------
      float Magnitude() const;

      // ---------------------------------------------------------------------
      // MagnitudeSquared
      // ---------------------------------------------------------------------
      // Returns the square of the length(magnitude) of the vector.
      // This  method is for efficiency - calculating the actual
      // length of a vector requires a square root, which is expensive
      // in terms of the operations required. This method returns the
      // square of the length of the vector, i.e. the same as the
      // length but before the square root is taken. Use this if you
      // want to find the longest / shortest vector without incurring
      // the square root.
      // ---------------------------------------------------------------------
      float MagnitudeSquared() const;

      // ---------------------------------------------------------------------
      // IsZeroMagnitude
      // ---------------------------------------------------------------------
      // Returns true if this vector is zero length.
      // ---------------------------------------------------------------------
      bool IsZeroMagnitude() const;

      // ---------------------------------------------------------------------
      // Normalise
      // ---------------------------------------------------------------------
      // Normalises the vector.
      //
      // This method normalises the vector such that it's
      // length / magnitude is 1. The result is called a unit vector.
      //
      // This function will not crash for zero-sized vectors, but there
      // will be no changes made to their components.
      //
      // RETURNS
      //    The previous length of the vector.
      // ---------------------------------------------------------------------
      float Normalise();

      // ---------------------------------------------------------------------
      // MakeFloor
      // ---------------------------------------------------------------------
      // Sets this vector's components to the minimum of its own and the ones 
      // of the passed in vector.
      //
      // 'Minimum' in this case means the combination of the lowest value of 
      // x and y from both vectors. Lowest is taken just numerically, not 
      // magnitude, so -1 < 0.
      // ---------------------------------------------------------------------
      void MakeFloor(const Vector2 &cmp);

      // ---------------------------------------------------------------------
      // MakeCeil
      // ---------------------------------------------------------------------
      // Sets this vector's components to the maximum of its own and the ones 
      // of the passed in vector.
      //
      // 'Maximum' in this case means the combination of the highest value of 
      // x and y from both vectors. Highest is taken just numerically, not 
      // magnitude, so 1 > -3.
      // ---------------------------------------------------------------------
      void MakeCeil(const Vector2 &cmp);

      // ---------------------------------------------------------------------
      // DotProduct
      // ---------------------------------------------------------------------
      // Calculates the dot (scalar) product of two vectors.
      //
      // The dot product can be used to calculate the angle between 2
      // vectors. If both are unit vectors, the dot product is the
      // cosine of the angle; otherwise the dot product must be
      // divided by the product of the lengths of both vectors to get
      // the cosine of the angle. This result can further be used to
      // calculate the distance of a point from a plane.
      // 
      // RETURNS
      //    A float representing the dot product value.
      // ---------------------------------------------------------------------
      static float DotProduct(const Vector2 &lhs, const Vector2 &rhs);

      // ---------------------------------------------------------------------
      // Lerp
      // ---------------------------------------------------------------------
      // Perform a linear interpolation between two vectors.
      //
      // from
      //    Interpolate from this vector.
      // to
      //    Interpolate to this vector.
      // t
      //    The percentage of the way between the two vectors.  Zero is 
      //    equivalent to the from vector. One is equivalent to the to vector
      //    Values outside the range 0.0f to 1.0f are allowed.
      // ---------------------------------------------------------------------
      static Vector2 Lerp(const Vector2 &from, const Vector2 &to, float t);
   };


   // ---------------------------------------------------------------------
   // Per Element Arithmetic Operations
   // ---------------------------------------------------------------------
    Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
    Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
    Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs);
    Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs);

    Vector2 operator*(const Vector2 &lhs, float rhs);
    Vector2 operator/(const Vector2 &lhs, float rhs);

    Vector2 operator*(float lhs, const Vector2 &rhs);
    Vector2 operator/(float lhs, const Vector2 &rhs);

    Vector2 operator-(const Vector2 &op);

   // ---------------------------------------------------------------------
   // Per Element Equality Operations
   // ---------------------------------------------------------------------
    bool operator==(const Vector2 &lhs, const Vector2 &rhs);
    bool operator!=(const Vector2 &lhs, const Vector2 &rhs);

   // ---------------------------------------------------------------------
   // Perp
   // ---------------------------------------------------------------------
   // Obtain a vector perpendicular to the given vector.
   //
   // RETURNS
   //    Vector2(v.y, -v.x)
   // ---------------------------------------------------------------------
    Vector2 Perp(const Vector2 &v);

   // ---------------------------------------------------------------------
   // Dot
   // ---------------------------------------------------------------------
   // Obtain a dot product of two given vectors.
   //
   // RETURNS
   //    v1 dot v2
   // ---------------------------------------------------------------------
    float Dot(const Vector2 &v1, const Vector2 &v2);

   // ---------------------------------------------------------------------
   // ostream<<(Vector2)
   // ---------------------------------------------------------------------
   // Output to a stream.
   // ---------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &lhs, const Vector2 &rhs);
}

#endif
