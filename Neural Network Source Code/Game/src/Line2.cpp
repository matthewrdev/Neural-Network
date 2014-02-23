//****************************************************************************
//**
//**    $Workfile: Clarity_Line2.cpp $
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
//**    $Date: 17/11/06 6:22p $ 
//**    $Revision: 1 $
//**
//****************************************************************************

#include <Clarity/Math/Line2.h>
#include <Clarity/Math/Math.h>

namespace Clarity
{
   Line2::Line2()
   {
      FromNormalDistance(Vector2::UNIT_Y, 0.0f);
   }

   Line2::Line2(const Vector2 &normal, float distance)
   {
      FromNormalDistance(normal, distance);
   }

   Line2::Line2(const Vector2 &tail, const Vector2 &head)
   {
      FromPoints(tail, head);
   }

   void Line2::FromNormalDistance(const Vector2 &normal, float distance)
   {
      m_normal = normal;
      m_distance = distance;
      m_directionDirty = true;
   }

   void Line2::FromPoints(const Vector2 &tail, const Vector2 &head)
   {
      m_normal.x = head.y - tail.y;
      m_normal.y = tail.x - head.x;
      m_distance = head.x * tail.y - tail.x * head.y;

      float invMag = 1.0f / Sqrt(m_normal.x * m_normal.x + m_normal.y * m_normal.y);
      m_normal.x *= invMag;
      m_normal.y *= invMag;
      m_distance *= invMag;

      m_directionDirty = true;
   }

   Line2::~Line2()
   {
   }

   const Vector2 &Line2::GetDirection() const
   {
      if (m_directionDirty)
      {
         m_direction.x = -m_normal.y;
         m_direction.y = m_normal.x;
         m_directionDirty = false;
      }

      return m_direction;
   }

   const Vector2 &Line2::GetNormal() const
   {
      return m_normal;
   }

   float Line2::GetDistance() const
   {
      return m_distance;
   }

   float Line2::GetSlope() const
   {
      // The slope is equivalent to the negative inverse slope of the normal
      return -m_normal.x / m_normal.y;
   }

   float Line2::DistanceToPoint(const Vector2 &point) const
   {
      return 
         m_normal.x * point.x + 
         m_normal.y * point.y + 
         m_distance;
   }

   float Line2::DistanceToPoint(
      const Vector2 &lineNormal, 
      float lineDistance, 
      const Vector2 &point)
   {
      return 
         lineNormal.x * point.x + 
         lineNormal.y * point.y + 
         lineDistance;
   }

}

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
