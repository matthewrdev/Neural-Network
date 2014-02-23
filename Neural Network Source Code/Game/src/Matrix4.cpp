//****************************************************************************
//**
//**    $Workfile: Clarity_Matrix4.cpp $
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

#include <Clarity/Math/Matrix4.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Vector3.h>
#include <Clarity/Math/Vector4.h>
#include <Clarity/Math/Quaternion.h>
#include <Clarity/Math/EulerAngle.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Matrix4 Matrix4::ZERO(
      0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f);

   const Matrix4 Matrix4::IDENTITY(
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f);

   Matrix4::Matrix4()
   {
   }

   Matrix4::Matrix4(
      float m11, float m12, float m13, float m14,
      float m21, float m22, float m23, float m24,
      float m31, float m32, float m33, float m34,
      float m41, float m42, float m43, float m44)
   {

      m[0][0] = m11;
      m[0][1] = m12;
      m[0][2] = m13;
      m[0][3] = m14;

      m[1][0] = m21;
      m[1][1] = m22;
      m[1][2] = m23;
      m[1][3] = m24;

      m[2][0] = m31;
      m[2][1] = m32;
      m[2][2] = m33;
      m[2][3] = m34;

      m[3][0] = m41;
      m[3][1] = m42;
      m[3][2] = m43;
      m[3][3] = m44;
   }

   Matrix4::Matrix4(const Matrix3 &rhs)
   {
      *this = rhs;
   }

   Matrix4::Matrix4(const Matrix3 &rhs, const Vector3 &translation)
   {
      m[0][0] = rhs(0, 0);  m[0][1] = rhs(0, 1);  m[0][2] = rhs(0, 2);  m[0][3] = translation.x;
      m[1][0] = rhs(1, 0);  m[1][1] = rhs(1, 1);  m[1][2] = rhs(1, 2);  m[1][3] = translation.y;
      m[2][0] = rhs(2, 0);  m[2][1] = rhs(2, 1);  m[2][2] = rhs(2, 2);  m[2][3] = translation.z;
      m[3][0] = 0.0f;       m[3][1] = 0.0f;       m[3][2] = 0.0f;       m[3][3] = 1.0f;
   }

   Matrix4::~Matrix4()
   {
   }

   Matrix4 &Matrix4::operator=(const Matrix3 &rhs)
   {
      m[0][0] = rhs(0, 0);  m[0][1] = rhs(0, 1);  m[0][2] = rhs(0, 2);  m[0][3] = 0.0f;
      m[1][0] = rhs(1, 0);  m[1][1] = rhs(1, 1);  m[1][2] = rhs(1, 2);  m[1][3] = 0.0f;
      m[2][0] = rhs(2, 0);  m[2][1] = rhs(2, 1);  m[2][2] = rhs(2, 2);  m[2][3] = 0.0f;
      m[3][0] = 0.0f;       m[3][1] = 0.0f;       m[3][2] = 0.0f;       m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::Identity()
   {
      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] = 0.0f;   m[1][3] = 0.0f;
      m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = 1.0f;   m[2][3] = 0.0f;
      m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromBasisVectors(
      const Vector3 &right, 
      const Vector3 &up, 
      const Vector3 &forward)
   {
      m[0][0] = right.x;  m[0][1] = up.x;  m[0][2] = forward.x;  m[0][3] = 0.0f;
      m[1][0] = right.y;  m[1][1] = up.y;  m[1][2] = forward.y;  m[1][3] = 0.0f;
      m[2][0] = right.z;  m[2][1] = up.z;  m[2][2] = forward.z;  m[2][3] = 0.0f;
      m[3][0] = 0.0f;     m[3][1] = 0.0f;  m[3][2] = 0.0f;       m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromTranslation(const Vector3 &v)
   {
      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = v.x;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] = 0.0f;   m[1][3] = v.y;
      m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = 1.0f;   m[2][3] = v.z;
      m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromQuaternion(const Quaternion &q)
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
      m[0][3] = 0.0f;

      m[1][0] = xy + wz;
      m[1][1] = 1.0f - (xx + zz);
      m[1][2] = yz - wx;
      m[1][3] = 0.0f;

      m[2][0] = xz - wy;
      m[2][1] = yz + wx;
      m[2][2] = 1.0f - (xx + yy);
      m[2][3] = 0.0f;

      m[3][0] = 0.0f;
      m[3][1] = 0.0f;
      m[3][2] = 0.0f;
      m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromEulerAngle(const EulerAngle &euler)
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

   Matrix4 &Matrix4::FromRotationX(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RX =    1       0       0
      //           0     cos(t) -sin(t)
      //           0     sin(t)  cos(t)
      // where t > 0 indicates a counterclockwise rotation in the yz-plane

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = 1.0f;   m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = fCos;   m[1][2] = -fSin;  m[1][3] = 0.0f;
      m[2][0] = 0.0f;   m[2][1] = fSin;   m[2][2] = fCos;   m[2][3] = 0.0f;
      m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromRotationY(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RY =  cos(t)    0     sin(t)
      //           0       1       0
      //        -sin(t)    0     cos(t)
      // where t > 0 indicates a counterclockwise rotation in the zx-plane

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = fCos;   m[0][1] = 0.0f;   m[0][2] = fSin;   m[0][3] = 0.0f;
      m[1][0] = 0.0f;   m[1][1] = 1.0f;   m[1][2] = 0.0f;   m[1][3] = 0.0f;
      m[2][0] = -fSin;  m[2][1] = 0.0f;   m[2][2] = fCos;   m[2][3] = 0.0f;
      m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromRotationZ(float angle)
   {
      // NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
      // Coordinate axis rotation matrices are of the form
      //   RZ =  cos(t) -sin(t)    0
      //         sin(t)  cos(t)    0
      //           0       0       1
      // where t > 0 indicates a counterclockwise rotation in the xy-plane.

      float fCos = Cos(angle);
      float fSin = Sin(angle);

      m[0][0] = fCos;   m[0][1] = -fSin;  m[0][2] = 0.0f;   m[0][3] = 0.0f;
      m[1][0] = fSin;   m[1][1] =  fCos;  m[1][2] = 0.0f;   m[1][3] = 0.0f;
      m[2][0] = 0.0f;   m[2][1] =  0.0f;  m[2][2] = 1.0f;   m[2][3] = 0.0f;
      m[3][0] = 0.0f;   m[3][1] =  0.0f;  m[3][2] = 0.0f;   m[3][3] = 1.0f;

      return *this;
   }

   Matrix4 &Matrix4::FromScale(const Vector3 &scale)
   {
      m[0][0] = scale.x;   m[0][1] = 0.0f;      m[0][2] = 0.0f;      m[0][3] = 0.0f;
      m[1][0] = 0.0f;      m[1][1] = scale.y;   m[1][2] = 0.0f;      m[1][3] = 0.0f;
      m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = scale.z;   m[2][3] = 0.0f;
      m[3][0] = 0.0f;      m[3][1] = 0.0f;      m[3][2] = 0.0f;      m[3][3] = 1.0f;

      return *this;
   }

   float &Matrix4::operator()(int rowIdx, int colIdx)
   {
      assert(0 <= rowIdx && rowIdx <= 3 && 0 <= colIdx && colIdx <= 3);

      return m[rowIdx][colIdx];
   }

   float Matrix4::operator()(int rowIdx, int colIdx) const
   {
      assert(0 <= rowIdx && rowIdx <= 3 && 0 <= colIdx && colIdx <= 3);

      return m[rowIdx][colIdx];
   }

   Vector3 Matrix4::operator[](int basisIdx) const
   {
      assert(0 <= basisIdx && basisIdx <= 3);
      return Vector3(m[0][basisIdx], m[1][basisIdx], m[2][basisIdx]);
   }

   Vector3 Matrix4::GetRight() const
   {
      return Vector3(m[0][0], m[1][0], m[2][0]);
   }

   Vector3 Matrix4::GetUp() const
   {
      return Vector3(m[0][1], m[1][1], m[2][1]);
   }

   Vector3 Matrix4::GetForward() const
   {
      return Vector3(m[0][2], m[1][2], m[2][2]);
   }

   Matrix4 &Matrix4::operator+=(const Matrix4 &rhs)
   {
      for (int i = 0; i < 4; i++)
      {
         for (int j = 0; j < 4; j++)
         {
            m[i][j] += rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix4 &Matrix4::operator-=(const Matrix4 &rhs)
   {
      for (int i = 0; i < 4; i++)
      {
         for (int j = 0; j < 4; j++)
         {
            m[i][j] -= rhs.m[i][j];
         }
      }

      return *this;
   }

   Matrix4 &Matrix4::operator*=(const Matrix4 &rhs)
   {
      Matrix4 temp;
      temp = *this * rhs;
      *this = temp;
      return *this;
   }

   Matrix4 &Matrix4::operator*=(float rhs)
   {
      for (int i = 0; i < 4; i++)
      {
         for (int j = 0; j < 4; j++)
         {
            m[i][j] *= rhs;
         }
      }

      return *this;
   }

   float Matrix4::Determinant() const
   {
      return 
         m[0][0] * MinorDeterminant(1, 2, 3, 1, 2, 3) -
         m[0][1] * MinorDeterminant(1, 2, 3, 0, 2, 3) +
         m[0][2] * MinorDeterminant(1, 2, 3, 0, 1, 3) -
         m[0][3] * MinorDeterminant(1, 2, 3, 0, 1, 2);
   }

   bool Matrix4::IsSingular() const
   {
      return (Determinant() == 0);
   }

   bool Matrix4::IsOrthogonal() const
   {
      // Determinant is 1 or -1
      return Abs(1.0f - Abs(Determinant())) < EPSILON;
   }

   bool Matrix4::IsOrthonormal() const
   {
      // Determinant is 1
      return Abs(1.0f - Determinant()) < EPSILON;
   }

   float Matrix4::MinorDeterminant(
      const int r0, const int r1, const int r2, 
      const int c0, const int c1, const int c2) const
   {
      return 
         m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
         m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
         m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
   }

   Matrix4 Matrix4::Transpose() const
   {
      return Matrix4(
         m[0][0], m[1][0], m[2][0], m[3][0],
         m[0][1], m[1][1], m[2][1], m[3][1],
         m[0][2], m[1][2], m[2][2], m[3][2],
         m[0][3], m[1][3], m[2][3], m[3][3]);
   }

   Matrix4 Matrix4::Adjoint() const
   {
      return Matrix4( 
         MinorDeterminant(1, 2, 3, 1, 2, 3),
         -MinorDeterminant(0, 2, 3, 1, 2, 3),
         MinorDeterminant(0, 1, 3, 1, 2, 3),
         -MinorDeterminant(0, 1, 2, 1, 2, 3),

         -MinorDeterminant(1, 2, 3, 0, 2, 3),
         MinorDeterminant(0, 2, 3, 0, 2, 3),
         -MinorDeterminant(0, 1, 3, 0, 2, 3),
         MinorDeterminant(0, 1, 2, 0, 2, 3),

         MinorDeterminant(1, 2, 3, 0, 1, 3),
         -MinorDeterminant(0, 2, 3, 0, 1, 3),
         MinorDeterminant(0, 1, 3, 0, 1, 3),
         -MinorDeterminant(0, 1, 2, 0, 1, 3),

         -MinorDeterminant(1, 2, 3, 0, 1, 2),
         MinorDeterminant(0, 2, 3, 0, 1, 2),
         -MinorDeterminant(0, 1, 3, 0, 1, 2),
         MinorDeterminant(0, 1, 2, 0, 1, 2));
   }

   Matrix4 Matrix4::Inverse() const
   {
      float minorDeterminant123123 = MinorDeterminant(1, 2, 3, 1, 2, 3);
      float minorDeterminant123023 = MinorDeterminant(1, 2, 3, 0, 2, 3);
      float minorDeterminant123013 = MinorDeterminant(1, 2, 3, 0, 1, 3);
      float minorDeterminant123012 = MinorDeterminant(1, 2, 3, 0, 1, 2);

      float determinant = 
         m[0][0] * minorDeterminant123123 -
         m[0][1] * minorDeterminant123023 +
         m[0][2] * minorDeterminant123013 -
         m[0][3] * minorDeterminant123012;

      Matrix4 adjoint( 
         minorDeterminant123123,
         -MinorDeterminant(0, 2, 3, 1, 2, 3),
         MinorDeterminant(0, 1, 3, 1, 2, 3),
         -MinorDeterminant(0, 1, 2, 1, 2, 3),

         -minorDeterminant123023,
         MinorDeterminant(0, 2, 3, 0, 2, 3),
         -MinorDeterminant(0, 1, 3, 0, 2, 3),
         MinorDeterminant(0, 1, 2, 0, 2, 3),

         minorDeterminant123013,
         -MinorDeterminant(0, 2, 3, 0, 1, 3),
         MinorDeterminant(0, 1, 3, 0, 1, 3),
         -MinorDeterminant(0, 1, 2, 0, 1, 3),

         -minorDeterminant123012,
         MinorDeterminant(0, 2, 3, 0, 1, 2),
         -MinorDeterminant(0, 1, 3, 0, 1, 2),
         MinorDeterminant(0, 1, 2, 0, 1, 2));

      return adjoint * (1.0f / determinant);
   }

   Matrix4 Matrix4::InverseFast() const
   {
      // assert: only rotation and translation

      // First calculate the inverse of the rotation section by transposing
      Matrix3 inverse3x3(*this);
      inverse3x3.Transpose();

      // Next caculate the translation inverse
      Vector3 translation = -GetTranslation();
      translation = translation.Transform(inverse3x3);

      // Next generate the 4x4 inverse by combining the rotation with the translation
      return Matrix4(inverse3x3, translation);
   }

   Matrix4 &Matrix4::Orthonormalize()
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

   Vector3 Matrix4::GetTranslation() const
   {
      return Vector3(m[0][3], m[1][3], m[2][3]);
   }

   Vector3 Matrix4::GetScale() const
   {
      return Vector3(m[0][0], m[1][1], m[2][2]);
   }

   Matrix4 &Matrix4::SetTranslation(const Vector3 &translation)
   {
      m[0][3] = translation.x;
      m[1][3] = translation.y;
      m[2][3] = translation.z;

      return *this;
   }

   Matrix4 &Matrix4::SetScale(const Vector3 &scale)
   {
      m[0][0] = scale.x;
      m[1][1] = scale.y;
      m[2][2] = scale.z;

      return *this;
   }

   bool operator==(const Matrix4 &lhs, const Matrix4 &rhs)
   {
      for (int row = 0; row < 4; row++)
      {
         for (int col = 0; col < 4; col++)
         {
            if (lhs(row, col) != rhs(row, col))
               return false;
         }
      }

      return true;
   }

   bool operator!=(const Matrix4 &lhs, const Matrix4 &rhs)
   {
      return !(lhs == rhs);
   }

   Matrix4 operator+(const Matrix4 &lhs, const Matrix4 &rhs)
   {
      Matrix4 result(lhs);
      result += rhs;
      return result;
   }

   Matrix4 operator-(const Matrix4 &lhs, const Matrix4 &rhs)
   {
      Matrix4 result(lhs);
      result -= rhs;
      return result;
   }

   Matrix4 operator-(const Matrix4 &op)
   {
      Matrix4 result(op);

      for (int row = 0; row < 4; row++)
      {
         for (int col = 0; col < 4; col++)
         {
            result(row, col) = -result(row, col);
         }
      }

      return result;
   }

   Matrix4 operator*(const Matrix4 &lhs, const Matrix4 &rhs)
   {
      Matrix4 result;

      for (int row = 0; row < 4; row++)
      {
         for (int col = 0; col < 4; col++)
         {
            result(row, col) =
               lhs(row, 0) * rhs(0, col) +
               lhs(row, 1) * rhs(1, col) +
               lhs(row, 2) * rhs(2, col) +
               lhs(row, 3) * rhs(3, col);
         }
      }

      return result;
   }

   Matrix4 operator*(const Matrix4 &lhs, float rhs)
   {
      Matrix4 result(lhs);
      result *= rhs;
      return result;
   }

   Matrix4 operator*(float lhs, const Matrix4 &rhs)
   {
      return rhs * lhs;
   }

   Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs)
   {
      return Vector3(rhs.Transform(lhs));
   }

   Vector4 operator*(const Matrix4 &lhs, const Vector4 &rhs)
   {
      return Vector4(rhs.Transform(lhs));
   }

   std::ostream &operator<<(std::ostream &lhs, const Matrix4 &rhs)
   {
      lhs << "Matrix4(";

      for (int i = 0; i < 4; ++i)
      {
         lhs << " row" << i << "{";

         for(int j = 0; j < 4; ++j)
         {
            lhs << rhs(i, j) << " ";
         }

         lhs << "}";
      }

      lhs << ")";

      return lhs;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
