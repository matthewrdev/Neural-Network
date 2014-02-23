//****************************************************************************
//**
//**    $Workfile: Clarity_Quaternion.cpp $
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

#include <Clarity/Math/Quaternion.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Matrix4.h>
#include <Clarity/Math/Vector3.h>
#include <Clarity/Math/Math.h>

namespace Clarity
{
   const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
   const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

   Quaternion::Quaternion()
   {
      *this = IDENTITY;
   }

   Quaternion::Quaternion(float wIn, float xIn, float yIn, float zIn)
   {
      w = wIn;
      x = xIn;
      y = yIn;
      z = zIn;
   }

   Quaternion::Quaternion(const Matrix3 &rotMat)
   {
      *this = rotMat;
   }

   Quaternion::Quaternion(const Matrix4 &rotMat)
   {
      *this = Matrix3(rotMat);
   }

   Quaternion::Quaternion(float angle, const Vector3 &axis)
   {
      // assert:  axis[] is unit mag
      //
      // The quaternion representing the rotation is
      //   q = cos(A / 2) + sin(A / 2) * (x * i + y * j + z * k)
      float halangle = 0.5f * angle;
      float sinA = Sin(halangle);
      float cosA = Cos(halangle);

      w = cosA;
      x = sinA * axis.x;
      y = sinA * axis.y;
      z = sinA * axis.z;
   }

   Quaternion::~Quaternion()
   {
   }

   Quaternion &Quaternion::operator=(const Matrix3 &rotMat)
   {
      // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
      // article "Quaternion Calculus and Fast Animation".

      float trace = rotMat(0, 0) + rotMat(1, 1) + rotMat(2, 2);
      float root;

      if (trace > 0.0)
      {
         // |w| > 1/2, may as well choose w > 1/2
         root = Sqrt(trace + 1.0f);  // 2w
         w = 0.5f * root;
         root = 0.5f / root;  // 1/(4w)
         x = (rotMat(2, 1) - rotMat(1, 2)) * root;
         y = (rotMat(0, 2) - rotMat(2, 0)) * root;
         z = (rotMat(1, 0) - rotMat(0, 1)) * root;
      }
      else
      {
         // |w| <= 1/2
         static int next[3] = { 1, 2, 0 };
         int i = 0;

         if (rotMat(1, 1) > rotMat(0, 0))
         {
            i = 1;
         }

         if (rotMat(2, 2) > rotMat(i, i))
         {
            i = 2;
         }

         int j = next[i];
         int k = next[j];

         root = Sqrt(rotMat(i, i) - rotMat(j, j) - rotMat(k, k) + 1.0f);

         float* quat[3] = { &x, &y, &z };
         *quat[i] = 0.5f * root;

         root = 0.5f / root;
         w = (rotMat(k, j) - rotMat(j, k)) * root;

         *quat[j] = (rotMat(j, i) + rotMat(i, j)) * root;
         *quat[k] = (rotMat(k, i) + rotMat(i, k)) * root;
      }

      return *this;
   }

   Quaternion &Quaternion::operator=(const Matrix4 &rotMat)
   {
      *this = Matrix3(rotMat);
      return *this;
   }

   void Quaternion::ToAngleAxis(float &angle, Vector3 &axis) const
   {
      // The quaternion representing the rotation is
      //   q = cos(A / 2) + sin(A / 2) * (x * i + y * j + z * k)

      float norm = Norm();

      if (norm > EPSILON)
      {
         angle = 2.0f * ACos(w);
         float invMag = InvSqrt(norm);
         axis.x = x * invMag;
         axis.y = y * invMag;
         axis.z = z * invMag;
      }
      else
      {
         // angle is 0 (mod 2 * pi), so use the Z axis so 2D will work
         angle = 0.0;
         axis.x = 0.0;
         axis.y = 0.0;
         axis.z = 1.0;
      }
   }

   Quaternion &Quaternion::operator+=(const Quaternion &rhs)
   {
      w += rhs.w;
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;

      return *this;
   }

   Quaternion &Quaternion::operator-=(const Quaternion &rhs)
   {
      w -= rhs.w;
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;

      return *this;
   }

   Quaternion &Quaternion::operator*=(const Quaternion &rhs)
   {
      Quaternion temp(*this * rhs);
      *this = temp;
      return *this;
   }

   Quaternion &Quaternion::operator*=(float rhs)
   {
      w *= rhs;
      x *= rhs;
      y *= rhs;
      z *= rhs;
      return *this;
   }

   bool Quaternion::IsIdentity() const
   {
      return (w == 1 && x == 0 && y == 0 && z == 0);
   }

   float Quaternion::Magnitude() const
   {
      return Sqrt(Norm());
   }

   float Quaternion::Norm() const
   {
      return x * x + y * y + z * z;
   }

   float Quaternion::Normalise()
   {
      float mag;
      float norm = Norm();

      if (norm > 0.0f)
      {
         mag = Sqrt(norm);
         float invMag = 1.0f / mag;
         x *= invMag;
         y *= invMag;
         z *= invMag;
      }
      else
      {
         // set to an invalid result to flag the error
         *this = ZERO;
         mag = 0.0f;
      }

      return mag;
   }

   Quaternion Quaternion::Conjugate() const
   {
      return Quaternion(w, -x, -y, -z);
   }

   Quaternion Quaternion::Inverse() const
   {
      float norm = Norm();

      if (norm > 0.0f)
      {
         float invLenSq = 1.0f / norm;
         return Quaternion(w * invLenSq, -x * invLenSq, -y * invLenSq, -z * invLenSq);
      }
      else
      {
         // return an invalid result to flag the error
         return ZERO;
      }
   }

   Quaternion Quaternion::Exp() const
   {
      // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit mag, then
      // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
      // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

      float angle = Sqrt(x * x + y * y + z * z);
      float sinA = Sin(angle);

      Quaternion result;
      result.w = Cos(angle);

      if (Abs(sinA) >= EPSILON)
      {
         float coeff = sinA / angle;
         result.x = coeff * x;
         result.y = coeff * y;
         result.z = coeff * z;
      }
      else
      {
         result.x = x;
         result.y = y;
         result.z = z;
      }

      return result;
   }

   Quaternion Quaternion::Ln() const
   {
      // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit mag, then
      // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
      // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

      Quaternion result;
      result.w = 0.0;

      if (Abs(w) < 1.0)
      {
         float angle = ACos(w);
         float sinA = Sin(angle);

         if (Abs(sinA) >= EPSILON)
         {
            float fCoeff = angle / sinA;
            result.x = fCoeff * x;
            result.y = fCoeff * y;
            result.z = fCoeff * z;
            return result;
         }
      }

      result.x = x;
      result.y = y;
      result.z = z;

      return result;
   }

   float Quaternion::Dot(const Quaternion &lhs, const Quaternion &rhs)
   {
      return 
         lhs.w * rhs.w + 
         lhs.x * rhs.x + 
         lhs.y * rhs.y + 
         lhs.z * rhs.z;
   }

   Quaternion Quaternion::Slerp(
      float t, 
      const Quaternion &q1,
      const Quaternion &q2, 
      bool shortestPath)
   {
      float cosA = Dot(q1, q2);
      float angle = ACos(cosA);

      if (Abs(angle) < EPSILON)
      {
         return q1;
      }

      float sinA = Sin(angle);
      float invSinA = 1.0f / sinA;
      float coeff0 = Sin((1.0f - t) * angle) * invSinA;
      float coeff1 = Sin(t * angle) * invSinA;

      // Do we need to invert rotation?
      if (cosA < 0.0f && shortestPath)
      {
         coeff0 = -coeff0;
         // taking the complement requires renormalisation
         Quaternion result(coeff0 * q1 + coeff1 * q2);
         result.Normalise();
         return result;
      }
      else
      {
         return coeff0 * q1 + coeff1 * q2;
      }
   }

   Quaternion Quaternion::SlerpExtraSpins(
      float t,
      const Quaternion &q1, 
      const Quaternion &q2,
      int extraSpins)
   {
      float cosA = Dot(q1, q2);
      float angle = ACos(cosA);

      if (Abs(angle) < EPSILON)
      {
         return q1;
      }

      float sinA = Sin(angle);
      float phase = PI * extraSpins * t;
      float invSinA = 1.0f / sinA;
      float coeff0 = Sin((1.0f - t) * angle - phase) * invSinA;
      float coeff1 = Sin(t * angle + phase) * invSinA;
      return coeff0 * q1 + coeff1 * q2;
   }

   void Quaternion::SetupSquad(
      const Quaternion &q0,
      const Quaternion &q1, 
      const Quaternion &q2,
      Quaternion &a, 
      Quaternion &b)
   {
      // assert:  q0, q1, q2 are unit quaternions

      Quaternion q0inv = q0.Conjugate();
      Quaternion q1inv = q1.Conjugate();
      Quaternion p0 = q0inv * q1;
      Quaternion p1 = q1inv * q2;
      Quaternion arg = 0.25f * (p0.Ln() - p1.Ln());
      Quaternion minusArg = -arg;

      a = q1 * arg.Exp();
      b = q1 * minusArg.Exp();
   }

   Quaternion Quaternion::Squad(
      float t, 
      const Quaternion &p,
      const Quaternion &a, 
      const Quaternion &b,
      const Quaternion &q, 
      bool shortestPath)
   {
      float slerpT = 2.0f * t * (1.0f - t);
      Quaternion slerpP = Slerp(t, p, q, shortestPath);
      Quaternion slerpQ = Slerp(t, a, b);
      return Slerp(slerpT, slerpP ,slerpQ);
   }

   Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs)
   {
      Quaternion temp(lhs);
      temp += rhs;
      return temp;
   }

   Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs)
   {
      Quaternion temp(lhs);
      temp -= rhs;
      return temp;
   }

   Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs)
   {
      return Quaternion(
         lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
         lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
         lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
         lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x);
   }

   Vector3 operator*(const Quaternion &lhs, const Vector3 &rhs)
   {
      // nVidia SDK implementation
      Vector3 uv, uuv; 
      Vector3 qvec(lhs.x, lhs.y, lhs.z);
      uv = Vector3::CrossProduct(qvec, rhs); 
      uuv = Vector3::CrossProduct(qvec, uv); 
      uv *= (2.0f * lhs.w); 
      uuv *= 2.0f; 
      return rhs + uv + uuv;
   }

   Quaternion operator*(float lhs, const Quaternion &rhs)
   {
      return Quaternion(lhs * rhs.w, lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
   }

   Quaternion operator*(const Quaternion &lhs, float rhs)
   {
      Quaternion temp(lhs);
      temp *= rhs;
      return temp;
   }

   Quaternion operator-(const Quaternion &op)
   {
      return Quaternion(-op.w, -op.x, -op.y, -op.z);
   }

   Quaternion operator~(const Quaternion &op)
   {
      return op.Conjugate();
   }

   std::ostream &operator<<(std::ostream &lhs, const Quaternion &rhs)
   {
      float angle;
      Vector3 axis;
      rhs.ToAngleAxis(angle, axis);

      lhs << "Quaternion(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << "; " << RadiansToDegrees(angle) << " " << axis << ")";
      return lhs;
   }

}  // end namespace

//****************************************************************************
//**
//**    END IMPLEMENTATION 
//**
//****************************************************************************
