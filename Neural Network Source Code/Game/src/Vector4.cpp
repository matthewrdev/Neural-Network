//****************************************************************************
//**
//**    $Workfile: Clarity_Vector4.cpp $
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
//**    $Revision: 2 $
//**
//****************************************************************************

#include <Clarity/Math/Vector4.h>
#include <Clarity/Math/Vector3.h>
#include <Clarity/Math/Matrix4.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   const Vector4 Vector4::ZERO(0, 0, 0, 1);

   Vector4::Vector4()
   {
      *this = ZERO;
   }

   Vector4::Vector4(float xIn, float yIn, float zIn, float wIn)
   {
      Set(xIn, yIn, zIn, wIn);
   }

   Vector4::Vector4(const Vector3 &vector3)
   {
      *this = vector3;
   }

   Vector4::~Vector4()
   {
   }

   void Vector4::Set(float xIn, float yIn, float zIn, float wIn)
   {
      x = xIn;
      y = yIn;
      z = zIn;
      w = wIn;
   }

   Vector4 &Vector4::operator=(const Vector3 &vector3)
   {
      x = vector3.x;
      y = vector3.y;
      z = vector3.z;
      w = 1.0f;

      return *this;
   }


   float Vector4::operator[](int idx) const
   {
      assert(0 <= idx && idx <= 3);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
         return y;

      case 2:
         return z;

      case 3:
      default:
         return w;

      }
   }

   float &Vector4::operator[](int idx)
   {
      assert(0 <= idx && idx <= 3);

      switch (idx)
      {
      case 0: 
         return x;

      case 1: 
         return y;

      case 2:
         return z;

      case 3:
      default:
         return w;
      }
   }


   Vector4 Vector4::Transform(const Matrix4 &mat) const
   {
      return Vector4(
         x * mat(0, 0) + y * mat(1, 0) + z * mat(2, 0) + w * mat(3, 0),
         x * mat(0, 1) + y * mat(1, 1) + z * mat(2, 1) + w * mat(3, 1),
         x * mat(0, 2) + y * mat(1, 2) + z * mat(2, 2) + w * mat(3, 2),
         x * mat(0, 3) + y * mat(1, 3) + z * mat(2, 3) + w * mat(3, 3)
         );
   }

   std::ostream &operator <<(std::ostream &lhs, const Vector4 &rhs)
   {
      lhs << "Vector4(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
      return lhs;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
