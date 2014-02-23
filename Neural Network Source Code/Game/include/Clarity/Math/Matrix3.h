#ifndef CLARITY_MATRIX3_H
#define CLARITY_MATRIX3_H

/** @file Matrix3.h
 *
 *  This file contains the Matrix3 class definition.
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


namespace Clarity
{
   struct Quaternion;
   struct Vector2;
   struct Vector3;
   struct EulerAngle;
   class Matrix4;

   // ========================================================================
   // Matrix3
   // ========================================================================
   // A 3x3 matrix which can represent rotations around axes.
   //
   // NB All code adapted from Wild Magic 0.2 Matrix math (free source code)
   // http://www.magic-software.com
   //
   // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
   // Coordinate axis rotation matrices are of the form
   //   RX =    1       0       0
   //           0     cos(t) -sin(t)
   //           0     sin(t)  cos(t)
   // where t > 0 indicates a counterclockwise rotation in the yz-plane
   //   RY =  cos(t)    0     sin(t)
   //           0       1       0
   //        -sin(t)    0     cos(t)
   // where t > 0 indicates a counterclockwise rotation in the zx-plane
   //   RZ =  cos(t) -sin(t)    0
   //         sin(t)  cos(t)    0
   //           0       0       1
   // where t > 0 indicates a counterclockwise rotation in the xy-plane.
   // ========================================================================
   class  Matrix3
   {
   public:
      // ---------------------------------------------------------------------
      // Constants
      // ---------------------------------------------------------------------
      // ZERO
      //    All elements zero.
      // IDENTITY
      //    The identity matrix.
      // ---------------------------------------------------------------------
      static const Matrix3 ZERO;
      static const Matrix3 IDENTITY;

      // ---------------------------------------------------------------------
      // Matrix3
      // ---------------------------------------------------------------------
      // Default constructor.  Does not initialise the matrix for performance
      // reasons.
      // ---------------------------------------------------------------------
      Matrix3();

      // ---------------------------------------------------------------------
      // Matrix3
      // ---------------------------------------------------------------------
      // Construct the matrix given individual elements.
      // ---------------------------------------------------------------------
      Matrix3(
         float m11, float m12, float m13,
         float m21, float m22, float m23,
         float m31, float m32, float m33);

      // ---------------------------------------------------------------------
      // Matrix3(Matrix4)
      // ---------------------------------------------------------------------
      // Construct a 3x3 Matrix from a 4x4 Matrx object by cropping out the
      // rotation scaling section.
      // ---------------------------------------------------------------------
      explicit Matrix3(const Matrix4 &rhs);

      // ---------------------------------------------------------------------
      // ~Matrix3
      // ---------------------------------------------------------------------
      // Destruct a Matrix3.
      // ---------------------------------------------------------------------
      ~Matrix3();

      // ---------------------------------------------------------------------
      // operator=(Matrix4)
      // ---------------------------------------------------------------------
      // Extract a 3x3 Matrix from a 4x4 Matrx object by cropping out the
      // rotation scaling section.
      // ---------------------------------------------------------------------
      Matrix3 &operator=(const Matrix4 &rhs);

      // ---------------------------------------------------------------------
      // Identity
      // ---------------------------------------------------------------------
      // Set to the identity matrix.
      // ---------------------------------------------------------------------
      Matrix3 &Identity();

      // ---------------------------------------------------------------------
      // FromAxes
      // ---------------------------------------------------------------------
      // Initialise the matrix from a set of axes.
      // ---------------------------------------------------------------------
      Matrix3 &FromBasisVectors(
         const Vector3 &right, 
         const Vector3 &up, 
         const Vector3 &forward);

      // ---------------------------------------------------------------------
      // FromTranslation
      // ---------------------------------------------------------------------
      // Builds a translation matrix.
      // ---------------------------------------------------------------------
      Matrix3 &FromTranslation(const Vector2 &v);

      // ---------------------------------------------------------------------
      // FromQuaternion
      // ---------------------------------------------------------------------
      // Initialise a rotation matrix from a quaternion.
      // ---------------------------------------------------------------------
      Matrix3 &FromQuaternion(const Quaternion &q);

      // ---------------------------------------------------------------------
      // FromEulerAngle
      // ---------------------------------------------------------------------
      // Initialise a rotation matrix from an euler angle.
      // ---------------------------------------------------------------------
      Matrix3 &FromEulerAngle(const EulerAngle &euler);

      // ---------------------------------------------------------------------
      // FromRotationX
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the x-axis.
      //
      // angle
      //    The amount to rotate around the x-axis in radians.
      // ---------------------------------------------------------------------
      Matrix3 &FromRotationX(float angle);

      // ---------------------------------------------------------------------
      // FromRotationY
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the y-axis.
      //
      // angle
      //    The amount to rotate around the y-axis in radians.
      // ---------------------------------------------------------------------
      Matrix3 &FromRotationY(float angle);

      // ---------------------------------------------------------------------
      // FromRotationZ
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the z-axis.
      //
      // angle
      //    The amount to rotate around the z-axis in radians.
      // ---------------------------------------------------------------------
      Matrix3 &FromRotationZ(float angle);

      // ---------------------------------------------------------------------
      // FromScale
      // ---------------------------------------------------------------------
      // Builds a matrix that scales along the x-axis and the y-axis.
      // ---------------------------------------------------------------------
      Matrix3 &FromScale2(const Vector2 &scale);

      // ---------------------------------------------------------------------
      // FromScale
      // ---------------------------------------------------------------------
      // Builds a matrix that scales along the x-axis, the y-axis, and the 
      // z-axis.
      // ---------------------------------------------------------------------
      Matrix3 &FromScale(const Vector3 &scale);

      // ---------------------------------------------------------------------
      // operator()
      // ---------------------------------------------------------------------
      // Access an element using subscript notation.  In this case we cannot
      // use operator[] as it can only ever take one argument.
      //
      // rowIdx
      //    The row index (0 - 2).
      // colIdx
      //    The col index (0 - 2).
      // ---------------------------------------------------------------------
      float &operator()(int rowIdx, int colIdx);
      float operator()(int rowIdx, int colIdx) const;

      // ---------------------------------------------------------------------
      // operator[](int)
      // ---------------------------------------------------------------------
      // Extract a basis vector from the matrix.
      // basisIdx
      //    0 - Extract the right vector
      //    1 - Extract the up vector
      //    2 - Extract the forward vector
      // ---------------------------------------------------------------------
      Vector3 operator[](int basisIdx) const;

      // ---------------------------------------------------------------------
      // GetRight, GetUp, GetForward
      // ---------------------------------------------------------------------
      // Extract the basis vectors from the matrix.
      // ---------------------------------------------------------------------
      Vector3 GetRight() const;
      Vector3 GetUp() const;
      Vector3 GetForward() const;

      // ---------------------------------------------------------------------
      // operator+=(Matrix3)
      // ---------------------------------------------------------------------
      // Add another matrix to this matrix.
      // ---------------------------------------------------------------------
      Matrix3 &operator+=(const Matrix3 &rhs);

      // ---------------------------------------------------------------------
      // operator-=(Matrix3)
      // ---------------------------------------------------------------------
      // Subtract another matrix from this matrix.
      // ---------------------------------------------------------------------
      Matrix3 &operator-=(const Matrix3 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(Matrix3)
      // ---------------------------------------------------------------------
      // Concatenate/multiply another matrix with this matrix.
      // ---------------------------------------------------------------------
      Matrix3 &operator*=(const Matrix3 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(float)
      // ---------------------------------------------------------------------
      // Multiply the matrix by a scalar.
      // ---------------------------------------------------------------------
      Matrix3 &operator*=(float rhs);
      
      // ---------------------------------------------------------------------
      // Determinant
      // ---------------------------------------------------------------------
      // Comupute the determinant of this matrix.
      // ---------------------------------------------------------------------
      float Determinant() const;

      // ---------------------------------------------------------------------
      // IsSingular
      // ---------------------------------------------------------------------
      // A singular matrix has no inverse.  A square matrix has no inverse if 
      // the determinant is zero.
      // ---------------------------------------------------------------------
      bool IsSingular() const;

      // ---------------------------------------------------------------------
      // IsOrthogonal
      // ---------------------------------------------------------------------
	   // Determine if the matrix is orthogonal.  A matrix is orthogonal if the
      // basis vectors are all unit vectors and are all orthogonal.  The 
      // determinant of an orthogonal matrix is always 1 or -1.
      //
      // The matrix product of two orthogonal matrices is another orthogonal 
      // matrix. In addition, the inverse of an orthogonal matrix is an 
      // orthogonal matrix, as is the identity matrix. 
      //
      // tolerance
      //    The accepted deviation from a determinant of 1 or -1 within which 
      //    the matrix can still be considered orthogonal.
      // ---------------------------------------------------------------------
	   bool IsOrthogonal(float tolerance) const;

      // ---------------------------------------------------------------------
      // IsOrthonormal
      // ---------------------------------------------------------------------
      // An orthonormal or special orthogonal matrix is an orthogonal matrix 
      // where the basis vectors are orthogonal and unit length.  The 
      // determinant is always 1.  An orthonormal matrix is a pure rotation 
      // matrix.
      //
      // tolerance
      //    The accepted deviation from a determinant of 1 within which the 
      //    matrix can still be considered orthonormal.
      // ---------------------------------------------------------------------
      bool IsOrthonormal(float tolerance) const;

      // ---------------------------------------------------------------------
      // Transpose
      // ---------------------------------------------------------------------
      // Compute the transpose of this matrix.  Columns become rows, rows 
      // become columns.
      // ---------------------------------------------------------------------
      Matrix3 Transpose() const;

      // ---------------------------------------------------------------------
      // Inverse
      // ---------------------------------------------------------------------
      // Comupute the general inverse of this matrix.  This function will fail
      // silently if the matrix is singular.  See IsSingular().
      // ---------------------------------------------------------------------
      Matrix3 Inverse() const;

      // ---------------------------------------------------------------------
      // InverseFast
      // ---------------------------------------------------------------------
   	// Does a fast inverse, assuming the matrix only contains translation 
      // and rotation.  The inverse of a pure rotation matrix is its transpose
      // and the inverse of the translation is trivial.
      //
      // WARNING
      //    Returns invalid results if the matrix does not contain only 
      //    rotation.
      // ---------------------------------------------------------------------
      Matrix3 InverseFast() const;

      // ---------------------------------------------------------------------
      // Orthonormalize
      // ---------------------------------------------------------------------
      // Takes a matrix with nonorthogonal linearly independent basis vectors
      // and constructs an orthonormalised basis.  This means the basis 
      // vectors are unit length and perpendicular.
      // ---------------------------------------------------------------------
      Matrix3 &Orthonormalize();

      // ---------------------------------------------------------------------
      // GetScale
      // ---------------------------------------------------------------------
      // Gets the scale elements of the matrix as a vector.
      // ---------------------------------------------------------------------
      Vector3 GetScale() const;

      // ---------------------------------------------------------------------
      // SetScale
      // ---------------------------------------------------------------------
      // Sets the scale elements of the matrix only.
      // ---------------------------------------------------------------------
      Matrix3 &SetScale(const Vector3 &scale);

   private:
      float m[3][3];
   };


   // ---------------------------------------------------------------------
   // operator==(Matrix3, Matrix3)
   // ---------------------------------------------------------------------
   // Tests two matrices for equality.
   // ---------------------------------------------------------------------
    bool operator==(const Matrix3 &lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   // operator!=(Matrix3, Matrix3)
   // ---------------------------------------------------------------------
   // Tests two matrices for inequality.
   // ---------------------------------------------------------------------
    bool operator!=(const Matrix3 &lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   // operator+(Matrix3, Matrix3)
   // ---------------------------------------------------------------------
   // Add two matrices to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix3 operator+(const Matrix3 &lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   // operator-(Matrix3, Matrix3)
   // ---------------------------------------------------------------------
   // Subtract two matrices to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix3 operator-(const Matrix3 &lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   // operator-(Matrix3)
   // ---------------------------------------------------------------------
   // Negate a matrix to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix3 operator-(const Matrix3 &op);

   // ---------------------------------------------------------------------
   // operator*(Matrix3, Matrix3)
   // ---------------------------------------------------------------------
   // Concatenate/multiply two matricies to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix3 operator*(const Matrix3 &lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   //  operator*(Matrix3, float)
   // ---------------------------------------------------------------------
   // Multiply a matrix by a scalar to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix3 operator*(const Matrix3 &lhs, float rhs);
    Matrix3 operator*(float lhs, const Matrix3 &rhs);

   // ---------------------------------------------------------------------
   // operator*(Matrix3, Vector2)
   // ---------------------------------------------------------------------
   // Transforms the vector by the matrix
   // ---------------------------------------------------------------------
    Vector2 operator*(const Matrix3 &lhs, const Vector2 &rhs);

   // ---------------------------------------------------------------------
   // operator*(Matrix3, Vector3)
   // ---------------------------------------------------------------------
   // Transforms the vector by the matrix
   // ---------------------------------------------------------------------
    Vector3 operator*(const Matrix3 &lhs, const Vector3 &rhs);
}

#endif
