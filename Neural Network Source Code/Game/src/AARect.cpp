//****************************************************************************
//**
//**    $Workfile: Clarity_AARect.cpp $
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
//**    $Revision: 4 $
//**
//****************************************************************************

#include <Clarity/Math/AARect.h>
#include <Clarity/Math/Matrix3.h>
#include <cassert>

namespace Clarity
{
   AARect::AARect()
   {
      // Default to null box
      SetMinimum(-0.5, -0.5);
      SetMaximum(0.5, 0.5);
      m_null = true;
   }

   AARect::AARect(const Vector2 &min, const Vector2 &max)
   {
      SetExtents(min, max);
   }

   AARect::AARect(
      float minX, float minY,
      float maxX, float maxY)
   {
      SetExtents(minX, minY, maxX, maxY);
   }

   AARect::AARect(const Vector2 &size)
   {
      m_null = size.x == 0.0f || size.y == 0.0f;
      m_maximum = Vector2(size.x * 0.5f, size.y * 0.5f);
      m_minimum = m_maximum - size;
      UpdateCorners();  
   }

   AARect::~AARect()
   {
   }

   const Vector2 &AARect::GetMinimum() const
   {
      return m_minimum; 
   }

   const Vector2 &AARect::GetMaximum() const
   {
      return m_maximum;
   }

   void AARect::SetMinimum(const Vector2 &vec)
   {
      m_null = false;
      m_minimum = vec;
      UpdateCorners();
   }

   void AARect::SetMinimum(float x, float y)
   {
      m_null = false;
      m_minimum.x = x;
      m_minimum.y = y;
      UpdateCorners();
   }

   void AARect::SetMaximum(const Vector2 &vec)
   {
      m_null = false;
      m_maximum = vec;
      UpdateCorners();
   }

   void AARect::SetMaximum(float x, float y)
   {
      m_null = false;
      m_maximum.x = x;
      m_maximum.y = y;
      UpdateCorners();
   }

   void AARect::SetExtents(const Vector2 &min, const Vector2 &max)
   {
      m_null = false;
      m_minimum = min;
      m_maximum = max;
      UpdateCorners();
   }

   void AARect::SetExtents(
      float minX, float minY,
      float maxX, float maxY)
   {
      m_null = false;

      m_minimum.x = minX;
      m_minimum.y = minY;

      m_maximum.x = maxX;
      m_maximum.y = maxY;

      UpdateCorners();
   }

   const Vector2 *AARect::GetAllCorners() const
   {
      assert(!m_null && "Can't get corners of a null AAB");
      return (const Vector2*)m_corners;
   }

   void AARect::Merge(const AARect &rhs)
   {
      // Do nothing if rhs null
      if (rhs.m_null)
      {
         return;
      }
      // Otherwise if current null, just take rhs
      else if (m_null)
      {
         SetExtents(rhs.m_minimum, rhs.m_maximum);
      }
      // Otherwise merge
      else
      {
         Vector2 min = m_minimum;
         Vector2 max = m_maximum;
         max.MakeCeil(rhs.m_maximum);
         min.MakeFloor(rhs.m_minimum);

         SetExtents(min, max);
      }
   }

   void AARect::Merge(const Vector2 &point)
   {
      if (m_null)
      { 
         // if null, use this point
         SetExtents(point, point);
      } 
      else 
      {
         m_maximum.MakeCeil(point);
         m_minimum.MakeFloor(point);
         UpdateCorners();
      }
   }

   void AARect::Transform(const Matrix3 &matrix)
   {
      // Do nothing if current null
      if (m_null)
         return;

      Vector2 min, max, temp;
      bool first = true;
      size_t i;

      for (i = 0; i < 4; ++i)
      {
         // Transform and check extents
         temp = matrix * m_corners[i];
         if (first || temp.x > max.x)
         {
            max.x = temp.x;
         }

         if (first || temp.y > max.y)
         {
            max.y = temp.y;
         }

         if (first || temp.x < min.x)
         {
            min.x = temp.x;
         }

         if (first || temp.y < min.y)
         {
            min.y = temp.y;
         }

         first = false;
      }

      SetExtents(min,max);
   }

   void AARect::Translate(const Vector2 &translation)
   {
      SetExtents(GetMinimum() + translation, GetMaximum() + translation);
   }

   void AARect::SetNull()
   {
      m_null = true;
   }

   bool AARect::IsNull() const
   {
      return m_null;
   }

   void AARect::Scale(const Vector2 &s)
   {
      // NB assumes centered on origin
      Vector2 min = m_minimum * s;
      Vector2 max = m_maximum * s;
      SetExtents(min, max);
   }

   bool AARect::IsSubsetOfRect(const AARect &b2) const
   {
      return (
         m_minimum.x >= b2.m_minimum.x &&
         m_minimum.y >= b2.m_minimum.y &&
         m_maximum.x <= b2.m_maximum.x &&
         m_maximum.y <= b2.m_maximum.y);
   }

   Vector2 AARect::GetCenter() const
   {
      return Vector2((m_maximum + m_minimum) * 0.5);
   }

   float AARect::GetWidth() const
   {
      return m_maximum.x - m_minimum.x;
   }

   float AARect::GetHeight() const
   {
      return m_maximum.y - m_minimum.y;
   }

   Vector2 AARect::GetSize() const
   {
      return m_maximum - m_minimum;
   }

   void AARect::UpdateCorners()
   {
      // The order of these items is, using right-handed co-ordinates:
      // starting with Min(all), then anticlockwise
      //   around face (looking onto the face)
      m_corners[0] = m_minimum;
      m_corners[1].x = m_minimum.x; m_corners[1].y = m_maximum.y;
      m_corners[2].x = m_maximum.x; m_corners[2].y = m_maximum.y;
      m_corners[3].x = m_maximum.x; m_corners[3].y = m_minimum.y;
   }

   std::ostream &operator<<(std::ostream &lhs, const AARect &rhs)
   {
      if (rhs.IsNull())
      {
         lhs << "AARect(null)";
      }
      else
      {
         lhs << "AARect(min=" << rhs.GetMinimum() << ", max=" << rhs.GetMaximum();
         lhs << ", corners=";

         for (int i = 0; i < 3; ++i)
         {
            lhs << rhs.GetAllCorners()[i] << ", ";
         }

         lhs << rhs.GetAllCorners()[3] << ")";
      }

      return lhs;
   }
}

//****************************************************************************
//**
//**   END IMPLEMENTATION 
//**
//****************************************************************************
