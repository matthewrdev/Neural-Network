#ifndef CLARITY_VECTOR3_H
#define CLARITY_VECTOR3_H


/** @file Vector3.h
 *
 *  This file contains the Vector3 class definition.
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
   struct Vector2;
   struct Vector4;
   class Matrix3;
   class Matrix4;

   // ========================================================================
   // Vector3
   // ========================================================================
   // ========================================================================
   struct  Vector3
   {
      // ---------------------------------------------------------------------
      // Components
      // ---------------------------------------------------------------------
      // Vector3 is considered a basic type so exposing the data members is
      // condidered an acceptable violation of encapsulation.
      // ---------------------------------------------------------------------
      float x, y, z;        

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
      static const Vector3 ZERO;
      static const Vector3 UNIT_X;
      static const Vector3 UNIT_Y;
      static const Vector3 UNIT_Z;
      static const Vector3 NEGATIVE_UNIT_X;
      static const Vector3 NEGATIVE_UNIT_Y;
      static const Vector3 NEGATIVE_UNIT_Z;
      static const Vector3 UNIT_SCALE;

      // ---------------------------------------------------------------------
      // Vector3
      // ---------------------------------------------------------------------
      // Default constructor.  Elements set to the zero vector.
      // ---------------------------------------------------------------------
      Vector3();

      // ---------------------------------------------------------------------
      // Vector3
      // ---------------------------------------------------------------------
      // Construct a 3d vector from its elements.
      // ---------------------------------------------------------------------
      Vector3(float xIn, float yIn, float zIn);

      // ---------------------------------------------------------------------
      // Vector3
      // ---------------------------------------------------------------------
      // Construct a 3d vector from a homogenous vector by dividing by the w
      // component.
      //
      // PRECONDITIONS
      //    v4.w != 0
      // ---------------------------------------------------------------------
      explicit Vector3(const Vector4 &v4);

      // ---------------------------------------------------------------------
      // Vector3
      // ---------------------------------------------------------------------
      // Construct a 3d vector from a 2D vector and a z component.
      // ---------------------------------------------------------------------
      Vector3(const Vector2 &rhs, float z);

      // ---------------------------------------------------------------------
      // ~Vector3
      // ---------------------------------------------------------------------
      // Destruct a Vector3.
      // ---------------------------------------------------------------------
      ~Vector3();

      // ---------------------------------------------------------------------
      // operator=(Vector4)
      // ---------------------------------------------------------------------
      // Assign a homogenous vector to a 3d vector by dividing by the w 
      // component.  
      //
      // PRE: rhs.w != 0
      // ---------------------------------------------------------------------
      Vector3 &operator=(const Vector4 &rhs);

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
      // Set a Vector3 object from component parts.
      // ---------------------------------------------------------------------
      void Set(float xIn, float yIn, float zIn);

      // ---------------------------------------------------------------------
      // operator*=(Vector3)
      // ---------------------------------------------------------------------
      // Perform a componentwise multiply assignment.
      // ---------------------------------------------------------------------
      Vector3 &operator*=(const Vector3 &rhs);

      // ---------------------------------------------------------------------
      // operator/=(Vector3)
      // ---------------------------------------------------------------------
      // Perform a componentwise division assignment.
      //
      // PRE: rhs.x != 0 && rhs.y != 0 && rhs.z != 0
      // ---------------------------------------------------------------------
      Vector3 &operator/=(const Vector3 &rhs);

      // ---------------------------------------------------------------------
      // operator+=(Vector3)
      // ---------------------------------------------------------------------
      // Perform a componentwise addition assignment.
      // ---------------------------------------------------------------------
      Vector3 &operator+=(const Vector3 &rhs);

      // ---------------------------------------------------------------------
      // operator-=(Vector3)
      // ---------------------------------------------------------------------
      // Perform a componentwise subtraction assignment.
      // ---------------------------------------------------------------------
      Vector3 &operator-=(const Vector3 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(float)
      // ---------------------------------------------------------------------
      // Multiply assign the vector by a scalar.
      // ---------------------------------------------------------------------
      Vector3 &operator*=(float rhs);

      // ---------------------------------------------------------------------
      // operator/=(float)
      // ---------------------------------------------------------------------
      // Divide assign the vector by a scalar.
      //
      // PRE: rhs != 0
      // ---------------------------------------------------------------------
      Vector3 &operator/=(float rhs);

      // ---------------------------------------------------------------------
      // Transform(Matrix3)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied.
      // ---------------------------------------------------------------------
      Vector3 Transform(const Matrix3 &lhs) const;

      // ---------------------------------------------------------------------
      // Transform(Matrix4)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied, projecting the result 
      // back into w = 1.
      //
      // This means that the initial w is considered to be 1.0, and then all 
      // the three elements of the resulting 3-D vector are divided by the 
      // resulting w.
      // ---------------------------------------------------------------------
      Vector3 Transform(const Matrix4 &lhs) const;

      // ---------------------------------------------------------------------
      // TransformVector(Matrix4)
      // ---------------------------------------------------------------------
      // Transforms this vector by the matrix supplied but only uses the 
      // rotation/scale elements of the matrix, not the translation.
      // ---------------------------------------------------------------------
      Vector3 TransformVector(const Matrix4 &lhs) const;

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
      // x, y and z from both vectors. Lowest is taken just numerically, not 
      // magnitude, so -1 < 0.
      // ---------------------------------------------------------------------
      void MakeFloor(const Vector3 &cmp);

      // ---------------------------------------------------------------------
      // MakeCeil
      // ---------------------------------------------------------------------
      // Sets this vector's components to the maximum of its own and the ones 
      // of the passed in vector.
      //
      // 'Maximum' in this case means the combination of the highest value of 
      // x, y and z from both vectors. Highest is taken just numerically, not 
      // magnitude, so 1 > -3.
      // ---------------------------------------------------------------------
      void MakeCeil(const Vector3 &cmp);

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
      static float DotProduct(const Vector3 &lhs, const Vector3 &rhs);

      // ---------------------------------------------------------------------
      // CrossProduct
      // ---------------------------------------------------------------------
      // Calculates the cross-product of 2 vectors, i.e. the vector that lies 
      // perpendicular to them both.
      //
      // The cross-product is normally used to calculate the normal
      // vector of a plane, by calculating the cross-product of 2
      // non-equivalent vectors which lie on the plane (e.g. 2 edges
      // of a triangle).
      //
      // RETURNS
      // A vector which is the result of the cross-product. This vector will 
      // NOT be normalised, to maximise efficiency call Vector3::normalise on 
      // the result if you wish this to be done. As for which side the 
      // resultant vector will be on, the returned vector will be on the side 
      // from which the arc from 'this' to rhs is anticlockwise.  
      // E.g.  UNIT_Y.crossProduct(UNIT_Z) =  UNIT_X, 
      //       UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X
      //
      // For a clearer explanation, look a the left and the bottom edges
      // of your monitor's screen. Assume that the first vector is the
      // left edge and the second vector is the bottom edge, both of
      // them starting from the lower-left corner of the screen. The
      // resulting vector is going to be perpendicular to both of them
      // and will go inside the screen, towards the cathode tube
      // (assuming you're using a CRT monitor, of course).
      // ---------------------------------------------------------------------
      static Vector3 CrossProduct(const Vector3 &lhs, const Vector3 &rhs);
   };

   // ---------------------------------------------------------------------
   // Per Element Arithmetic Operations
   // ---------------------------------------------------------------------
    Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);
    Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);
    Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs);
    Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator*(const Vector3 &lhs, float rhs);
    Vector3 operator/(const Vector3 &lhs, float rhs);

    Vector3 operator*(float lhs, const Vector3 &rhs);
    Vector3 operator/(float lhs, const Vector3 &rhs);

    Vector3 operator-(const Vector3 &op);

   // ---------------------------------------------------------------------
   // Per Element Equality Operations
   // ---------------------------------------------------------------------
    bool operator==(const Vector3 &lhs, const Vector3 &rhs);
    bool operator!=(const Vector3 &lhs, const Vector3 &rhs);

   // ---------------------------------------------------------------------
   // ostream<<(Vector3)
   // ---------------------------------------------------------------------
   // Output to a stream.
   // ---------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &lhs, const Vector3 &rhs);
}

#endif
