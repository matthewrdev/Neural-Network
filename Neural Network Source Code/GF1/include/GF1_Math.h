#ifndef GF1_MATH_H
#define GF1_MATH_H
//****************************************************************************
//**
//**    GF1_Math.h
//**    Mathematic Utilities Module
//**    Contains Common Mathematical Constants and Operations
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include <GF1_Def.h>
#include <cassert>

   namespace GF1
   {
      // ---------------------------------------------------------------------
      // Degrees and Radians Conversion
      // ---------------------------------------------------------------------
      const float DEGS_PER_RAD = 57.29578f;
      const float RADS_PER_DEG = 1.0f / DEGS_PER_RAD;

      GF1_API float RadToDeg(float radians);
      GF1_API float DegToRad(float degrees);


      // ---------------------------------------------------------------------
      // Common Mathematical Constants
      // ---------------------------------------------------------------------
      const float PI = 3.14159f;


      // ---------------------------------------------------------------------
      // Lerp
      // ---------------------------------------------------------------------
      // Linearly interpolates between the first 2 parameters by the fraction
      // in the third parameter. 
      //
      // typename T1
      //    Must support all of the following: 
      //       T1 - T1 == T1
      //       T1 + T1 == T1
      //       T1 * T2 == T1
      // typename T2 
      //    Must be float or double.
      //
      // val1
      //    Start of range.
      // val2
      //    End of range.
      // t
      //    Fraction describing the amount through the Lerp.
      //    Generally in the range 0 <= t <= 1. If t is outside of the range
      //    0 <= t <= 1 then the result will be outside the val1 <= val2
      //    range.  This allows for extrapolation as well as interpolation.
      //
      // POSTCONDITIONS
      //    t == 0  => (result = val1)
      //    t == 1  => (result = val2)
      //    t > 0   => (result is between val1 and val2)
      //    t < 1   => (result is between val1 and val2)
      // ---------------------------------------------------------------------
      template<typename T1, typename T2>
      T1 Lerp(const T1 &val1, const T1 &val2, const T2 &t);


      // ---------------------------------------------------------------------
      // SCurve
      // ---------------------------------------------------------------------
      // Remaps a linear value to a sigmoid curve (similar to a sine wave
      // between values of -pi/2 and pi/2).
      //
      // typename T
      //    Must support the following:
      //       T * T == T
      //       double * T == T
      //       double - T == T
      //
      // val
      //    Value in the range 0 <= val <= 1 which will be converted to a 
      //    sigmoid curve.
      //
      // PRECONDITIONS
      //    0 <= val <= 1  (for any component of type T)
      // ---------------------------------------------------------------------
      template<typename T>
      T SCurve(const T &val);


      // ---------------------------------------------------------------------
      // Remap
      // ---------------------------------------------------------------------
      // Remaps a number from one range to another.
      // The value to remap doesn't have to be in the range
      //
      // typename T
      //    Must support all of the following: 
      //       T1 + T1 == T1
      //       T1 - T1 == T1
      //       T1 * T1 == T1
      //       T1 / T1 == T1
      //
      // srcRangeStart
      // srcRangeEnd
      //    Define the source range.
      // dstRangeStart
      // dstRangeEnd
      //    Define the destination range.
      // valueToRemap
      //    The value to be mapped from the source range to the destination 
      //    range. If the value is outside of the source range, then it is
      //    mapped to a corresponding value outside of the destination range.
      //
      // PRECONDITIONS
      //    (srcRangeEnd - srcRangeStart) != 0
      // ---------------------------------------------------------------------
      template<typename T>
      T Remap(
         const T &srcRangeStart, 
         const T &srcRangeEnd, 
         const T &dstRangeStart, 
         const T &dstRangeEnd, 
         const T &valueToRemap);

   }  // end namespace GF1


// Include the inline implementation
#include <GF1_Math.inl>

//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif

