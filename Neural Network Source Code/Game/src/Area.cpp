//****************************************************************************
//**
//**    $Workfile: Clarity_Area.cpp $
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
//**    $Date: 29/12/06 6:15p $ 
//**    $Revision: 3 $
//**
//****************************************************************************

#include <Clarity/Math/Area.h>
#include <Clarity/Math/Circle.h>
#include <Clarity/Math/AARect.h>
#include <Clarity/Math/Vector2.h>

namespace Clarity
{
   Area::Area()
   {
      Set(1.0f);
   }

   Area::Area(float radius)
   {
      Set(radius);
   }

   Area::Area(float width, float height)
   {
      Set(width, height);
   }

   Area::Type Area::GetType() const
   {
      return m_type;
   }

   float Area::GetRadius() const
   {
      return m_radius;
   }

   float Area::GetWidth() const
   {
      return m_width;
   }

   float Area::GetHeight() const
   {
      return m_height;
   }

   void Area::Set(float radius)
   {
      m_type = TYPE_CIRCLE;
      m_radius = radius;
      m_width = m_radius * 2;
      m_height = m_radius * 2;
   }

   void Area::Set(float width, float height)
   {
      m_type = TYPE_RECT;
      m_width = width;
      m_height = height;
      m_radius = Vector2(m_width, m_height).Magnitude() * 0.5f;
   }
   
   Circle Area::MakeCircle(const Vector2 &centre) const
   {
      return Circle(centre, m_radius);
   }

   AARect Area::MakeAARect(const Vector2 &centre) const
   {
      Vector2 halfSize(Vector2(m_width, m_height) * 0.5f);
      return AARect(-halfSize + centre, halfSize + centre);
   }

}

//****************************************************************************
//**
//**   END IMPLEMENTATION 
//**
//****************************************************************************
