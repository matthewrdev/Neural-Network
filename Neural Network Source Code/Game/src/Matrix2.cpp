//****************************************************************************
//**
//**    $Workfile: Clarity_Matrix2.cpp $
//**
//**    This source file is part of Clarity.
//**    Clarity is a game engine designed for teaching.
//**    For the latest info, see http://members.optusnet.com.au/dfreya
//**
//**    Copyright (c) 2007 Dale Freya
//**
//**    This library is free software; you can redistribute it and/or
//**    modify it under the terms of the GNU Lesser General Public
//**    License as published by the Free Software Foundation; either
//**    version 2.1 of the License, or (at your option) any later version.
//**
//**    This library is distributed in the hope that it will be useful,
//**    but WITHOUT ANY WARRANTY; without even the implied warranty of
//**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//**    Lesser General Public License for more details.
//**
//**    You should have received a copy of the GNU Lesser General Public
//**    License along with this library; if not, write to the Free Software
//**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//**    or go to http://www.gnu.org/copyleft/lesser.txt.
//**
//**    This work is partially based on OGRE 
//**        (Object-oriented Graphics Rendering Engine)
//**        For the latest info, see http://www.ogre3d.org/
//**        OGRE is also covered by the GNU Lesser General Public License.
//**
//**    $Author: Dfreya $
//**    $Date: 2/04/06 11:03p $ 
//**    $Revision: 3 $
//**
//****************************************************************************

#include <Clarity/Math/Matrix2.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Matrix2 Matrix2::ZERO(
      0.0f, 0.0f,
      0.0f, 0.0f);

   const Matrix2 Matrix2::IDENTITY(
      1.0f, 0.0f,
      0.0f, 1.0f);

   Matrix2::Matrix2()
   {
   }

   Matrix2::Matrix2(
      float m11, float m12,
      float m21, float m22)
   {
      m[0][0] = m11;
      m[0][1] = m12;

      m[1][0] = m21;
      m[1][1] = m22;
   }

   Matrix2::Matrix2(const Matrix3 &rhs)
   {
      *this = rhs;
   }

   Matrix2::~Matrix2()
   {
   }

   Matrix2 &Matrix2::operator=(const Matrix3 &rhs)
   {
      m[0][0] = rhs(0, 0);
      m[0][1] = rhs(0, 1);

      m[1][0] = rhs(1, 0);
      m[1][1] = rhs(1, 1);

      return *this;
   }

   Matrix2 &Matrix2::Identity()
   {
      m[0][0] = 1.0f;   m[0][1] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;

      return *this;
   }

   Matrix2 &Matrix2::FromBasisVectors(
      const Vector2 &right, 
      const Vector2 &up)
   {
      m[0][0] = right.x;  m[0][1] = up.x;
      m[1][0] = right.y;  m[1][1] = up.y;

      return *this;
   }

   Matrix2 &Matrix2::FromRotation(float angle)
   {
      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = fCos;   m[0][1] = -fSin;
      m[1][0] = fSin;   m[1][1] = fCos;

      return *this;
   }

   Matrix2 &Matrix2::FromScale(const Vector2 &scale)
   {
      m[0][0] = scale.x;   m[0][1] = 0.0f;
      m[1][0] = 0.0f;      m[1][1] = scale.y;

      return *this;
   }

   float &Matrix2::operator()(int rowIdx, int colIdx)
   {
      assert(0 <= rowIdx && rowIdx <= 1 && 0 <= colIdx && colIdx <= 1);

      return m[rowIdx][colIdx];
   }

   float Matrix2::operator()(int rowIdx, int colIdx) const
   {
      assert(0 <= rowIdx && rowIdx <= 1 && 0 <= colIdx && colIdx <= 1);

      return m[rowIdx][colIdx];
   }

   Vector2 Matrix2::operator[](int basisIdx) const
   {
      assert(0 <= basisIdx && basisIdx <= 1);
      return Vector2(m[0][basisIdx], m[1][basisIdx]);
   }

   Vector2 Matrix2::GetRight() const
   {
      return Vector2(m[0][0], m[1][0]);
   }

   Vector2 Matrix2::GetUp() const
   {
      return Vector2(m[0][1], m[1][1]);
   }

   Matrix2 &Matrix2::operator+=(const Matrix2 &rhs)
   {
      for (int i = 0; i < 2; i++)
      {
         for (int j = 0; j < 2; j++)
         {
            m[i][j] += rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix2 &Matrix2::operator-=(const Matrix2 &rhs)
   {
      for (int i = 0; i < 2; i++)
      {
         for (int j = 0; j < 2; j++)
         {
            m[i][j] -= rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix2 &Matrix2::operator*=(const Matrix2 &rhs)
   {
      Matrix2 temp;
      temp = *this * rhs;
      *this = temp;
      return *this;
   }

   Matrix2 &Matrix2::operator*=(float rhs)
   {
      for (int i = 0; i < 2; i++)
      {
         for (int j = 0; j < 2; j++)
         {
            m[i][j] *= rhs;
         }
      }

      return *this;
   }

   float Matrix2::Determinant() const
   {
      return m[0][0] * m[1][1] - m[0][1] * m[1][0];
   }

   bool Matrix2::IsSingular() const
   {
      return (Determinant() == 0);
   }

	bool Matrix2::IsOrthogonal() const
   {
      // Determinant is 1 or -1
      return Abs(1.0f - Abs(Determinant())) < EPSILON;
   }

   bool Matrix2::IsOrthonormal() const
   {
      // Determinant is 1
      return Abs(1.0f - Determinant()) < EPSILON;
   }

   Matrix2 Matrix2::Transpose() const
   {
      return Matrix2(
         m[0][0], m[1][0],
         m[0][1], m[1][1]);
   }

   Matrix2 Matrix2::Inverse() const
   {
      float det = Determinant();

      assert(det != 0.0f);

      float invDet = 1.0f / det;

      return Matrix2(
         m[1][1] *  invDet, m[0][1] * -invDet,
         m[1][0] * -invDet, m[0][0] *  invDet);
   }

   Matrix2 Matrix2::InverseFast() const
   {
      // assert: matrix is orthonormal
      return Transpose();
   }

   Vector2 Matrix2::GetScale() const
   {
      return Vector2(m[0][0], m[1][1]);
   }

   Matrix2 &Matrix2::SetScale(const Vector2 &scale)
   {
      m[0][0] = scale.x;
      m[1][1] = scale.y;

      return *this;
   }

   bool operator==(const Matrix2 &lhs, const Matrix2 &rhs)
   {
      for (int row = 0; row < 2; row++)
      {
         for (int col = 0; col < 2; col++)
         {
            if (lhs(row, col) != rhs(row, col))
               return false;
         }
      }

      return true;
   }

   bool operator!=(const Matrix2 &lhs, const Matrix2 &rhs)
   {
      return !(lhs == rhs);
   }

   Matrix2 operator+(const Matrix2 &lhs, const Matrix2 &rhs)
   {
      Matrix2 result(lhs);
      result += rhs;
      return result;
   }

   Matrix2 operator-(const Matrix2 &lhs, const Matrix2 &rhs)
   {
      Matrix2 result(lhs);
      result -= rhs;
      return result;
   }

   Matrix2 operator-(const Matrix2 &op)
   {
      Matrix2 result(op);

      for (int row = 0; row < 2; row++)
      {
         for (int col = 0; col < 2; col++)
         {
            result(row, col) = -result(row, col);
         }
      }

      return result;
   }

   Matrix2 operator*(const Matrix2 &lhs, const Matrix2 &rhs)
   {
      Matrix2 result;

      for (int row = 0; row < 2; row++)
      {
         for (int col = 0; col < 2; col++)
         {
            result(row, col) =
               lhs(row, 0) * rhs(0, col) +
               lhs(row, 1) * rhs(1, col);
         }
      }

      return result;
   }

   Matrix2 operator*(const Matrix2 &lhs, float rhs)
   {
      Matrix2 result(lhs);
      result *= rhs;
      return result;
   }

   Matrix2 operator*(float lhs, const Matrix2 &rhs)
   {
      return rhs * lhs;
   }

   Vector2 operator*(const Matrix2 &lhs, const Vector2 &rhs)
   {
      return rhs.Transform(lhs);
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
