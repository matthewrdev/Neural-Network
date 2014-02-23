//****************************************************************************
//**
//**    $Workfile: Clarity_Direction.cpp $
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
//**    $Date: 28/11/06 3:22p $ 
//**    $Revision: 1 $
//**
//****************************************************************************

#include <Clarity/Math/Direction.h>
#include <Clarity/Math/Math.h>

namespace Clarity
{
   const Direction NEXT_DIRECTION_TABLE[] = 
   { 
      SOUTH_EAST,
      SOUTH,
      SOUTH_WEST,
      WEST,
      NORTH_WEST,
      NORTH,
      NORTH_EAST,
      EAST
   };

   const Direction PREV_DIRECTION_TABLE[] = 
   { 
      NORTH_EAST,
      EAST,
      SOUTH_EAST,
      SOUTH,
      SOUTH_WEST,
      WEST,
      NORTH_WEST,
      NORTH,
   };

   const Direction NEXT_CARDINAL_DIRECTION_TABLE[] = 
   { 
      SOUTH,
      SOUTH,
      WEST,
      WEST,
      NORTH,
      NORTH,
      EAST,
      EAST
   };

   const Direction PREV_CARDINAL_DIRECTION_TABLE[] = 
   { 
      NORTH,
      EAST,
      EAST,
      SOUTH,
      SOUTH,
      WEST,
      WEST,
      NORTH,
   };

   const Direction NEXT_DIAGONAL_DIRECTION_TABLE[] = 
   {
      SOUTH_EAST,
      SOUTH_WEST,
      SOUTH_WEST,
      NORTH_WEST,
      NORTH_WEST,
      NORTH_EAST,
      NORTH_EAST,
      SOUTH_EAST
   };

   const Direction PREV_DIAGONAL_DIRECTION_TABLE[] = 
   {
      NORTH_EAST,
      NORTH_EAST,
      SOUTH_EAST,
      SOUTH_EAST,
      SOUTH_WEST,
      SOUTH_WEST,
      NORTH_WEST,
      NORTH_WEST
   };

   // Note: This table is offset by +7
   //       Add 7 to the difference before indexing to find the distance
   const int DIRECTION_DISTANCE_TABLE[] = 
   {
      1, 2, 3, 4, -3, -2, -1, 0, 1, 2, 3, 4, -3, -2, -1
   };

   const bool CARDINAL_DIRECTION_TABLE[] =
   {
      true, false, true, false, true, false, true, false
   };

   const float DIAG_VALUE(1.0f / Sqrt(2));

   const Vector2 VECTOR_DIRECTION_TABLE[] =
   {
      Vector2(1, 0),
      Vector2(DIAG_VALUE, -DIAG_VALUE),
      Vector2(0, -1),
      Vector2(-DIAG_VALUE, -DIAG_VALUE),
      Vector2(-1, 0),
      Vector2(-DIAG_VALUE, DIAG_VALUE),
      Vector2(0, 1),
      Vector2(DIAG_VALUE, DIAG_VALUE)
   };

   const Vector2 VECTOR_BOX_DIRECTION_TABLE[] =
   {
      Vector2( 1,  0),
      Vector2( 1, -1),
      Vector2( 0, -1),
      Vector2(-1, -1),
      Vector2(-1,  0),
      Vector2(-1,  1),
      Vector2( 0,  1),
      Vector2( 1,  1)
   };

   const std::string DIRECTION_STRING_TABLE[] = 
   {
      "East", "Southeast", "South", "Southwest", "West", "Northwest", "North", "Northeast"
   };

   int ToDirection(const Vector2 &vector)
   {
      assert(vector != Vector2::ZERO);
      
      if (vector.x > 0.0f)
      {
         if (vector.y > 0.0f)
         {
            if (vector.x > vector.y)
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[NORTH_EAST]) < vector.x)
               {
                  return EAST;
               }
               else
               {
                  return NORTH_EAST;
               }
            }
            else
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[NORTH_EAST]) < vector.y)
               {
                  return NORTH;
               }
               else
               {
                  return NORTH_EAST;
               }
            }
         }
         else
         {
            if (vector.x > -vector.y)
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[SOUTH_EAST]) < vector.x)
               {
                  return EAST;
               }
               else
               {
                  return SOUTH_EAST;
               }
            }
            else
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[SOUTH_EAST]) < -vector.y)
               {
                  return SOUTH;
               }
               else
               {
                  return SOUTH_EAST;
               }
            }
         }
      }
      else
      {
         if (vector.y > 0.0f)
         {
            if (-vector.x > vector.y)
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[NORTH_WEST]) < -vector.x)
               {
                  return WEST;
               }
               else
               {
                  return NORTH_WEST;
               }
            }
            else
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[NORTH_WEST]) < vector.y)
               {
                  return NORTH;
               }
               else
               {
                  return NORTH_WEST;
               }
            }
         }
         else
         {
            if (-vector.x > -vector.y)
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[SOUTH_WEST]) < -vector.x)
               {
                  return WEST;
               }
               else
               {
                  return SOUTH_WEST;
               }
            }
            else
            {
               if (Vector2::DotProduct(vector, VECTOR_DIRECTION_TABLE[SOUTH_WEST]) < -vector.y)
               {
                  return SOUTH;
               }
               else
               {
                  return SOUTH_WEST;
               }
            }
         }
      }
   }

   int ToCardinalDirection(const Vector2 &vector)
   {
      assert(vector != Vector2::ZERO);

      if (vector.x > 0.0f)
      {
         if (vector.y > 0.0f)
         {
            if (vector.x > vector.y)
            {
               return EAST;
            }
            else
            {
               return NORTH;
            }
         }
         else
         {
            if (vector.x > -vector.y)
            {
               return EAST;
            }
            else
            {
               return SOUTH;
            }
         }
      }
      else
      {
         if (vector.y > 0.0f)
         {
            if (-vector.x > vector.y)
            {
               return WEST;
            }
            else
            {
               return NORTH;
            }
         }
         else
         {
            if (-vector.x > -vector.y)
            {
               return WEST;
            }
            else
            {
               return SOUTH;
            }
         }
      }
   }

   const std::string &DirectionToString(int direction)
   {
      assert(IsValidDirection(direction));
      return DIRECTION_STRING_TABLE[direction];
   }

   int NextClosestDirection(int current, int desired)
   {
      int distance = DIRECTION_DISTANCE_TABLE[desired - current + 7];

      if (distance == 0 || distance == 4)
      {
         // equal or opposite
         return current;
      }

      if (distance < 0)
      {
         return PrevDirection(current);
      }
      else
      {
         return NextDirection(current);
      }
   }

   bool IsOppositeDirection(int direction1, int direction2)
   {
      return DIRECTION_DISTANCE_TABLE[direction1 - direction2 + 7] == 4;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
