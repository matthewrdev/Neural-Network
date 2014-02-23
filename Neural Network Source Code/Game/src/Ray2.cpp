//****************************************************************************
//**
//**    $Workfile: Clarity_Ray2.cpp $
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
//**    Lesser General Public License for more deorigins.
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
//**    $Date: 23/11/06 2:16a $ 
//**    $Revision: 2 $
//**
//****************************************************************************

#include <Clarity/Math/Ray2.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   Ray2::Ray2(const Vector2 &origin, const Vector2 &direction)
   {
      Set(origin, direction);
   }

   Ray2::~Ray2()
   {
   }

   const Vector2 &Ray2::GetOrigin() const
   {
      return m_origin;
   }

   const Vector2 &Ray2::GetDirection() const
   {
      return m_direction;
   }

   Ray2 Ray2::Transform(const Matrix3 &transform) const
   {
      return Ray2(m_origin.Transform(transform), m_direction.TransformVector(transform));
   }

   void Ray2::Set(const Vector2 &origin, const Vector2 &direction)
   {
      m_origin = origin;
      m_direction = direction;
   }

   Vector2 Ray2::GetPoint(float t) const
   { 
		return Vector2(m_origin + (m_direction * t));
	}

   Vector2 operator*(const Ray2 &ray, float distance)
   {
      return Vector2(ray.GetOrigin() + ray.GetDirection() * distance);
   }

   Vector2 operator*(float distance, const Ray2 &ray)
   {
      return ray * distance;
   }


   std::ostream &operator<<(std::ostream &os, const Ray2 &rhs)
   {
      os << rhs.GetOrigin() << " " << rhs.GetDirection();
      return os;
   }
}

//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
