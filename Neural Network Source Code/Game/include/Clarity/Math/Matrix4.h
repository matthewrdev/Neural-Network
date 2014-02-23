#ifndef CLARITY_MATRIX4_H
#define CLARITY_MATRIX4_H

/** @file Matrix4.h
 *
 *  This file contains the Matrix4 class definition.
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
   struct Vector3;
   struct Vector4;
   struct EulerAngle;
   struct Quaternion;

   // ========================================================================
   // Matrix4
   // ========================================================================
   // Class encapsulating a standard 4x4 homogenous matrix.
   //
   // Column vectors are used when applying matrix multiplications,
   // This means a vector is represented as a single column, 4-row
   // matrix. This has the effect that the tranformations implemented
   // by the matrices happens right-to-left e.g. if vector V is to be
   // transformed by M1 then M2 then M3, the calculation would be
   // M3 * M2 * M1 * V. The order that matrices are concatenated is
   // vital since matrix multiplication is not cummatative, i.e. you
   // can get a different result if you concatenate in the wrong order.
   //
   // The use of column vectors and right-to-left ordering is the
   // standard in most mathematical texts, and id the same as used in
   // OpenGL. It is, however, the opposite of Direct3D, which uses
   // row vectors and left-to-right matrix multiplication.
   //
   // The differences between D3D and OpenGL etc. are dealt with
   // internally when operating through different render systems.
   // Users only need to conform to standard maths conventions, i.e.
   // right-to-left matrix multiplication, (matrices passed to D3D 
   // are transposed to compensate).
   //
   // The generic form M * V which shows the layout of the matrix 
   // entries is shown below:
   //
   //    [ m[1][1]  m[1][2]  m[1][3]  m[1][4] ]   {x}
   //    | m[2][1]  m[2][2]  m[2][3]  m[2][4] | * {y}
   //    | m[3][1]  m[3][2]  m[3][3]  m[3][4] |   {z}
   //    [ m[4][1]  m[4][2]  m[4][3]  m[4][4] ]   {2}
   //
   // ========================================================================
   class  Matrix4
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
      static const Matrix4 ZERO;
      static const Matrix4 IDENTITY;

      // ---------------------------------------------------------------------
      // Matrix4
      // ---------------------------------------------------------------------
      // Default constructor initialises the matrix to the identity.
      // ---------------------------------------------------------------------
      Matrix4();

      // ---------------------------------------------------------------------
      // Matrix4
      // ---------------------------------------------------------------------
      // Construct the matrix given individual elements.
      // ---------------------------------------------------------------------
      Matrix4(
         float m11, float m12, float m13, float m14,
         float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34,
         float m41, float m42, float m43, float m44);

      // ---------------------------------------------------------------------
      // Matrix4
      // ---------------------------------------------------------------------
      // Construct a Matrix4 that is equivalent to the supplied Matrix3.
      // ---------------------------------------------------------------------
      explicit Matrix4(const Matrix3 &rhs);

      // ---------------------------------------------------------------------
      // Matrix4
      // ---------------------------------------------------------------------
      // Construct a Matrix4 that is equivalent to the supplied Matrix3 
      // combined with a translation.
      // ---------------------------------------------------------------------
      Matrix4(const Matrix3 &rhs, const Vector3 &translation);

      // ---------------------------------------------------------------------
      // ~Matrix4
      // ---------------------------------------------------------------------
      // Destruct a Matrix4.
      // ---------------------------------------------------------------------
      ~Matrix4();

      // ---------------------------------------------------------------------
      // operator=(Matrix3)
      // ---------------------------------------------------------------------
      // Assign a Matrix3 to a Matrix4.  The Matrix4 is equivalent to the 
      // original Matrix3 object.
      // ---------------------------------------------------------------------
      Matrix4 &operator=(const Matrix3 &rhs);

      // ---------------------------------------------------------------------
      // Identity
      // ---------------------------------------------------------------------
      // Set to the identity matrix.
      // ---------------------------------------------------------------------
      Matrix4 &Identity();

      // ---------------------------------------------------------------------
      // FromAxes
      // ---------------------------------------------------------------------
      // Initialise the matrix from a set of axes.
      // ---------------------------------------------------------------------
      Matrix4 &FromBasisVectors(
         const Vector3 &right, 
         const Vector3 &up, 
         const Vector3 &forward);

      // ---------------------------------------------------------------------
      // FromTranslation
      // ---------------------------------------------------------------------
      // Builds a translation matrix.
      // ---------------------------------------------------------------------
      Matrix4 &FromTranslation(const Vector3 &v);

      // ---------------------------------------------------------------------
      // FromQuaternion
      // ---------------------------------------------------------------------
      // Initialise a rotation matrix from a quaternion.
      // ---------------------------------------------------------------------
      Matrix4 &FromQuaternion(const Quaternion &q);

      // ---------------------------------------------------------------------
      // FromEulerAngle
      // ---------------------------------------------------------------------
      // Initialise a rotation matrix from an euler angle.
      // ---------------------------------------------------------------------
      Matrix4 &FromEulerAngle(const EulerAngle &euler);

      // ---------------------------------------------------------------------
      // FromRotationX
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the x-axis.
      //
      // angle
      //    The amount to rotate around the x-axis in radians.
      // ---------------------------------------------------------------------
      Matrix4 &FromRotationX(float angle);

      // ---------------------------------------------------------------------
      // FromRotationY
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the y-axis.
      //
      // angle
      //    The amount to rotate around the y-axis in radians.
      // ---------------------------------------------------------------------
      Matrix4 &FromRotationY(float angle);

      // ---------------------------------------------------------------------
      // FromRotationZ
      // ---------------------------------------------------------------------
      // Builds a matrix that rotates around the z-axis.
      //
      // angle
      //    The amount to rotate around the z-axis in radians.
      // ---------------------------------------------------------------------
      Matrix4 &FromRotationZ(float angle);

      // ---------------------------------------------------------------------
      // FromScale
      // ---------------------------------------------------------------------
      // Builds a matrix that scales along the x-axis, the y-axis, and the 
      // z-axis.
      // ---------------------------------------------------------------------
      Matrix4 &FromScale(const Vector3 &scale);

      // ---------------------------------------------------------------------
      // operator()
      // ---------------------------------------------------------------------
      // Access an element using subscript notation.  In this case we cannot
      // use operator[] as it can only ever take one argument.
      //
      // rowIdx
      //    The row index (0 - 3).
      // colIdx
      //    The col index (0 - 3).
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
      // operator+=(Matrix4)
      // ---------------------------------------------------------------------
      // Add another matrix to this matrix.
      // ---------------------------------------------------------------------
      Matrix4 &operator+=(const Matrix4 &rhs);

      // ---------------------------------------------------------------------
      // operator-=(Matrix4)
      // ---------------------------------------------------------------------
      // Subtract another matrix from this matrix.
      // ---------------------------------------------------------------------
      Matrix4 &operator-=(const Matrix4 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(Matrix4)
      // ---------------------------------------------------------------------
      // Concatenate/multiply another matrix with this matrix.
      // ---------------------------------------------------------------------
      Matrix4 &operator*=(const Matrix4 &rhs);

      // ---------------------------------------------------------------------
      // operator*=(float)
      // ---------------------------------------------------------------------
      // Multiply the matrix by a scalar.
      // ---------------------------------------------------------------------
      Matrix4 &operator*=(float rhs);

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
      // ---------------------------------------------------------------------
	   bool IsOrthogonal() const;

      // ---------------------------------------------------------------------
      // IsOrthonormal
      // ---------------------------------------------------------------------
      // An orthonormal or special orthogonal matrix is an orthogonal matrix 
      // where the basis vectors are orthogonal and unit length.  The 
      // determinant is always 1.  An orthonormal matrix is a pure rotation 
      // matrix.
      // ---------------------------------------------------------------------
      bool IsOrthonormal() const;

      // ---------------------------------------------------------------------
      // MinorDeterminant
      // ---------------------------------------------------------------------
      // Compute the determinant of a minor of this matrix.  The parameters
      // indicate which rows and columns to build the minor from.
      // ---------------------------------------------------------------------
      float MinorDeterminant(
         const int r0, const int r1, const int r2, 
         const int c0, const int c1, const int c2) const;

      // ---------------------------------------------------------------------
      // Transpose
      // ---------------------------------------------------------------------
      // Compute the transpose of this matrix.  Columns become rows, rows 
      // become columns.
      // ---------------------------------------------------------------------
      Matrix4 Transpose() const;

      // ---------------------------------------------------------------------
      // Adjoint
      // ---------------------------------------------------------------------
      // Comupute the classical adjoint of this matrix.
      // ---------------------------------------------------------------------
      Matrix4 Adjoint() const;

      // ---------------------------------------------------------------------
      // Inverse
      // ---------------------------------------------------------------------
      // Comupute the general inverse of this matrix.  This function will fail
      // silently if the matrix is singular.  See IsSingular().
      // ---------------------------------------------------------------------
      Matrix4 Inverse() const;

      // ---------------------------------------------------------------------
      // InverseFast
      // ---------------------------------------------------------------------
   	// Does a fast inverse, assuming the matrix only contains translation 
      // and rotation.  The inverse of a pure rotation matrix is its transpose
      // and the inverse of the translation is trivial.
      //
      // WARNING
      //    Returns invalid results if the matrix does not contain only 
      //    rotation and translation.
      // ---------------------------------------------------------------------
      Matrix4 InverseFast() const;

      // ---------------------------------------------------------------------
      // Orthonormalize
      // ---------------------------------------------------------------------
      // Takes a matrix with nonorthogonal linearly independent basis vectors
      // and constructs an orthonormalised basis.  This means the basis 
      // vectors are unit length and perpendicular.
      // ---------------------------------------------------------------------
      Matrix4 &Orthonormalize();

      // ---------------------------------------------------------------------
      // GetTranslation
      // ---------------------------------------------------------------------
      // Get the translation elements of the matrix as a vector.
      // ---------------------------------------------------------------------
      Vector3 GetTranslation() const;

      // ---------------------------------------------------------------------
      // GetScale
      // ---------------------------------------------------------------------
      // Gets the scale elements of the matrix as a vector.
      // ---------------------------------------------------------------------
      Vector3 GetScale() const;

      // ---------------------------------------------------------------------
      // SetTranslation
      // ---------------------------------------------------------------------
      // Set only the translation elements of the matrix.  All other elements
      // remain unchanged.
      // ---------------------------------------------------------------------
      Matrix4 &SetTranslation(const Vector3 &translation);

      // ---------------------------------------------------------------------
      // SetScale
      // ---------------------------------------------------------------------
      // Sets the scale elements of the matrix only.
      // ---------------------------------------------------------------------
      Matrix4 &SetScale(const Vector3 &scale);

   private:
      float m[4][4];
   };

   // ---------------------------------------------------------------------
   // operator==(Matrix4, Matrix4)
   // ---------------------------------------------------------------------
   // Tests two matrices for equality.
   // ---------------------------------------------------------------------
    bool operator==(const Matrix4 &lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   // operator!=(Matrix4, Matrix4)
   // ---------------------------------------------------------------------
   // Tests two matrices for inequality.
   // ---------------------------------------------------------------------
    bool operator!=(const Matrix4 &lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   // operator+(Matrix4, Matrix4)
   // ---------------------------------------------------------------------
   // Add two matrices to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix4 operator+(const Matrix4 &lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   // operator-(Matrix4, Matrix4)
   // ---------------------------------------------------------------------
   // Subtract two matrices to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix4 operator-(const Matrix4 &lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   // operator-(Matrix4)
   // ---------------------------------------------------------------------
   // Negate a matrix to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix4 operator-(const Matrix4 &op);

   // ---------------------------------------------------------------------
   // operator*(Matrix4, Matrix4)
   // ---------------------------------------------------------------------
   // Concatenate/multiply two matricies to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix4 operator*(const Matrix4 &lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   //  operator*(Matrix4, float)
   // ---------------------------------------------------------------------
   // Multiply a matrix by a scalar to produce a new matrix.
   // ---------------------------------------------------------------------
    Matrix4 operator*(const Matrix4 &lhs, float rhs);
    Matrix4 operator*(float lhs, const Matrix4 &rhs);

   // ---------------------------------------------------------------------
   // operator*(Matrix4, Vector3)
   // ---------------------------------------------------------------------
   // Transforms the vector by the matrix, projecting the result back into 
   // w = 1.
   //
   // This means that the initial w is considered to be 1.0, and then all 
   // the tree elements of the resulting vector are divided by the 
   // resulting w.
   // ---------------------------------------------------------------------
    Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs);

   // ---------------------------------------------------------------------
   // operator*(Matrix4, Vector4)
   // ---------------------------------------------------------------------
   // Transform a 4D vector by a Homogenous Matrix.
   // ---------------------------------------------------------------------
    Vector4 operator*(const Matrix4 &lhs, const Vector4 &rhs);

   // ---------------------------------------------------------------------
   // operator<<(ostream, Matrix4)
   // ---------------------------------------------------------------------
   // Output to a stream.
   // ---------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &lhs, const Matrix4 &rhs);
}

#endif
