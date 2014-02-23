#ifndef CLARITY_MIRROR_H
#define CLARITY_MIRROR_H

/** @file Mirror.h
 *
 *  This file contains the Mirror class definition.
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

#include <Clarity/Math/Vector2.h>

namespace Clarity
{
   // ========================================================================
   // Mirror
   // ========================================================================
   enum MirrorAxis
   {
      MIRROR_AXIS_NONE,
      MIRROR_AXIS_X,
      MIRROR_AXIS_Y,
      MIRROR_AXIS_XY,
      MIRROR_AXIS_COUNT
   };

    const Vector2 &MirrorAxisToDirection(MirrorAxis mirrorAxis);
}

#endif
