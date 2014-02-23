//****************************************************************************
//**
//**    $Workfile: Clarity_Matrix3.cpp $
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
//**    $Date: 11/12/06 5:08p $ 
//**    $Revision: 3 $
//**
//****************************************************************************

#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Matrix4.h>
#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Vector3.h>
#include <Clarity/Math/Vector4.h>
#include <Clarity/Math/Quaternion.h>
#include <Clarity/Math/EulerAngle.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Matrix3 Matrix3::ZERO(
      0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f);

   const Matrix3 Matrix3::IDENTITY(
      1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f);

   Matrix3::Matrix3()
   {
   }

   Matrix3::Matrix3(
      float m11, float m12, float m13,
      float m21, float m22, float m23,
      float m31, float m32, float m33)
   {
      m[0][0] = m11;
      m[0][1] = m12;
      m[0][2] = m13;

      m[1][0] = m21;
      m[1][1] = m22;
      m[1][2] = m23;

      m[2][0] = m31;
      m[2][1] = m32;
      m[2][2] = m33;
   }

   Matrix3::Matrix3(const Matrix4 &rhs)
   {
      *this = rhs;
   }

   Matrix3::~Matrix3()
   {
   }

   Matrix3 &Matrix3::operator=(const Matrix4 &rhs)
   {
      m[0][0] = rhs(0, 0);
      m[0][1] = rhs(0, 1);
      m[0][2] = rhs(0, 2);

      m[1][0] = rhs(1, 0);
      m[1][1] = rhs(1, 1);
      m[1][2] = rhs(1, 2);

      m[2][0] = rhs(2, 0);
      m[2][1] = rhs(2, 1);
      m[2][2] = rhs(2, 2);

      return *this;
   }

   Matrix3 &Matrix3::Identity()
   {
      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] = 0.0f;
      m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = 1.0f;

      return *this;
   }

   Matrix3 &Matrix3::FromBasisVectors(
      const Vector3 &right, 
      const Vector3 &up, 
      const Vector3 &forward)
   {
      m[0][0] = right.x;  m[0][1] = up.x;  m[0][2] = forward.x;
      m[1][0] = right.y;  m[1][1] = up.y;  m[1][2] = forward.y;
      m[2][0] = right.z;  m[2][1] = up.z;  m[2][2] = forward.z;

      return *this;
   }

   Matrix3 &Matrix3::FromTranslation(const Vector2 &v)
   {
      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] =  v.x;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] =  v.y;
      m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = 1.0f;

      return *this;
   }

   Matrix3 &Matrix3::FromQuaternion(const Quaternion &q)
   {
      float x  = 2.0f * q.x;
      float y  = 2.0f * q.y;
      float z  = 2.0f * q.z;
      float wx = x * q.w;
      float wy = y * q.w;
      float wz = z * q.w;
      float xx = x * q.x;
      float xy = y * q.x;
      float xz = z * q.x;
      float yy = y * q.y;
      float yz = z * q.y;
      float zz = z * q.z;

      m[0][0] = 1.0f - (yy + zz);
      m[0][1] = xy - wz;
      m[0][2] = xz + wy;

      m[1][0] = xy + wz;
      m[1][1] = 1.0f - (xx + zz);
      m[1][2] = yz - wx;

      m[2][0] = xz - wy;
      m[2][1] = yz + wx;
      m[2][2] = 1.0f - (xx + yy);

      return *this;
   }

   Matrix3 &Matrix3::FromEulerAngle(const EulerAngle &euler)
   {
      float fCos, fSin;

      fCos = Cos(euler.yaw);
      fSin = Sin(euler.yaw);
      Matrix3 yMatrix(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

      fCos = Cos(euler.pitch);
      fSin = Sin(euler.pitch);
      Matrix3 xMatrix(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

      fCos = Cos(euler.roll);
      fSin = Sin(euler.roll);
      Matrix3 zMatrix(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

      *this = yMatrix * (xMatrix * zMatrix);

      return *this;
   }

   Matrix3 &Matrix3::FromRotationX(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RX =    1       0       0
      //           0     cos(t) -sin(t)
      //           0     sin(t)  cos(t)
      // where t > 0 indicates a counterclockwise rotation in the yz-plane

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = fCos;   m[1][2] = -fSin;
      m[2][0] = 0.0f;   m[2][1] = fSin;   m[2][2] = fCos;

      return *this;
   }

   Matrix3 &Matrix3::FromRotationY(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RY =  cos(t)    0     sin(t)
      //           0       1       0
      //        -sin(t)    0     cos(t)
      // where t > 0 indicates a counterclockwise rotation in the zx-plane

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = fCos;   m[0][1] = 0.0f;   m[0][2] = fSin;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] = 0.0f;
      m[2][0] = -fSin;  m[2][1] = 0.0f;   m[2][2] = fCos;

      return *this;
   }

   Matrix3 &Matrix3::FromRotationZ(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RZ =  cos(t) -sin(t)    0
      //         sin(t)  cos(t)    0
      //           0       0       1
      // where t > 0 indicates a counterclockwise rotation in the xy-plane.

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = fCos;   m[0][1] = -fSin;  m[0][2] = 0.0f;
      m[1][0] = fSin;   m[1][1] =  fCos;  m[1][2] = 0.0f;
      m[2][0] = 0.0f;   m[2][1] =  0.0f;  m[2][2] = 1.0f;

      return *this;
   }

   Matrix3 &Matrix3::FromScale2(const Vector2 &scale)
   {
      m[0][0] = scale.x;   m[0][1] = 0.0f;      m[0][2] = 0.0f;
      m[1][0] = 0.0f;      m[1][1] = scale.y;   m[1][2] = 0.0f;
      m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = 1.0f;

      return *this;
   }

   Matrix3 &Matrix3::FromScale(const Vector3 &scale)
   {
      m[0][0] = scale.x;   m[0][1] = 0.0f;      m[0][2] = 0.0f;
      m[1][0] = 0.0f;      m[1][1] = scale.y;   m[1][2] = 0.0f;
      m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = scale.z;

      return *this;
   }

   float &Matrix3::operator()(int rowIdx, int colIdx)
   {
      assert(0 <= rowIdx && rowIdx <= 2 && 0 <= colIdx && colIdx <= 2);

      return m[rowIdx][colIdx];
   }

   float Matrix3::operator()(int rowIdx, int colIdx) const
   {
      assert(0 <= rowIdx && rowIdx <= 2 && 0 <= colIdx && colIdx <= 2);

      return m[rowIdx][colIdx];
   }

   Vector3 Matrix3::operator[](int basisIdx) const
   {
      assert(0 <= basisIdx && basisIdx <= 2);
      return Vector3(m[0][basisIdx], m[1][basisIdx], m[2][basisIdx]);
   }

   Vector3 Matrix3::GetRight() const
   {
      return Vector3(m[0][0], m[1][0], m[2][0]);
   }

   Vector3 Matrix3::GetUp() const
   {
      return Vector3(m[0][1], m[1][1], m[2][1]);
   }

   Vector3 Matrix3::GetForward() const
   {
      return Vector3(m[0][2], m[1][2], m[2][2]);
   }

   Matrix3 &Matrix3::operator+=(const Matrix3 &rhs)
   {
      for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < 3; j++)
         {
            m[i][j] += rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix3 &Matrix3::operator-=(const Matrix3 &rhs)
   {
      for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < 3; j++)
         {
            m[i][j] -= rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix3 &Matrix3::operator*=(const Matrix3 &rhs)
   {
      Matrix3 temp;
      temp = *this * rhs;
      *this = temp;
      return *this;
   }

   Matrix3 &Matrix3::operator*=(float rhs)
   {
      for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < 3; j++)
         {
            m[i][j] *= rhs;
         }
      }

      return *this;
   }

   float Matrix3::Determinant() const
   {
      float cofactor00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
      float cofactor10 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
      float cofactor20 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

      return m[0][0] * cofactor00 + m[0][1] * cofactor10 + m[0][2] * cofactor20;
   }

   bool Matrix3::IsSingular() const
   {
      return (Determinant() == 0);
   }

	bool Matrix3::IsOrthogonal(float tolerance) const
   {
      // Determinant is 1 or -1
      return Abs(1.0f - Abs(Determinant())) < tolerance;
   }

   bool Matrix3::IsOrthonormal(float tolerance) const
   {
      // Determinant is 1
      return Abs(1.0f - Determinant()) < tolerance;
   }

   Matrix3 Matrix3::Transpose() const
   {
      return Matrix3(
         m[0][0], m[1][0], m[2][0],
         m[0][1], m[1][1], m[2][1],
         m[0][2], m[1][2], m[2][2]);
   }

   Matrix3 Matrix3::Inverse() const
   {
      // Invert a 3x3 using cofactors.  This is about 8 times faster than
      // the Numerical Recipes code which uses Gaussian elimination.

      Matrix3 inverse;

      inverse.m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
      inverse.m[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
      inverse.m[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
      inverse.m[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
      inverse.m[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
      inverse.m[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
      inverse.m[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
      inverse.m[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
      inverse.m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

      float determinant =
         m[0][0] * inverse.m[0][0] +
         m[0][1] * inverse.m[1][0]+
         m[0][2] * inverse.m[2][0];

      assert(Abs(determinant) != 0.0f);

      float inverseDeterminant = 1.0f / determinant;

      for (int row = 0; row < 3; row++)
      {
         for (int col = 0; col < 3; col++)
         {
            inverse.m[row][col] *= inverseDeterminant;
         }
      }

      return inverse;
   }

   Matrix3 Matrix3::InverseFast() const
   {
      // assert: matrix is orthonormal
      return Transpose();
   }

   Matrix3 &Matrix3::Orthonormalize()
   {
      // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
      // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
      //
      //   q0 = m0/|m0|
      //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
      //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
      //
      // where |V| indicates length of vector V and A*B indicates dot
      // product of vectors A and B.

      // compute q0
      float fInvLength = InvSqrt(
         m[0][0] * m[0][0] + 
         m[1][0] * m[1][0] +
         m[2][0] * m[2][0]);

      m[0][0] *= fInvLength;
      m[1][0] *= fInvLength;
      m[2][0] *= fInvLength;

      // compute q1
      float fDot0 =
         m[0][0] * m[0][1] +
         m[1][0] * m[1][1] +
         m[2][0] * m[2][1];

      m[0][1] -= fDot0 * m[0][0];
      m[1][1] -= fDot0 * m[1][0];
      m[2][1] -= fDot0 * m[2][0];

      fInvLength = InvSqrt(
         m[0][1] * m[0][1] +
         m[1][1] * m[1][1] +
         m[2][1] * m[2][1]);

      m[0][1] *= fInvLength;
      m[1][1] *= fInvLength;
      m[2][1] *= fInvLength;

      // compute q2
      float fDot1 =
         m[0][1] * m[0][2] +
         m[1][1] * m[1][2] +
         m[2][1] * m[2][2];

      fDot0 =
         m[0][0] * m[0][2] +
         m[1][0] * m[1][2] +
         m[2][0] * m[2][2];

      m[0][2] -= fDot0 * m[0][0] + fDot1 * m[0][1];
      m[1][2] -= fDot0 * m[1][0] + fDot1 * m[1][1];
      m[2][2] -= fDot0 * m[2][0] + fDot1 * m[2][1];

      fInvLength = InvSqrt(
         m[0][2] * m[0][2] +
         m[1][2] * m[1][2] +
         m[2][2] * m[2][2]);

      m[0][2] *= fInvLength;
      m[1][2] *= fInvLength;
      m[2][2] *= fInvLength;

      return *this;
   }

   Vector3 Matrix3::GetScale() const
   {
      return Vector3(m[0][0], m[1][1], m[2][2]);
   }

   Matrix3 &Matrix3::SetScale(const Vector3 &scale)
   {
      m[0][0] = scale.x;
      m[1][1] = scale.y;
      m[2][2] = scale.z;

      return *this;
   }

   bool operator==(const Matrix3 &lhs, const Matrix3 &rhs)
   {
      for (int row = 0; row < 3; row++)
      {
         for (int col = 0; col < 3; col++)
         {
            if (lhs(row, col) != rhs(row, col))
               return false;
         }
      }

      return true;
   }

   bool operator!=(const Matrix3 &lhs, const Matrix3 &rhs)
   {
      return !(lhs == rhs);
   }

   Matrix3 operator+(const Matrix3 &lhs, const Matrix3 &rhs)
   {
      Matrix3 result(lhs);
      result += rhs;
      return result;
   }

   Matrix3 operator-(const Matrix3 &lhs, const Matrix3 &rhs)
   {
      Matrix3 result(lhs);
      result -= rhs;
      return result;
   }

   Matrix3 operator-(const Matrix3 &op)
   {
      Matrix3 result(op);

      for (int row = 0; row < 3; row++)
      {
         for (int col = 0; col < 3; col++)
         {
            result(row, col) = -result(row, col);
         }
      }

      return result;
   }

   Matrix3 operator*(const Matrix3 &lhs, const Matrix3 &rhs)
   {
      Matrix3 result;

      for (int row = 0; row < 3; row++)
      {
         for (int col = 0; col < 3; col++)
         {
            result(row, col) =
               lhs(row, 0) * rhs(0, col) +
               lhs(row, 1) * rhs(1, col) +
               lhs(row, 2) * rhs(2, col);
         }
      }

      return result;
   }

   Matrix3 operator*(const Matrix3 &lhs, float rhs)
   {
      Matrix3 result(lhs);
      result *= rhs;
      return result;
   }

   Matrix3 operator*(float lhs, const Matrix3 &rhs)
   {
      return rhs * lhs;
   }

   Vector2 operator*(const Matrix3 &lhs, const Vector2 &rhs)
   {
      return Vector2(rhs.Transform(lhs));
   }

   Vector3 operator*(const Matrix3 &lhs, const Vector3 &rhs)
   {
      return rhs.Transform(lhs);
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
