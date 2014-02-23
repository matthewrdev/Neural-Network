#ifndef GF1_MATH_INL
#define GF1_MATH_INL
//****************************************************************************
//**
//**    GF1_Math.inl
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Dale Freya
//**    Created: 17/11/2003
//**
//****************************************************************************
#include <GF1_Def.h>
#include <cassert>

   namespace GF1
   {
      // ---------------------------------------------------------------------
      // Degrees and Radians Conversion
      // ---------------------------------------------------------------------
      GF1_API inline float RadToDeg(float radians) 
      { 
         return radians * DEGS_PER_RAD; 
      }

      GF1_API inline float DegToRad(float degrees) 
      { 
         return degrees * RADS_PER_DEG; 
      }


      // ---------------------------------------------------------------------
      // Lerp
      // ---------------------------------------------------------------------
      template<typename T1, typename T2>
      inline T1 Lerp(const T1 &val1, const T1 &val2, const T2 &t)
      {
         return (val2 - val1) * t + val1;
      }


      // ---------------------------------------------------------------------
      // SCurve
      // ---------------------------------------------------------------------
      template<typename T>
      inline T SCurve(const T &val)
      {
         assert(0.0 <= val && val <= 1.0);
         return val * val * (3.0 - 2.0 * val);
      } 


      // ---------------------------------------------------------------------
      // Remap
      // ---------------------------------------------------------------------
      template<typename T>
      inline T Remap(
         const T &srcRangeStart, 
         const T &srcRangeEnd, 
         const T &dstRangeStart, 
         const T &dstRangeEnd, 
         const T &valueToRemap)
      {
         assert((srcRangeEnd - srcRangeStart) != 0);

         return 
            ((dstRangeEnd - dstRangeStart) * 
             (valueToRemap - srcRangeStart)) / 
             (srcRangeEnd - srcRangeStart) + dstRangeStart;
      }

   }  // end namespace GF1


//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
