//****************************************************************************
//**
//**    $Workfile: Clarity_AABox.cpp $
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

#include <Clarity/Math/AABox.h>
#include <Clarity/Math/Matrix4.h>
#include <cassert>

namespace Clarity
{
   AABox::AABox()
   {
      // Default to null box
      SetMinimum(-0.5, -0.5, -0.5);
      SetMaximum(0.5, 0.5, 0.5);
      m_null = true;
   }

   AABox::AABox(const Vector3 &min, const Vector3 &max)
   {
      SetExtents(min, max);
   }

   AABox::AABox(
      float minX, float minY, float minZ,
      float maxX, float maxY, float maxZ)
   {
      SetExtents(minX, minY, minZ, maxX, maxY, maxZ);
   }

   AABox::~AABox()
   {
   }

   const Vector3 &AABox::GetMinimum() const
   {
      return m_minimum; 
   }

   const Vector3 &AABox::GetMaximum() const
   {
      return m_maximum;
   }

   void AABox::SetMinimum(const Vector3 &vec)
   {
      m_null = false;
      m_minimum = vec;
      UpdateCorners();
   }

   void AABox::SetMinimum(float x, float y, float z)
   {
      m_null = false;
      m_minimum.x = x;
      m_minimum.y = y;
      m_minimum.z = z;
      UpdateCorners();
   }

   void AABox::SetMaximum(const Vector3 &vec)
   {
      m_null = false;
      m_maximum = vec;
      UpdateCorners();
   }

   void AABox::SetMaximum(float x, float y, float z)
   {
      m_null = false;
      m_maximum.x = x;
      m_maximum.y = y;
      m_maximum.z = z;
      UpdateCorners();
   }

   void AABox::SetExtents(const Vector3 &min, const Vector3 &max)
   {
      m_null = false;
      m_minimum = min;
      m_maximum = max;
      UpdateCorners();
   }

   void AABox::SetExtents(
      float minX, float minY, float minZ,
      float maxX, float maxY, float maxZ)
   {
      m_null = false;

      m_minimum.x = minX;
      m_minimum.y = minY;
      m_minimum.z = minZ;

      m_maximum.x = maxX;
      m_maximum.y = maxY;
      m_maximum.z = maxZ;

      UpdateCorners();
   }

   const Vector3 *AABox::GetAllCorners() const
   {
      assert(!m_null && "Can't get corners of a null AAB");
      return (const Vector3*)m_corners;
   }

   void AABox::Merge(const AABox &rhs)
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
         Vector3 min = m_minimum;
         Vector3 max = m_maximum;
         max.MakeCeil(rhs.m_maximum);
         min.MakeFloor(rhs.m_minimum);

         SetExtents(min, max);
      }
   }

   void AABox::Merge(const Vector3 &point)
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

   void AABox::Transform(const Matrix4 &matrix)
   {
      // Do nothing if current null
      if (m_null)
         return;

      Vector3 min, max, temp;
      bool first = true;
      size_t i;

      for (i = 0; i < 8; ++i)
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

         if (first || temp.z > max.z)
         {
            max.z = temp.z;
         }

         if (first || temp.x < min.x)
         {
            min.x = temp.x;
         }

         if (first || temp.y < min.y)
         {
            min.y = temp.y;
         }

         if (first || temp.z < min.z)
         {
            min.z = temp.z;
         }

         first = false;
      }

      SetExtents(min,max);
   }

   void AABox::SetNull()
   {
      m_null = true;
   }

   bool AABox::IsNull() const
   {
      return m_null;
   }

   void AABox::Scale(const Vector3 &s)
   {
      // NB assumes centered on origin
      Vector3 min = m_minimum * s;
      Vector3 max = m_maximum * s;
      SetExtents(min, max);
   }

   bool AABox::Intersects(const AABox &b2) const
   {
      // Early-fail for nulls
      if (this->IsNull() || b2.IsNull())
         return false;

      // Use up to 6 separating planes
      if (m_maximum.x < b2.m_minimum.x)
         return false;
      if (m_maximum.y < b2.m_minimum.y)
         return false;
      if (m_maximum.z < b2.m_minimum.z)
         return false;

      if (m_minimum.x > b2.m_maximum.x)
         return false;
      if (m_minimum.y > b2.m_maximum.y)
         return false;
      if (m_minimum.z > b2.m_maximum.z)
         return false;

      // otherwise, must be intersecting
      return true;
   }

   bool AABox::Intersects(const Vector3 &v) const
   {
      return(v.x >= m_minimum.x  &&  v.x <= m_maximum.x  && 
         v.y >= m_minimum.y  &&  v.y <= m_maximum.y  && 
         v.z >= m_minimum.z  &&  v.z <= m_maximum.z);
   }

   Vector3 AABox::GetCenter() const
   {
      return Vector3((m_maximum + m_minimum) * 0.5);
   }

   void AABox::UpdateCorners()
   {
      // The order of these items is, using right-handed co-ordinates:
      // Minimum Z face, starting with Min(all), then anticlockwise
      //   around face (looking onto the face)
      // Maximum Z face, starting with Max(all), then anticlockwise
      //   around face (looking onto the face)
      m_corners[0] = m_minimum;
      m_corners[1].x = m_minimum.x; m_corners[1].y = m_maximum.y; m_corners[1].z = m_minimum.z;
      m_corners[2].x = m_maximum.x; m_corners[2].y = m_maximum.y; m_corners[2].z = m_minimum.z;
      m_corners[3].x = m_maximum.x; m_corners[3].y = m_minimum.y; m_corners[3].z = m_minimum.z;            

      m_corners[4] = m_maximum;
      m_corners[5].x = m_minimum.x; m_corners[5].y = m_maximum.y; m_corners[5].z = m_maximum.z;
      m_corners[6].x = m_minimum.x; m_corners[6].y = m_minimum.y; m_corners[6].z = m_maximum.z;
      m_corners[7].x = m_maximum.x; m_corners[7].y = m_minimum.y; m_corners[7].z = m_maximum.z; 
   }

   std::ostream &operator<<(std::ostream &lhs, const AABox &rhs)
   {
      if (rhs.IsNull())
      {
         lhs << "AABox(null)";
      }
      else
      {
         lhs << "AABox(min=" << rhs.GetMinimum() << ", max=" << rhs.GetMaximum();
         lhs << ", corners=";

         for (int i = 0; i < 7; ++i)
         {
            lhs << rhs.GetAllCorners()[i] << ", ";
         }

         lhs << rhs.GetAllCorners()[7] << ")";
      }

      return lhs;
   }
}

//****************************************************************************
//**
//**   END IMPLEMENTATION 
//**
//****************************************************************************
