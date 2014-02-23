#ifndef CLARITY_QUATERNION_H
#define CLARITY_QUATERNION_H

/** @file Quaternion.h
 *
 *  This file contains the Quaternion class definition.
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
   class Matrix3;
   class Matrix4;
   struct Vector3;

   // ========================================================================
   // Quaternion
   // ========================================================================
   // Represents an orientation as an axis and an amount of rotation around 
   // that axis.
   // ========================================================================
   struct  Quaternion
   {
      // ---------------------------------------------------------------------
      // Components
      // ---------------------------------------------------------------------
      // Quaternion is considered a basic type so exposing the data members is
      // condidered an acceptable violation of encapsulation.
      // ---------------------------------------------------------------------
      float w, x, y, z;

      // ---------------------------------------------------------------------
      // Constants
      // ---------------------------------------------------------------------
      // ZERO
      //    w = 0, x = 0, y = 0, z = 0
      // IDENTITY
      //    w = 1, x = 0, y = 0, z = 0
      // ---------------------------------------------------------------------
      static const Quaternion ZERO;
      static const Quaternion IDENTITY;

      // ---------------------------------------------------------------------
      // Quaternion
      // ---------------------------------------------------------------------
      // Default constructor.  Quaternion is initialised to the identity
      // quaternion.
      // ---------------------------------------------------------------------
      Quaternion();

      // ---------------------------------------------------------------------
      // Quaternion(float, float, float, float)
      // ---------------------------------------------------------------------
      // Construct a quaternion from components.
      // ---------------------------------------------------------------------
      Quaternion(float wIn, float xIn, float yIn, float zIn);

      // ---------------------------------------------------------------------
      // Quaternion(Matrix3)
      // ---------------------------------------------------------------------
      // Construct a quaternion from a 3x3 rotation matrix.
      // The matrix must be orthonormal.
      // ---------------------------------------------------------------------
      explicit Quaternion(const Matrix3 &rotationMatrix);

      // ---------------------------------------------------------------------
      // Quaternion(Matrix4)
      // ---------------------------------------------------------------------
      // Construct a quaternion from a 4x4 rotation matrix.
      // The matrix must be orthonormal.
      // ---------------------------------------------------------------------
      explicit Quaternion(const Matrix4 &rotationMatrix);

      // ---------------------------------------------------------------------
      // Quaternion(float, Vector3)
      // ---------------------------------------------------------------------
      // Construct a quaternion from angle axis form.
      // ---------------------------------------------------------------------
      Quaternion(float angle, const Vector3 &axis);

      // ---------------------------------------------------------------------
      // ~Quaternion
      // ---------------------------------------------------------------------
      // Destruct a quaternion.
      // ---------------------------------------------------------------------
      ~Quaternion();

      // ---------------------------------------------------------------------
      // operator=(Matrix3)
      // ---------------------------------------------------------------------
      // Assign a 3x3 Rotation Matrix to the quaternion.
      // The matrix must be orthonormal.
      // ---------------------------------------------------------------------
      Quaternion &operator=(const Matrix3 &rotMat);

      // ---------------------------------------------------------------------
      // operator=(Matrix4)
      // ---------------------------------------------------------------------
      // Assign a 4x4 Rotation Matrix to the quaternion.
      // The matrix must be orthonormal.
      // ---------------------------------------------------------------------
      Quaternion &operator=(const Matrix4 &rotMat);

      // ---------------------------------------------------------------------
      // ToAngleAxis
      // ---------------------------------------------------------------------
      // Convert to angle axis form.
      // ---------------------------------------------------------------------
      void ToAngleAxis(float &angle, Vector3 &axis) const;

      // ---------------------------------------------------------------------
      // operator+=(Quaternion)
      // ---------------------------------------------------------------------
      // Add a quaternion to the current quaternion.
      // ---------------------------------------------------------------------
      Quaternion &operator+=(const Quaternion &rhs);

      // ---------------------------------------------------------------------
      // operator-=(Quaternion)
      // ---------------------------------------------------------------------
      // Subtract a quaternion to the current quaternion.
      // ---------------------------------------------------------------------
      Quaternion &operator-=(const Quaternion &rhs);

      // ---------------------------------------------------------------------
      // operator*=(Quaternion)
      // ---------------------------------------------------------------------
      // Multiplies two quaternions.
      // The result represents the rotation rhs followed by the rotation lhs.
      // This is done so that multiplying quaternions maintains the same 
      // semantics as multiplying matricies because unit quaternions can be 
      // considered as another way to represent rotation matrices.
      //
      // The multiplication of quaternions is not commutative.
      // ---------------------------------------------------------------------
      Quaternion &operator*=(const Quaternion &rhs);

      // ---------------------------------------------------------------------
      // operator*=(float)
      // ---------------------------------------------------------------------
      // Multiplies a quaternion by a scalar.
      // ---------------------------------------------------------------------
      Quaternion &operator*=(float rhs);

      // ---------------------------------------------------------------------
      // IsIdentity
      // ---------------------------------------------------------------------
      // Determines if a quaternion is an identity quaternion.
      // ---------------------------------------------------------------------
      bool IsIdentity() const;

      // ---------------------------------------------------------------------
      // Magnitude
      // ---------------------------------------------------------------------
      // Returns the magnitude of a quaternion.
      // ---------------------------------------------------------------------
      float Magnitude() const;

      // ---------------------------------------------------------------------
      // Norm
      // ---------------------------------------------------------------------
      // Returns the norm of the quaternion.
      //
      // The norm of a quaternion Q(a,b,c,d) is the square root of the
      // determinant of the corresponding matrix:
      //    Det(Q(a,b,c,d)) = (a^2 + b^2 + c^2 + d^2)^2
      //    Norm(Q(a,b,c,d)) = a^2 + b^2 + c^2 + d^2.
      // 
      // Note that norm(Q1 Q2) = norm(Q1) norm(Q2), and that 
      // norm(Q') = norm(Q).
      // 
      // Note also that if norm(Q(a,b,c,d)) = 1, then the matrix corresponding 
      // to Q(a,b,c,d) is orthogonal.
      // ---------------------------------------------------------------------
      float Norm() const;

      // ---------------------------------------------------------------------
      // Normalise
      // ---------------------------------------------------------------------
      // Normalises the quaternion, and returns the previous length.
      // ---------------------------------------------------------------------
      float Normalise();

      // ---------------------------------------------------------------------
      // Conjugate
      // ---------------------------------------------------------------------
      // Obtain the conjugate of a quaternion.  The conjugate represents 
      // rotation in the opposite direction.
      //
      // Given a quaternion (x, y, z, w), this function will return the 
      // quaternion (-x, -y, -z, w).  The conjugate of a unit length
      // quaternion is also its inverse.
      //
      // Note the conjugate of ~(a*b) = ~a * ~b. So the conjugate of a 
      // composite rotation is not the inverse of the rotations.
      // ---------------------------------------------------------------------
      Quaternion Conjugate() const;

      // ---------------------------------------------------------------------
      // Inverse
      // ---------------------------------------------------------------------
      // Conjugates and renormalizes a quaternion.  
      // Apply to non-zero quaternions only.
      // ---------------------------------------------------------------------
      Quaternion Inverse() const;

      // ---------------------------------------------------------------------
      // Exp
      // ---------------------------------------------------------------------
      // Calculates the exponential.
      //
      // This method converts a pure quaternion to a unit quaternion. 
      // Exp expects a pure quaternion, where w is ignored in the calculation 
      // (w == 0).
      // Given a pure quaternion defined by:
      //    q = (0, theta * v); 
      //
      // This method calculates the exponential result.
      //    exp(Q) = (cos(theta), sin(theta) * v)
      //
      // where v is the vector portion of a quaternion.
      // ---------------------------------------------------------------------
      Quaternion Exp() const;

      // ---------------------------------------------------------------------
      // Ln
      // ---------------------------------------------------------------------
      // Calculates the natural logarithm.
      // 
      // The Ln function works only for unit quaternions.
      //
      // A unit quaternion, is defined by:
      //    Q == (cos(theta), sin(theta) * v) where |v| = 1
      //
      // The natural logarithm of Q is, ln(Q) = (0, theta * v)
      // ---------------------------------------------------------------------
      Quaternion Ln() const;

      // ---------------------------------------------------------------------
      // Dot
      // ---------------------------------------------------------------------
      // Calculate the dot product of two quaternions.
      // ---------------------------------------------------------------------
      static float Dot(const Quaternion &lhs, const Quaternion &rhs);

      // ---------------------------------------------------------------------
      // Slerp
      // ---------------------------------------------------------------------
      // Interpolates between two quaternions, using spherical linear 
      // interpolation.
      // ---------------------------------------------------------------------
      static Quaternion Slerp(
         float t, 
         const Quaternion &q1,
         const Quaternion &q2, 
         bool shortestPath = false);

      // ---------------------------------------------------------------------
      // SlerpExtraSpins
      // ---------------------------------------------------------------------
      // Spherical linear interpolation with extra spins.
      // ---------------------------------------------------------------------
      static Quaternion SlerpExtraSpins(
         float t,
         const Quaternion &q1, 
         const Quaternion &q2,
         int extraSpins);

      // ---------------------------------------------------------------------
      // SetupSquad
      // ---------------------------------------------------------------------
      // Setup control points for spherical quadrangle interpolation.
      //
      // This function takes three control points, which are supplied to the 
      // inputs q0, q1, and q2. The function then alters these values to find 
      // a curve that flows along the shortest path.
      // ---------------------------------------------------------------------
      static void SetupSquad(
         const Quaternion &q0,
         const Quaternion &q1, 
         const Quaternion &q2,
         Quaternion &a, 
         Quaternion &b);

      // ---------------------------------------------------------------------
      // Squad
      // ---------------------------------------------------------------------
      // Interpolates between quaternions, using spherical quadrangle 
      // interpolation.
      //
      // This function uses the following sequence of spherical linear 
      // interpolation operations:
      //    Slerp(2t(1 - t), Slerp(t, p, q, shortestPath), Slerp(t, a, b))
      // ---------------------------------------------------------------------
      static Quaternion Squad(
         float t, 
         const Quaternion &p,
         const Quaternion &a, 
         const Quaternion &b,
         const Quaternion &q, 
         bool shortestPath = false);
   };

   // ---------------------------------------------------------------------
   // operator+(Quaternion, Quaternion)
   // ---------------------------------------------------------------------
   // Add quaternions.
   // ---------------------------------------------------------------------
    Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs);

   // ---------------------------------------------------------------------
   // operator-(Quaternion, Quaternion)
   // ---------------------------------------------------------------------
   // Subtract quaternions.
   // ---------------------------------------------------------------------
    Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs);

   // ---------------------------------------------------------------------
   // operator*(Quaternion, Quaternion)
   // ---------------------------------------------------------------------
   // Multiplies two quaternions.
   // The result represents the rotation rhs followed by the rotation lhs.
   // This is done so that multiplying quaternions maintains the same 
   // semantics as multiplying matricies because unit quaternions can be 
   // considered as another way to represent rotation matrices.
   //
   // The multiplication of quaternions is not commutative.
   // ---------------------------------------------------------------------
    Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs);

   // ---------------------------------------------------------------------
   // operator*(Quaternion, Vector3)
   // ---------------------------------------------------------------------
   // Rotate a vector by a quaternion
   // ---------------------------------------------------------------------
    Vector3 operator*(const Quaternion &lhs, const Vector3 &rhs);

   // ---------------------------------------------------------------------
   // operator*(float, Quaternion)
   // ---------------------------------------------------------------------
   // Multiplies a quaternion by a scalar.
   // ---------------------------------------------------------------------
    Quaternion operator*(float lhs, const Quaternion &rhs);

   // ---------------------------------------------------------------------
   // operator*(Quaternion, float)
   // ---------------------------------------------------------------------
   // Multiplies a quaternion by a scalar.
   // ---------------------------------------------------------------------
    Quaternion operator*(const Quaternion &lhs, float rhs);

   // ---------------------------------------------------------------------
   // operator-(Quaternion)
   // ---------------------------------------------------------------------
   // Negate a quaternion.
   // ---------------------------------------------------------------------
    Quaternion operator-(const Quaternion &op);

   // ---------------------------------------------------------------------
   // operator~(Quaternion)
   // ---------------------------------------------------------------------
   // Obtain the conjugate of a quaternion.  The conjugate represents 
   // rotation in the opposite direction.
   //
   // Given a quaternion (x, y, z, w), this function will return the 
   // quaternion (-x, -y, -z, w).  The conjugate of a unit length
   // quaternion is also its inverse.
   //
   // Note the conjugate of ~(a*b) = ~a * ~b. So the conjugate of a 
   // composite rotation is not the inverse of the rotations.
   // ---------------------------------------------------------------------
    Quaternion operator~(const Quaternion &op);

   // ---------------------------------------------------------------------
   // ostream<<(Quaternion)
   // ---------------------------------------------------------------------
   // Output to a stream.
   // ---------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &lhs, const Quaternion &rhs);
}

#endif
