//****************************************************************************
//**
//**    $Workfile: Clarity_Line.cpp $
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

#include <Clarity/Math/Line3.h>
#include <Clarity/Math/Math.h>

namespace Clarity
{
   Line3::Line3()
   {
      m_normal.z = 0.0f;
      FromNormalDistance(Vector3::UNIT_Y, 0.0f);
   }

   Line3::Line3(const Vector3 &normal, float distance)
   {
      m_normal.z = 0.0f;
      FromNormalDistance(normal, distance);
   }

   Line3::Line3(const Vector3 &tail, const Vector3 &head)
   {
      m_normal.z = 0.0f;
      FromPoints(tail, head);
   }

   void Line3::FromNormalDistance(const Vector3 &normal, float distance)
   {
      m_normal.x = normal.x;
      m_normal.y = normal.y;
      m_distance = distance;
      m_directionDirty = true;
   }

   void Line3::FromPoints(const Vector3 &tail, const Vector3 &head)
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

   Line3::~Line3()
   {
   }

   const Vector3 &Line3::GetDirection() const
   {
      if (m_directionDirty)
      {
         m_direction.x = -m_normal.y;
         m_direction.y = m_normal.x;
         m_directionDirty = false;
      }

      return m_direction;
   }

   const Vector3 &Line3::GetNormal() const
   {
      return m_normal;
   }

   float Line3::GetDistance() const
   {
      return m_distance;
   }

   float Line3::GetSlope() const
   {
      // The slope is equivalent to the negative inverse slope of the normal
      return -m_normal.x / m_normal.y;
   }

   float Line3::DistanceToPoint(const Vector3 &point) const
   {
      return 
         m_normal.x * point.x + 
         m_normal.y * point.y + 
         m_normal.z * point.z + 
         m_distance;
   }

   float Line3::DistanceToPoint(
      const Vector3 &lineNormal, 
      float lineDistance, 
      const Vector3 &point)
   {
      return 
         lineNormal.x * point.x + 
         lineNormal.y * point.y + 
         lineNormal.z * point.z + 
         lineDistance;
   }

}

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
