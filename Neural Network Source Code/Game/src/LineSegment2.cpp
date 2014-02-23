//****************************************************************************
//**
//**    $Workfile: Clarity_LineSegment2.cpp $
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
//**    $Revision: 1 $
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

   LineSegment2::LineSegment2(const Vector2 &tail, const Vector2 &head)
   {
      Set(tail, head);
   }

   LineSegment2::LineSegment2(const LineSegment3 &lineSegment)
   {
      m_tail = Vector2(lineSegment.GetTail(), Vector2::PROJECTION_MODE_ORTHOGRAPHIC);
      m_head = Vector2(lineSegment.GetHead(), Vector2::PROJECTION_MODE_ORTHOGRAPHIC);
      MarkAsDirty();
   }

   LineSegment2::~LineSegment2()
   {
   }

   const Vector2 &LineSegment2::GetTail() const
   {
      return m_tail;
   }

   const Vector2 &LineSegment2::GetHead() const
   {
      return m_head;
   }

   const Vector2 &LineSegment2::GetVector() const
   {
      if (m_vectorDirty)
      {
         m_vector = m_head - m_tail;
         m_vectorDirty = false;
      }

      return m_vector;
   }

   const Vector2 &LineSegment2::GetDirection() const
   {
      return GetLine().GetDirection();
   }

   const Vector2 &LineSegment2::GetNormal() const
   {
      return GetLine().GetNormal();
   }

   float LineSegment2::GetLength() const
   {
      if (m_lengthDirty)
      {
         m_length = Sqrt(GetLengthSquared());
         m_lengthDirty = false;
      }

      return m_length;
   }

   float LineSegment2::GetLengthSquared() const
   {
      if (m_lengthSquaredDirty)
      {
         m_lengthSquared = GetVector().MagnitudeSquared();
         m_lengthSquaredDirty = false;
      }

      return m_lengthSquared;
   }

   Vector2 LineSegment2::Midpoint() const
   {
      return Vector2(
         m_tail.x + (m_head.x - m_tail.x) / 2, 
         m_tail.y + (m_head.y - m_tail.y) / 2);
   }

   LineSegment2 LineSegment2::Transform(const Matrix3 &transform) const
   {
      return LineSegment2(m_tail.Transform(transform), m_head.Transform(transform));
   }

   void LineSegment2::Set(const Vector2 &tail, const Vector2 &head)
   {
      m_tail = tail;
      m_head = head;
      MarkAsDirty();
   }

   const Line2 &LineSegment2::GetLine() const
   {
      if (m_lineDirty)
      {
         m_line.FromPoints(m_tail, m_head);
         m_lineDirty = false;
      }

      return m_line;
   }

   Vector2 LineSegment2::FindNearestPoint(const Vector2 &startingPoint) const
   {
      Vector2 nearestPoint;
      const Vector2 &e = GetVector();

      nearestPoint = m_tail + Min(1.0f, Max(0.0f, Vector2::DotProduct(startingPoint - m_tail, e) / (GetLengthSquared()))) * e;
      return nearestPoint;
   }

   Vector2 LineSegment2::GetClosestPointFromDisplacement(float displacement) const
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

   void LineSegment2::MarkAsDirty() const
   {
      m_lineDirty = true;
      m_lengthDirty = true;
      m_lengthSquaredDirty = true;
      m_vectorDirty = true;
   }

   std::ostream &operator<<(std::ostream &os, const LineSegment2 &rhs)
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
