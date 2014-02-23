//****************************************************************************
//**
//**    $Workfile: Clarity_Vector3.cpp $
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

#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Vector3.h>
#include <Clarity/Math/Vector4.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Matrix4.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Vector3 Vector3::ZERO(0, 0, 0);
   const Vector3 Vector3::UNIT_X(1, 0, 0);
   const Vector3 Vector3::UNIT_Y(0, 1, 0);
   const Vector3 Vector3::UNIT_Z(0, 0, 1);
   const Vector3 Vector3::NEGATIVE_UNIT_X(-1, 0, 0);
   const Vector3 Vector3::NEGATIVE_UNIT_Y(0, -1, 0);
   const Vector3 Vector3::NEGATIVE_UNIT_Z(0, 0, -1);
   const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

   Vector3::Vector3()
   {
      *this = ZERO;
   }

   Vector3::Vector3(float xIn, float yIn, float zIn)
   {
      Set(xIn, yIn, zIn);
   }

   Vector3::Vector3(const Vector4 &v4)
   {
      *this = v4;
   }

   Vector3::Vector3(const Vector2 &rhs, float z)
   {
      this->x = rhs.x;
      this->y = rhs.y;
      this->z = z;
   }

   Vector3::~Vector3()
   {
   }

   Vector3 &Vector3::operator=(const Vector4 &rhs)
   {
      assert(rhs.w != 0.0f);

      float invw = 1.0f / rhs.w;

      x = rhs.x * invw;
      y = rhs.y * invw;
      z = rhs.z * invw;

      return *this;
   }

   float Vector3::operator[](int idx) const
   {
      assert(0 <= idx && idx <= 2);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
         return y;

      case 2:
      default:
         return z;
      }
   }

   float &Vector3::operator[](int idx)
   {
      assert(0 <= idx && idx <= 2);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
         return y;

      case 2:
      default:
         return z;
      }
   }


   void Vector3::Set(float xIn, float yIn, float zIn)
   {
      x = xIn;
      y = yIn;
      z = zIn;
   }

   Vector3 &Vector3::operator*=(const Vector3 &rhs)
   {
      x *= rhs.x;
      y *= rhs.y;
      z *= rhs.z;

      return *this;
   }

   Vector3 &Vector3::operator/=(const Vector3 &rhs)
   {
      assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0);
      x /= rhs.x;
      y /= rhs.y;
      z /= rhs.z;

      return *this;
   }

   Vector3 &Vector3::operator+=(const Vector3 &rhs)
   {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;

      return *this;
   }

   Vector3 &Vector3::operator-=(const Vector3 &rhs)
   {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;

      return *this;
   }

   Vector3 &Vector3::operator*=(float rhs)
   {
      x *= rhs;
      y *= rhs;
      z *= rhs;

      return *this;
   }

   Vector3 &Vector3::operator/=(float rhs)
   {
      assert(rhs != 0);

      float invrhs = 1.0f / rhs;
      *this *= invrhs;

      return *this;
   }

   Vector3 Vector3::Transform(const Matrix3 &lhs) const
   {
      return Vector3(
         lhs(0, 0) * x + lhs(0, 1) * y + lhs(0, 2) * z,
         lhs(1, 0) * x + lhs(1, 1) * y + lhs(1, 2) * z,
         lhs(2, 0) * x + lhs(2, 1) * y + lhs(2, 2) * z);
   }

   Vector3 Vector3::Transform(const Matrix4 &lhs) const
   {
      Vector3 result;

      result.x = x * lhs(0, 0) + y * lhs(0, 1) + z * lhs(0, 2) + lhs(0, 3);
      result.y = x * lhs(1, 0) + y * lhs(1, 1) + z * lhs(1, 2) + lhs(1, 3);
      result.z = x * lhs(2, 0) + y * lhs(2, 1) + z * lhs(2, 2) + lhs(2, 3);

      return result;
   }

   Vector3 Vector3::TransformVector(const Matrix4 &lhs) const
   {
      Vector3 result;

      result.x = x * lhs(0, 0) + y * lhs(0, 1) + z * lhs(0, 2);
      result.y = x * lhs(1, 0) + y * lhs(1, 1) + z * lhs(1, 2);
      result.z = x * lhs(2, 0) + y * lhs(2, 1) + z * lhs(2, 2);

      return result;
   }

   float Vector3::Magnitude() const
   {
      return Sqrt(MagnitudeSquared());
   }

   float Vector3::MagnitudeSquared() const
   {
      return (x * x + y * y + z * z);
   }

   bool Vector3::IsZeroMagnitude() const
   {
      return (MagnitudeSquared() < EPSILON);
   }

   float Vector3::Normalise()
   {
      float sqLen = MagnitudeSquared();
      assert(sqLen != 0);

      float len = Sqrt(sqLen);
      float invLen = 1.0f / len;

      x *= invLen;
      y *= invLen;
      z *= invLen;

      return len;
   }

   void Vector3::MakeFloor(const Vector3 &cmp)
   {
      if (cmp.x < x) 
      {
         x = cmp.x;
      }

      if (cmp.y < y) 
      {
         y = cmp.y;
      }

      if (cmp.z < z) 
      {
         z = cmp.z;
      }
   }

   void Vector3::MakeCeil(const Vector3& cmp)
   {
      if (cmp.x > x) 
      {
         x = cmp.x;
      }

      if (cmp.y > y) 
      {
         y = cmp.y;
      }

      if (cmp.z > z) 
      {
         z = cmp.z;
      }
   }

   float Vector3::DotProduct(const Vector3 &lhs, const Vector3 &rhs)
   {
      return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
   }

   Vector3 Vector3::CrossProduct(const Vector3 &lhs, const Vector3 &rhs)
   {
      Vector3 cross;

      cross.x = lhs.y * rhs.z - lhs.z * rhs.y;
      cross.y = lhs.z * rhs.x - lhs.x * rhs.z;
      cross.z = lhs.x * rhs.y - lhs.y * rhs.x;

      return cross;
   }

   Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
   {
      Vector3 temp(lhs);
      temp += rhs;
      return temp;
   }

   Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
   {
      Vector3 temp(lhs);
      temp -= rhs;
      return temp;
   }

   Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs)
   {
      Vector3 temp(lhs);
      temp *= rhs;
      return temp;
   }

   Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs)
   {
      Vector3 temp(lhs);
      temp /= rhs;
      return temp;
   }

   Vector3 operator*(const Vector3 &lhs, float rhs)
   {
      Vector3 temp(lhs);
      temp *= rhs;
      return temp;
   }

   Vector3 operator/(const Vector3 &lhs, float rhs)
   {
      Vector3 temp(lhs);
      temp /= rhs;
      return temp;
   }

   Vector3 operator*(float lhs, const Vector3 &rhs)
   {
      Vector3 temp(rhs);
      temp *= lhs;
      return temp;
   }

   Vector3 operator/(float lhs, const Vector3 &rhs)
   {
      Vector3 temp(rhs);
      temp /= lhs;
      return temp;
   }

   Vector3 operator-(const Vector3 &op)
   {
      return Vector3(-op.x, -op.y, -op.z);
   }

   bool operator==(const Vector3 &lhs, const Vector3 &rhs)
   {
      return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
   }

   bool operator!=(const Vector3 &lhs, const Vector3 &rhs)
   {
      return !(lhs == rhs);
   }

   std::ostream &operator<<(std::ostream &lhs, const Vector3 &rhs)
   {
      lhs << "Vector3(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
      return lhs;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
