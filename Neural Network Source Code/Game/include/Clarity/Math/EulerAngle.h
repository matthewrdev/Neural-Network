#ifndef CLARITY_EULERANGLE_H
#define CLARITY_EULERANGLE_H

/** @file EulerAngle.h
 *
 *  This file contains the EulerAngle structure definition.
 *
 *  This source file is part of Clarity.
 *  Clarity is a game engine designed for teaching.
 *  For the latest info, see http://members.optusnet.com.au/dfreya
 *
 *  Copyright (c) 2007 Dale Freya
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  or go to http://www.gnu.org/copyleft/lesser.txt.
 *
 */



namespace Clarity
{
   /**
    * An orientation represented by yaw, pitch and roll where yaw is rotation 
    * about the y-axis, pitch is rotation about the x-axis, and roll is 
    * rotation about the z-axis.  All angles are in radians.
    */
   struct EulerAngle
   {
      float yaw;     /**< Rotation about the y-axis */
      float pitch;   /**< Rotation about the x-axis */
      float roll;    /**< Rotation about the z-axis */
   };
}

#endif
