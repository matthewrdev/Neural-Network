#ifndef GF1_COLOUR_H
#define GF1_COLOUR_H
//****************************************************************************
//**
//**    GF1_Vector3.h
//**    Float Colour Class and Operations
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Greg Quincey
//**    Created: 16/11/03
//**
//****************************************************************************
#include <GF1_Def.h>
#include <iostream>

   namespace GF1
   {
      // =====================================================================
      // Colour
      // =====================================================================
      // This class represents a red, green, blue colour with an optional 
      // alpha component.  
      //
      // A lot of the methods are very similar to the Vector3 class.  This is 
      // because colour can be conveniently modelled as a 3D colour space.  
      // Perception of the 3D colour space is not linear  however so this 
      // perceived distance between two colours will be different than the 
      // mathematical distance between them.
      // =====================================================================
      class GF1_API Colour
      {
      public:
         // ------------------------------------------------------------------
         // Public Data Members
         // ------------------------------------------------------------------
         // Allowing public access to data breaks object oriented
         // encapsulation.  The colour class is an exception to
         // the general rule.
         // ------------------------------------------------------------------
         float r, g, b, a;


         // ------------------------------------------------------------------
         // LuminanceStyle
         // ------------------------------------------------------------------
         // Style of luminance calculation.
         //
         // LUMINANCE_EQUAL
         //    Each component is equally weighted.
         // LUMINANCE_MAX
         //    max component is luminance
         // LUMINANCE_REC709
         //    modern monitor
         // LUMINANCE_REC601
         //    ntsc compliant monitor
         // ------------------------------------------------------------------
         enum LuminanceStyle
         {
            LUMINANCE_EQUAL,
            LUMINANCE_MAX,
            LUMINANCE_REC709,
            LUMINANCE_REC601
         };


         // ------------------------------------------------------------------
         // Component
         // ------------------------------------------------------------------
         // Component identification for swizzling.
         // ------------------------------------------------------------------
         enum Component
         {
            COMPONENT_RED,
            COMPONENT_GREEN,
            COMPONENT_BLUE,
            COMPONENT_ALPHA
         };


         // ------------------------------------------------------------------
         // Common Colour Constants
         // ------------------------------------------------------------------
         // Component identification for swizzling.
         // ------------------------------------------------------------------
         const static Colour RED;
         const static Colour GREEN;
         const static Colour BLUE;
         const static Colour WHITE;
         const static Colour BLACK;
         const static Colour YELLOW;
         const static Colour ORANGE;
         const static Colour CYAN;
         const static Colour MAGENTA;
         const static Colour PINK;


         // ------------------------------------------------------------------
         // Creators
         // ------------------------------------------------------------------
         // Construct a colour by default (0, 0, 0), by 3 components
         // or by an array of floats.
         // ------------------------------------------------------------------
         Colour();
         Colour(float rIn, float gIn, float bIn, float aIn = 1.0f);
         Colour(float cIn[4]);
         ~Colour();


         // ------------------------------------------------------------------
         // IsZero
         // ------------------------------------------------------------------
         // Are all elements of the colour zero?
         // ------------------------------------------------------------------
         bool IsZero() const;


         // ------------------------------------------------------------------
         // Length
         // ------------------------------------------------------------------
         // Determine the magnitude of a colour.
         // ------------------------------------------------------------------
         float Length() const;


         // ------------------------------------------------------------------
         // LengthSquared
         // ------------------------------------------------------------------
         // Determine the squared length of the colour.
         // Useful for comparing the relative magnitude of colours.
         // Faster than Length.
         // ------------------------------------------------------------------
         float LengthSquared() const;


         // ------------------------------------------------------------------
         // Luminance
         // ------------------------------------------------------------------
         // Calculate the luminance (brightness) of a colour.
         //
         // s
         //    The luminance style to use, see LuminanceStyle.
         // ------------------------------------------------------------------
         float Luminance(LuminanceStyle s = LUMINANCE_REC709) const;


         // ------------------------------------------------------------------
         // Swiz
         // ------------------------------------------------------------------
         // Swizzles (rearranges) the components of a colour.
         // 
         // comp1
         // comp2
         // comp3
         // comp4
         //    These components define the new order of each component within 
         //    the colour.
         //
         // Example:
         //    The following converts an RGBA colour to a BGRA colour.
         //
         //    c1.Swiz(COMPONENT_BLUE, COMPONENT_GREEN, COMPONENT_RED, 
         //       COMPONENT_ALPHA);
         // ------------------------------------------------------------------
         Colour Swiz(
            Component comp1, 
            Component comp2, 
            Component comp3, 
            Component comp4) const;


         // ------------------------------------------------------------------
         // Set
         // ------------------------------------------------------------------
         // Set the elements of the colour.
         // ------------------------------------------------------------------
         void Set(
            float r_in, 
            float g_in, 
            float b_in, 
            float a_in = 1.0f);

         void Set(float c_in[4]);


         // ------------------------------------------------------------------
         // SetZero
         // ------------------------------------------------------------------
         // Set each element of the colour to zero
         // ------------------------------------------------------------------
         void SetZero();


         // ------------------------------------------------------------------
         // Normalise
         // ------------------------------------------------------------------
         // Change the length of the colour to 1 (unit length)
         // Direction of colour stays the same.
         // Returns the length of the colour.
         // The zero colour remains the zero colour.
         // ------------------------------------------------------------------
         float Normalise();


         // ------------------------------------------------------------------
         // Clamp
         // ------------------------------------------------------------------
         // Clamp the range of colour components to 0.0 -> 1.0.
         // ------------------------------------------------------------------
         void Clamp();


         // ------------------------------------------------------------------
         // Expose
         // ------------------------------------------------------------------
         // Apply exponential exposure to a colour. Overly bright colours are 
         // reduced to fit within the 0.0 -> 1.0 range without clamping.
         //
         // exposure
         //    PRE: exposure > 0
         //    Expose simulates the exposure effect of the shutter speed of a
         //    camera. Small values ( 0 < exposure <= 1 ) result in the colours
         //    becoming very dark, but overbright colours will be remapped to
         //    non overbright colours without all being clamped. Larger values
         //    (exposure > 1) result in colours becoming brighter.
         //    Small exposure is used to make overly bright colours visible,
         //    large exposure is used to make very dark colours visible.
         // ------------------------------------------------------------------
         void Expose(float exposure);


         // ------------------------------------------------------------------
         // Vector Addition, Subtraction, Multiplication & Division
         // ------------------------------------------------------------------
         Colour &operator+=(const Colour &rhs);
         Colour &operator-=(const Colour &rhs);
         Colour &operator*=(const Colour &rhs);
         Colour &operator/=(const Colour &rhs);


         // ------------------------------------------------------------------
         // Scalar Multiplication and Division
         // ------------------------------------------------------------------
         Colour &operator*=(float rhs);
         Colour &operator/=(float rhs);


         // ------------------------------------------------------------------
         // Integer Colour Conversions
         // ------------------------------------------------------------------
         // Convert between integer and Colour types.
         //
         // redMask
         // greenMask
         // blueMask
         // alpha mask
         //    The max value of each colour component. 
         //    Must be one less than a power of 2.
         //    32 bit colours would use 255 for each.
         // redShift
         // greenShift
         // blueShift
         // alphaShift
         //       The bit position of the component's value within an integer 
         //       colour.
         // c
         //    Integer (32 bit RGBA8888) colour to convert into a float colour.
         // redValue
         // greenValue
         // blueValue
         // alphaValue
         //    Already extracted integer component values.
         //
         // Examples:
         //    standard BGRA 32 bit:
         //       int intcol = col.to_integer(255, 16, 255, 8, 255, 0, 255, 24);
         //       col.from_integer(intcol, 255, 16, 255, 8, 255, 0, 255, 24);
         //    16 bit colour:
         //       int intcol = col.to_integer(31, 11, 63, 5, 31, 0);
         //       col.from_integer(intcol, 31, 11, 63, 5, 31, 0);
         // ------------------------------------------------------------------
         int ToInteger(
            int redMask, 
            int redShift, 
            int greenMask, 
            int greenShift, 
            int blueMask, 
            int blueShift) const;

         int ToInteger(
            int redMask, 
            int redShift, 
            int greenMask, 
            int greenShift, 
            int blueMask, 
            int blueShift, 
            int alphaMask, 
            int alphaShift) const;

         void FromInteger(
            int c, 
            int redMask, 
            int redShift, 
            int greenMask, 
            int greenShift, 
            int blueMask, 
            int blueShift, 
            int alphaMask, 
            int alphaShift);

         void FromInteger(
            int c, 
            int redMask, 
            int redShift, 
            int greenMask, 
            int greenShift, 
            int blueMask, 
            int blueShift);

         void FromIntegerComponents(
            int redValue, 
            int greenValue, 
            int blueValue, 
            int alphaValue, 
            int redMask, 
            int greenMask, 
            int blueMask, 
            int alphaMask);

         void FromIntegerComponents(
            int redValue, 
            int greenValue, 
            int blueValue, 
            int redMask, 
            int greenMask, 
            int blueMask);
      };


      // ---------------------------------------------------------------------
      // DotProduct
      // ---------------------------------------------------------------------
      // Compute the dot product (ratio) between two colours
      // Allows us to calculate the angle between the colours.
      // ---------------------------------------------------------------------
      GF1_API float DotProduct(const Colour &lhs, const Colour &rhs);


      // ---------------------------------------------------------------------
      // CrossProduct
      // ---------------------------------------------------------------------
      // Compute the cross product of two colours.  The result
      // is a colours normal to the plane formed by the original
      // two colours.  The result colours is at 90 degrees to
      // the original two colours.
      // ---------------------------------------------------------------------
      GF1_API Colour CrossProduct(const Colour &lhs, const Colour &rhs);


      // ---------------------------------------------------------------------
      // Normalise
      // ---------------------------------------------------------------------
      // Non member normalise.  See Colour::Normalise.
      // ---------------------------------------------------------------------
      GF1_API Colour Normalise(const Colour &c);


      // ---------------------------------------------------------------------
      // Clamp
      // ---------------------------------------------------------------------
      // See class member function Colour::Clamp.
      // ---------------------------------------------------------------------
      GF1_API Colour Clamp(const Colour &c);


      // ---------------------------------------------------------------------
      // Expose
      // ---------------------------------------------------------------------
      // See class member function Colour::Expose.
      // ---------------------------------------------------------------------
      GF1_API Colour Expose(const Colour &c, float exposure);


      // ---------------------------------------------------------------------
      // Vector Addition, Subtraction, Multiplication & Division
      // ---------------------------------------------------------------------
      GF1_API Colour operator+(const Colour &lhs, const Colour &rhs);
      GF1_API Colour operator-(const Colour &lhs, const Colour &rhs);
      GF1_API Colour operator*(const Colour &lhs, const Colour &rhs);
      GF1_API Colour operator/(const Colour &lhs, const Colour &rhs);


      // ---------------------------------------------------------------------
      // Scalar Multiplication & Division
      // ---------------------------------------------------------------------
      GF1_API Colour operator*(const Colour &lhs, float rhs);
      GF1_API Colour operator*(float lhs, const Colour &rhs);
      GF1_API Colour operator/(const Colour &lhs, float rhs);
      GF1_API Colour operator/(float lhs, const Colour &rhs);


      // ---------------------------------------------------------------------
      // Stream Operators
      // ---------------------------------------------------------------------
      // Overload the << (stream insertion operator) for the
      // Colour class so we can easily print out colours.
      // ---------------------------------------------------------------------
      GF1_API std::ostream &operator<<(
         std::ostream &os, 
         const Colour &rhs);
   }

// Include the inline implementation
#include "GF1_Colour.inl"

//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif

