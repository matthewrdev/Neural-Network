//****************************************************************************
//**
//**    $Workfile: Clarity_LineSegment.cpp $
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
//**    $Date: 21/11/06 7:05p $ 
//**    $Revision: 2 $
//**
//****************************************************************************

#include <Clarity/Math/LineSegment3.h>
#include <Clarity/Math/LineSegment2.h>
#include <Clarity/Math/Math.h>
#include <cassert>

namespace Clarity
{
   namespace
   {
      // ------------------------------------------------------------------------
      // Min
      // ------------------------------------------------------------------------
      // Return smaller of lhs and rhs.
      // ------------------------------------------------------------------------
      template<typename T> 
      const T &Min(const T &lhs, const T &rhs)
      {
         return (rhs < lhs ? rhs : lhs);
      }

      // ------------------------------------------------------------------------
      // Max
      // ------------------------------------------------------------------------
      // Return larger of lhs and rhs.
      // ------------------------------------------------------------------------
      template<typename T> 
      const T &Max(const T &lhs, const T &rhs)
      {
         return (lhs < rhs ? rhs : lhs);
      }
   }

   LineSegment3::LineSegment3(const Vector3 &tail, const Vector3 &head)
   {
      Set(tail, head);
   }

   LineSegment3::LineSegment3(const LineSegment2 &lineSegment2, float tailZ, float headZ)
   {
      Set(Vector3(lineSegment2.GetTail(), tailZ), Vector3(lineSegment2.GetHead(), headZ));
   }

   LineSegment3::~LineSegment3()
   {
   }

   const Vector3 &LineSegment3::GetTail() const
   {
      return m_tail;
   }

   const Vector3 &LineSegment3::GetHead() const
   {
      return m_head;
   }

   const Vector3 &LineSegment3::GetVector() const
   {
      if (m_vectorDirty)
      {
         m_vector = m_head - m_tail;
         m_vectorDirty = false;
      }

      return m_vector;
   }

   const Vector3 &LineSegment3::GetDirection() const
   {
      return GetLine().GetDirection();
   }

   const Vector3 &LineSegment3::GetNormal() const
   {
      return GetLine().GetNormal();
   }

   float LineSegment3::GetLength() const
   {
      if (m_lengthDirty)
      {
         m_length = Sqrt(GetLengthSquared());
         m_lengthDirty = false;
      }

      return m_length;
   }

   float LineSegment3::GetLengthSquared() const
   {
      if (m_lengthSquaredDirty)
      {
         m_lengthSquared = GetVector().MagnitudeSquared();
         m_lengthSquaredDirty = false;
      }

      return m_lengthSquared;
   }

   Vector3 LineSegment3::Midpoint() const
   {
      return Vector3(
         m_tail.x + (m_head.x - m_tail.x) / 2, 
         m_tail.y + (m_head.y - m_tail.y) / 2, 
         m_tail.z + (m_head.z - m_tail.z) / 2);
   }

   LineSegment3 LineSegment3::Transform(const Matrix4 &transform) const
   {
      return LineSegment3(m_tail.Transform(transform), m_head.Transform(transform));
   }

   void LineSegment3::Set(const Vector3 &tail, const Vector3 &head)
   {
      m_tail = tail;
      m_head = head;
      MarkAsDirty();
   }

   const Line3 &LineSegment3::GetLine() const
   {
      if (m_lineDirty)
      {
         m_line.FromPoints(m_tail, m_head);
         m_lineDirty = false;
      }

      return m_line;
   }

   Vector3 LineSegment3::FindNearestPoint(const Vector3 &startingPoint) const
   {
      Vector3 nearestPoint;
      const Vector3 &e = GetVector();

      nearestPoint = m_tail + Min(1.0f, Max(0.0f, Vector3::DotProduct(startingPoint - m_tail, e) / (GetLengthSquared()))) * e;
      return nearestPoint;
   }

   Vector3 LineSegment3::GetClosestPointFromDisplacement(float displacement) const
   {
      if (displacement <= 0.0) 
      {
         return m_tail;
      }
      else if (displacement >= GetLength())
      {
         return m_head;
      }
      else 
      {
         return (m_tail + displacement * GetLine().GetDirection());
      }
   }

   void LineSegment3::MarkAsDirty() const
   {
      m_lineDirty = true;
      m_lengthDirty = true;
      m_lengthSquaredDirty = true;
      m_vectorDirty = true;
   }

   std::ostream &operator<<(std::ostream &os, const LineSegment3 &rhs)
   {
      os << rhs.GetTail() << " " << rhs.GetHead();
      return os;
   }
}

//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
