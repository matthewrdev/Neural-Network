#ifndef CLARITY_MATRIX2_H
#define CLARITY_MATRIX2_H

/** @file Matrix2.h
 *
 *  This file contains the Matrix2 class definition.
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
   struct Vector2;
   class Matrix3;

   /**
   * A 2x2 matrix.  Used for rotation and scaling in 2D space.
   *
   * All code adapted from Wild Magic 0.2 Matrix math (free source code)
   * http://www.magic-software.com
   *
   * Coordinate axis rotation matrices are of the form
   *   R  =    cos(t) -sin(t)
   *           sin(t)  cos(t)
   */
   class  Matrix2
   {
   public:
      /**
      * Matrix with all elements zero.
      */
      static const Matrix2 ZERO;

      /**
      * The identity matrix.
      */
      static const Matrix2 IDENTITY;

      /**
      * Default constructor.  Does not initialise the matrix for performance
      * reasons.
      */
      Matrix2();

      /**
      * Construct the matrix given individual elements.
      * 
      * @param m11
      *     Initial value for row 1, column 1.
      * @param m12
      *     Initial value for row 1, column 2.
      * @param m21
      *     Initial value for row 2, column 1.
      * @param m22
      *     Initial value for row 2, column 2.
      */
      Matrix2(
         float m11, float m12,
         float m21, float m22);

      /**
      * Construct a 2x2 Matrix from a 3x3 Matrx object by cropping out the
      * rotation scaling section.
      *
      * @param rhs
      *     The 3x3 matrix from which to construct the 2x2 matrix.
      */
      explicit Matrix2(const Matrix3 &rhs);

      /**
      * Destructor.
      */
      ~Matrix2();

      /**
      * Extract a 2x2 Matrix from a 3x3 Matrx object by cropping out the
      * rotation scaling section.
      *
      * @param rhs
      *     The 3x3 matrix on which to base the 2x2 matrix.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &operator=(const Matrix3 &rhs);

      /**
      * Set to the identity matrix.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &Identity();

      /**
      * Initialise the matrix from a set of axes.
      *
      * @param right
      *     The right axis of the matrix.
      * @param up
      *     The up axis of the matrix.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &FromBasisVectors(
         const Vector2 &right, 
         const Vector2 &up);

      /**
      * Initialise a rotation matrix from a rotation (in radians).
      *
      * @param angle
      *     The angle of the rotation clockwise from the x-axis in radians.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &FromRotation(float angle);

      /**
      * Builds a matrix that scales along the x-axis, and the y-axis.
      *
      * @param scale
      *     The scale along the x and y axes.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &FromScale(const Vector2 &scale);

      /**
      * Access an element using subscript notation.  In this case we cannot
      * use operator[] as it can only ever take one argument.
      *
      * @param rowIdx
      *    The row index (0 - 1).
      * @param colIdx
      *    The col index (0 - 1).
      *
      * @returns
      *     A reference to the requested element of the matrix.
      */
      float &operator()(int rowIdx, int colIdx);

      /**
      * Access an element using subscript notation.  In this case we cannot
      * use operator[] as it can only ever take one argument.
      *
      * @param rowIdx
      *    The row index (0 - 1).
      * @param colIdx
      *    The col index (0 - 1).
      *
      * @returns
      *     A copy of the requested element of the matrix.
      */
      float operator()(int rowIdx, int colIdx) const;

      /**
      * Extract a basis vector from the matrix.
      *
      * @param basisIdx
      *    - 0 => Extract the right vector
      *    - 1 => Extract the up vector
      *
      * @returns
      *     A vector representing the axis.
      */
      Vector2 operator[](int basisIdx) const;

      /**
      * Extract the right basis vector from the matrix.
      *
      * @returns
      *     The right axis of the matrix.
      */
      Vector2 GetRight() const;

      /**
      * Extract the up basis vector from the matrix.
      *
      * @returns
      *     The up axis of the matrix.
      */
      Vector2 GetUp() const;

      /**
      * Add another matrix to this matrix.
      *
      * @param rhs
      *     The matrix to add to this matrix.
      *
      * @returns 
      *     A reference to this matrix.
      */
      Matrix2 &operator+=(const Matrix2 &rhs);

      /**
      * Subtract another matrix from this matrix.
      *
      * @param rhs
      *     The matrix to subtract from this matrix.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &operator-=(const Matrix2 &rhs);

      /**
      * Concatenate/multiply another matrix with this matrix.
      *
      * @param rhs
      *     The matrix to multiply this matrix by.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &operator*=(const Matrix2 &rhs);

      /**
      * Multiply the matrix by a scalar.
      *
      * @param rhs
      *     The scalar to multiply this matrix by.
      *
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &operator*=(float rhs);
      
      /**
      * Comupute the determinant of this matrix.
      *
      * @returns
      *     The determinant of this matrix.
      */
      float Determinant() const;

      /**
      * A singular matrix has no inverse.  A square matrix has no inverse if 
      * the determinant is zero.
      *
      * @returns
      *     Whether this matrix is singular.
      */
      bool IsSingular() const;

      /**
	   * Determine if the matrix is orthogonal.  A matrix is orthogonal if the
      * basis vectors are all unit vectors and are all orthogonal.  The 
      * determinant of an orthogonal matrix is always 1 or -1.
      *
      * The matrix product of two orthogonal matrices is another orthogonal 
      * matrix. In addition, the inverse of an orthogonal matrix is an 
      * orthogonal matrix, as is the identity matrix. 
      *
      * @returns
      *     Whether this matrix is orthoganal.
      */
	   bool IsOrthogonal() const;

      /**
      * An orthonormal or special orthogonal matrix is an orthogonal matrix 
      * where the basis vectors are orthogonal and unit length.  The 
      * determinant is always 1.  An orthonormal matrix is a pure rotation 
      * matrix.
      *
      * @returns
      *     Whether this matrix is orthonormal.
      */
      bool IsOrthonormal() const;

      /**
      * Compute the transpose of this matrix.  Columns become rows, rows 
      * become columns.
      *
      * @returns
      *     The transpose of this matrix.
      */
      Matrix2 Transpose() const;

      /**
      * Comupute the general inverse of this matrix.  This function will fail
      * silently if the matrix is singular.  See IsSingular().
      *
      * @returns
      *     The inverse of this matrix.
      */
      Matrix2 Inverse() const;

      /**
   	* Does a fast inverse, assuming the matrix only contains translation 
      * and rotation.  The inverse of a pure rotation matrix is its transpose
      * and the inverse of the translation is trivial.
      *
      * WARNING
      *    Returns invalid results if the matrix does not contain only 
      *    rotation.
      *
      * @returns
      *     The fast inverse of this matrix.
      */
      Matrix2 InverseFast() const;

      /**
      * Gets the scale elements of the matrix as a vector.
      *
      * @returns
      *     The scale of this matrix.
      */
      Vector2 GetScale() const;

      /**
      * Sets the scale elements of the matrix only.
      *
      * @param scale
      *     The scale to set the matrix scale to.
      * 
      * @returns
      *     A reference to this matrix.
      */
      Matrix2 &SetScale(const Vector2 &scale);

   private:
      float m[2][2];
   };

   /**
   * Tests two matrices for equality.
   *
   * @param lhs
   *     The first matrix to test for equality.
   * @param rhs
   *     The second matrix to test for equality.
   *
   * @returns
   *     Whether the matricies are equal.
   */
    bool operator==(const Matrix2 &lhs, const Matrix2 &rhs);

   /**
   * Tests two matrices for inequality.
   *
   * @param lhs
   *     The first matrix to test for inequality.
   * @param rhs
   *     The second matrix to test for inequality.
   *
   * @returns
   *     Whether the matricies are not equal.
   */
    bool operator!=(const Matrix2 &lhs, const Matrix2 &rhs);

   /**
   * Add two matrices to produce a new matrix.
   *
   * @param lhs
   *     The first matrix to add.
   * @param rhs
   *     The second matrix to add.
   *
   * @returns
   *     The sum of the two matrices.
   */
    Matrix2 operator+(const Matrix2 &lhs, const Matrix2 &rhs);

   /**
   * Subtract two matrices to produce a new matrix.
   *
   * @param lhs
   *     The matrix to subtract from.
   * @param rhs
   *     The matrix to subtract.
   *
   * @returns
   *     The matrix resulting from the subtraction.
   */
    Matrix2 operator-(const Matrix2 &lhs, const Matrix2 &rhs);

   /**
   * Negate a matrix to produce a new matrix.
   *
   * @param op
   *     The matrix to negate.
   *
   * @returns
   *     The negated matrix.
   */
    Matrix2 operator-(const Matrix2 &op);

   /**
   * Concatenate/multiply two matricies to produce a new matrix.
   *
   * @param lhs
   *     The first matrix to multiply.
   * @param rhs
   *     The second matrix to multiply.
   *
   * @returns
   *     The first matrix multiplied by the second matrix.
   */
    Matrix2 operator*(const Matrix2 &lhs, const Matrix2 &rhs);

   /**
   * Multiply a matrix by a scalar to produce a new matrix.
   *
   * @param lhs
   *     The matrix to multiply.
   * @param rhs
   *     The scalar to multiply the matrix by.
   *
   * @returns
   *     The result of the matrix multiplied by the scalar.
   */
    Matrix2 operator*(const Matrix2 &lhs, float rhs);

   /**
   * Multiply a scalar by a matrix to produce a new matrix.
   *
   * @param lhs
   *     The scalar to multiply.
   * @param rhs
   *     The matrix to multiply the scalar by.
   *
   * @returns
   *     The result of the scalar multiplied by the matrix.
   */
    Matrix2 operator*(float lhs, const Matrix2 &rhs);

   /**
   * Transforms the vector by the matrix
   *
   * @param lhs
   *     The matrix used to transform the vector.
   * @param rhs
   *     The vector to transform.
   *
   * @returns
   *     The transformed vector.
   */
    Vector2 operator*(const Matrix2 &lhs, const Vector2 &rhs);
}

#endif
