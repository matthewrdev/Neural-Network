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

#include <Clarity/Math/Mirror.h>
#include <cassert>

namespace Clarity
{

   namespace
   {
      const Vector2 MIRROR_TABLE[MIRROR_AXIS_COUNT] =
      {
         Vector2( 1.0f,  1.0f),
         Vector2(-1.0f,  1.0f),
         Vector2( 1.0f, -1.0f),
         Vector2(-1.0f, -1.0f)
      };
   }

   const Vector2 &MirrorAxisToDirection(MirrorAxis mirrorAxis)
   {
      assert(mirrorAxis < MIRROR_AXIS_COUNT);
      return MIRROR_TABLE[mirrorAxis];
   }


}

//****************************************************************************
//**
//**   END IMPLEMENTATION 
//**
//****************************************************************************
