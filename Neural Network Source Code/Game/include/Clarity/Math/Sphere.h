#ifndef CLARITY_SPHERE_H
#define CLARITY_SPHERE_H


/** @file Sphere.h
 *
 *  This file contains the Sphere class definition.
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


#include <Clarity/Math/Vector3.h>

namespace Clarity
{
   class AABox;

   // =====================================================================
   // Sphere
   // =====================================================================
   // A sphere primitive, mostly used for bounds checking. 
   //
   // A sphere in math texts is normally represented by the function
   // x^2 + y^2 + z^2 = r^2 (for sphere's centered on the origin). Spheres
   // are stored simply as a centre point and a radius.
   // =====================================================================
   class  Sphere
   {
   public:
      // ---------------------------------------------------------------------
      // Sphere
      // ---------------------------------------------------------------------
      // Standard constructor - creates a unit sphere around the origin.
      // ---------------------------------------------------------------------
      Sphere();

      // ---------------------------------------------------------------------
      // Sphere
      // ---------------------------------------------------------------------
      // Constructor allowing arbitrary spheres. 
      //
      // centre 
      //    The centre point of the sphere.
      // radius 
      //    The radius of the sphere.
      // ---------------------------------------------------------------------
      Sphere(const Vector3 &centre, float radius);

      // ---------------------------------------------------------------------
      // GetRadius
      // ---------------------------------------------------------------------
      // Returns the radius of the sphere.
      // ---------------------------------------------------------------------
      float GetRadius() const;

      // ---------------------------------------------------------------------
      // SetRadius
      // ---------------------------------------------------------------------
      // Sets the radius of the sphere.
      // ---------------------------------------------------------------------
      void SetRadius(float radius);

      // ---------------------------------------------------------------------
      // GetCentre
      // ---------------------------------------------------------------------
      // Returns the centre point of the sphere.
      // ---------------------------------------------------------------------
      const Vector3 &GetCentre() const;

      // ---------------------------------------------------------------------
      // SetCentre
      // ---------------------------------------------------------------------
      // Sets the centre point of the sphere.
      // ---------------------------------------------------------------------
        void SetCentre(const Vector3 &centre);

      // ---------------------------------------------------------------------
      // Intersects
      // ---------------------------------------------------------------------
      // Returns whether or not this sphere interects another sphere.
      // ---------------------------------------------------------------------
		bool Intersects(const Sphere &s) const;

      // ---------------------------------------------------------------------
      // Intersects
      // ---------------------------------------------------------------------
      // Returns whether or not this sphere interects a box.
      // ---------------------------------------------------------------------
		bool Intersects(const AABox &box) const;


      // ---------------------------------------------------------------------
      // Intersects
      // ---------------------------------------------------------------------
      // Returns whether or not this sphere interects a plane.
      // ---------------------------------------------------------------------
		// bool Intersects(const Plane &plane) const;

      // ---------------------------------------------------------------------
      // Intersects
      // ---------------------------------------------------------------------
      // Returns whether or not this sphere interects a point.
      // ---------------------------------------------------------------------
		bool Intersects(const Vector3 &v) const;

   private:
      float m_radius;
      Vector3 m_centre;
   };
}

#endif
