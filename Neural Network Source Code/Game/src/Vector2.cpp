//****************************************************************************
//**
//**    $Workfile: Clarity_Vector2.cpp $
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
#include <Clarity/Math/Matrix2.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Vector2 Vector2::ZERO(0, 0);
   const Vector2 Vector2::UNIT_X(1, 0);
   const Vector2 Vector2::UNIT_Y(0, 1);
   const Vector2 Vector2::NEGATIVE_UNIT_X(-1, 0);
   const Vector2 Vector2::NEGATIVE_UNIT_Y(0, -1);
   const Vector2 Vector2::UNIT_SCALE(1, 1);

   Vector2::Vector2()
   {
      *this = ZERO;
   }

   Vector2::Vector2(float xIn, float yIn)
   {
      Set(xIn, yIn);
   }

   Vector2::Vector2(const Vector3 &rhs, ProjectionMode projectionMode)
   {
      switch (projectionMode)
      {
      case PROJECTION_MODE_FROM_HOMOGENEOUS:
         {
            assert(rhs.z != 0.0f);

            float invw = 1.0f / rhs.z;

            x = rhs.x * invw;
            y = rhs.y * invw;
         }
         break;

      case PROJECTION_MODE_ORTHOGRAPHIC:
         x = rhs.x;
         y = rhs.y;
         break;
      }
   }

   Vector2::~Vector2()
   {
   }

   float Vector2::operator[](int idx) const
   {
      assert(0 <= idx && idx <= 1);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
         return y;

      default:
         return 0.0f;
      }
   }

   float &Vector2::operator[](int idx)
   {
      assert(0 <= idx && idx <= 1);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
      default:
         return y;
      }
   }


   void Vector2::Set(float xIn, float yIn)
   {
      x = xIn;
      y = yIn;
   }

   Vector2 &Vector2::operator*=(const Vector2 &rhs)
   {
      x *= rhs.x;
      y *= rhs.y;

      return *this;
   }

   Vector2 &Vector2::operator/=(const Vector2 &rhs)
   {
      assert(rhs.x != 0 && rhs.y != 0);
      x /= rhs.x;
      y /= rhs.y;

      return *this;
   }

   Vector2 &Vector2::operator+=(const Vector2 &rhs)
   {
      x += rhs.x;
      y += rhs.y;

      return *this;
   }

   Vector2 &Vector2::operator-=(const Vector2 &rhs)
   {
      x -= rhs.x;
      y -= rhs.y;
      
      return *this;
   }

   Vector2 &Vector2::operator*=(float rhs)
   {
      x *= rhs;
      y *= rhs;

      return *this;
   }

   Vector2 &Vector2::operator/=(float rhs)
   {
      assert(rhs != 0);

      float invrhs = 1.0f / rhs;
      *this *= invrhs;

      return *this;
   }

   Vector2 Vector2::Transform(const Matrix2 &lhs) const
   {
      return Vector2(
         lhs(0, 0) * x + lhs(0, 1) * y,
         lhs(1, 0) * x + lhs(1, 1) * y);
   }

   Vector2 Vector2::Transform(const Matrix3 &lhs) const
   {
      Vector2 result;

      result.x = x * lhs(0, 0) + y * lhs(0, 1) + lhs(0, 2);
      result.y = x * lhs(1, 0) + y * lhs(1, 1) + lhs(1, 2);

      return result;
   }

   Vector2 Vector2::TransformVector(const Matrix3 &lhs) const
   {
      Vector2 result;

      result.x = x * lhs(0, 0) + y * lhs(0, 1);
      result.y = x * lhs(1, 0) + y * lhs(1, 1);

      return result;
   }

   float Vector2::Magnitude() const
   {
      return Sqrt(MagnitudeSquared());
   }

   float Vector2::MagnitudeSquared() const
   {
      return (x * x + y * y);
   }

   bool Vector2::IsZeroMagnitude() const
   {
      return (MagnitudeSquared() < EPSILON);
   }

   float Vector2::Normalise()
   {
      float sqLen = MagnitudeSquared();
      assert(sqLen != 0); // Why the fuck would you do this?

      float len = Sqrt(sqLen);
      float invLen = 1.0f / len;

      x *= invLen;
      y *= invLen;

      return len;
   }

   void Vector2::MakeFloor(const Vector2 &cmp)
   {
      if (cmp.x < x) 
      {
         x = cmp.x;
      }

      if (cmp.y < y) 
      {
         y = cmp.y;
      }
   }

   void Vector2::MakeCeil(const Vector2& cmp)
   {
      if (cmp.x > x) 
      {
         x = cmp.x;
      }

      if (cmp.y > y) 
      {
         y = cmp.y;
      }
   }

   float Vector2::DotProduct(const Vector2 &lhs, const Vector2 &rhs)
   {
      return lhs.x * rhs.x + lhs.y * rhs.y;
   }

   Vector2 Vector2::Lerp(const Vector2 &from, const Vector2 &to, float t)
   {
      return from + (to - from) * t;
   }

   Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
   {
      Vector2 temp(lhs);
      temp += rhs;
      return temp;
   }

   Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
   {
      Vector2 temp(lhs);
      temp -= rhs;
      return temp;
   }

   Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs)
   {
      Vector2 temp(lhs);
      temp *= rhs;
      return temp;
   }

   Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs)
   {
      Vector2 temp(lhs);
      temp /= rhs;
      return temp;
   }

   Vector2 operator*(const Vector2 &lhs, float rhs)
   {
      Vector2 temp(lhs);
      temp *= rhs;
      return temp;
   }

   Vector2 operator/(const Vector2 &lhs, float rhs)
   {
      Vector2 temp(lhs);
      temp /= rhs;
      return temp;
   }

   Vector2 operator*(float lhs, const Vector2 &rhs)
   {
      Vector2 temp(rhs);
      temp *= lhs;
      return temp;
   }

   Vector2 operator/(float lhs, const Vector2 &rhs)
   {
      Vector2 temp(rhs);
      temp /= lhs;
      return temp;
   }

   Vector2 operator-(const Vector2 &op)
   {
      return Vector2(-op.x, -op.y);
   }

   bool operator==(const Vector2 &lhs, const Vector2 &rhs)
   {
      return (lhs.x == rhs.x) && (lhs.y == rhs.y);
   }

   bool operator!=(const Vector2 &lhs, const Vector2 &rhs)
   {
      return !(lhs == rhs);
   }

   Vector2 Perp(const Vector2 &v)
   {
      return Vector2(v.y, -v.x);
   }

   float Dot(const Vector2 &v1, const Vector2 &v2)
   {
      return Vector2::DotProduct(v1, v2);
   }

   std::ostream &operator<<(std::ostream &lhs, const Vector2 &rhs)
   {
      lhs << "Vector2(" << rhs.x << ", " << rhs.y << ")";
      return lhs;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
