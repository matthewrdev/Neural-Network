//****************************************************************************
//**
//**    $Workfile: Clarity_Circle.cpp $
//**
//**    This source file is part of Clarity.
//**    Clarity is game engine designed for teaching.
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
//**    $Date: 17/11/06 6:22p $ 
//**    $Revision: 3 $
//**
//****************************************************************************

#include <Clarity/Math/Circle.h>

namespace Clarity
{
   Circle::Circle()
      : m_radius(1.0f), m_centre(Vector2::ZERO)
   {
   }

   Circle::Circle(const Vector2 &centre, float radius)
      : m_radius(radius), m_centre(centre)
   {
   }

   float Circle::GetRadius() const
   {
      return m_radius;
   }

   void Circle::SetRadius(float radius)
   {
      m_radius = radius;
   }

   const Vector2 &Circle::GetCentre() const
   {
      return m_centre;
   }

   void Circle::SetCentre(const Vector2 &centre)
   {
      m_centre = centre;
   }
}

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
