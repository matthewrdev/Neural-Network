#ifndef GF1_COLOUR_INL
#define GF1_COLOUR_INL
//****************************************************************************
//**
//**    GF1_Colour.inl
//**    Float Colour Class and Operations
//**    Inline Implmentation
//**
//**    Copyright (c) 2003 
//**
//**    Author:  Greg Q
//**    Created: 16/11/03
//**
//****************************************************************************
#include <cmath>
#include <cassert>

   namespace GF1
   {

      inline Colour::Colour()
      {
         SetZero();
      }


      inline Colour::Colour(float rIn, float gIn, float bIn, float aIn)
      {
         Set(rIn, gIn, bIn, aIn);
      }


      inline Colour::Colour(float cIn[4])
      {
         Set(cIn);
      }


      inline Colour::~Colour()
      {
      }


      inline bool Colour::IsZero() const
      {
         return (r == 0 && g == 0 && b == 0);
      }


      inline void Colour::Set(float rIn, float gIn, float bIn, float aIn)
      {
         r = rIn;
         g = gIn;
         b = bIn;
         a = aIn;
      }


      inline void Colour::Set(float cIn[4])
      {
         r = cIn[0];
         g = cIn[1];
         b = cIn[2];
         a = cIn[3];
      }


      inline void Colour::SetZero()
      {
         Set(0, 0, 0);
      }


      inline float Colour::LengthSquared() const
      {
         return (r * r + g * g + b * b);
      }


      inline Colour &Colour::operator+=(const Colour &rhs)
      {
         r += rhs.r;
         g += rhs.g;
         b += rhs.b;

         return *this;
      }


      inline Colour &Colour::operator-=(const Colour &rhs)
      {
         r -= rhs.r;
         g -= rhs.g;
         b -= rhs.b;

         return *this;
      }


      inline Colour &Colour::operator*=(const Colour &rhs)
      {
         r *= rhs.r;
         g *= rhs.g;
         b *= rhs.b;

         return *this;
      }


      inline Colour &Colour::operator/=(const Colour &rhs)
      {
         r /= rhs.r;
         g /= rhs.g;
         b /= rhs.b;

         return *this;
      }


      inline Colour &Colour::operator*=(float rhs)
      {
         r *= rhs;
         g *= rhs;
         b *= rhs;

         return *this;
      }


      inline Colour &Colour::operator/=(float rhs)
      {
         r /= rhs;
         g /= rhs;
         b /= rhs;

         return *this;
      }


      inline Colour Clamp(const Colour &c)
      {
         float rr = c.r;
         float gg = c.g;
         float bb = c.b;
         float aa = c.a;

         if (rr > 1.0)
         {
            rr = 1.0;
         }
         else if (rr < 0)
         {
            rr = 0;
         }

         if (gg > 1.0)
         {
            gg = 1.0;
         }
         else if (gg < 0)
         {
            gg = 0;
         }

         if (bb > 1.0)
         {
            bb = 1.0;
         }
         else if (bb < 0)
         {
            bb = 0;
         }

         if (aa > 1.0)
         {
            aa = 1.0;
         }
         else if (aa < 0)
         {
            aa = 0;
         }

         return Colour(rr, gg, bb, aa);
      }


      inline void Colour::Clamp()
      {
         if (r > 1.0)
         {
            r = 1.0;
         }
         else if (r < 0)
         {
            r = 0;
         }
         if (g > 1.0)
         {
            g = 1.0;
         }
         else if (g < 0)
         {
            g = 0;
         }
         if (b > 1.0)
         {
            b = 1.0;
         }
         else if (b < 0)
         {
            b = 0;
         }
         if (a > 1.0)
         {
            a = 1.0;
         }
         else if (a < 0)
         {
            a = 0;
         }
      }


      inline Colour operator+(const Colour &lhs, const Colour &rhs)
      {
         return Colour(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
      }


      inline Colour operator-(const Colour &lhs, const Colour &rhs)
      {
         return Colour(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
      }


      inline Colour operator*(const Colour &lhs, const Colour &rhs)
      {
         return Colour(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
      }


      inline Colour operator/(const Colour &lhs, const Colour &rhs)
      {
         return Colour(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b);
      }


      inline Colour operator*(const Colour &lhs, float rhs)
      {
         return Colour(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
      }


      inline Colour operator/(const Colour &lhs, float rhs)
      {
         return Colour(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs);
      }


      inline Colour operator*(float lhs, const Colour &rhs)
      {
         return Colour(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b);
      }


      inline Colour operator/(float lhs, const Colour &rhs)
      {
         return Colour(lhs / rhs.r, lhs / rhs.g, lhs / rhs.b);
      }


      inline std::ostream &operator<<(std::ostream &os, const Colour &rhs)
      {
         os << "<" <<
            "R:" << rhs.r << ", " <<
            "G:" << rhs.g << ", " <<
            "B:" << rhs.b << ", " <<
            "A:" << rhs.a << ">";

         return os;
      }


      inline float DotProduct(const Colour &lhs, const Colour &rhs)
      {
         return (lhs.r * rhs.r + lhs.g * rhs.g + lhs.b * rhs.b);
      }

      inline Colour CrossProduct(const Colour &lhs, const Colour &rhs)
      {
         return Colour(
            lhs.g * rhs.b - lhs.b * rhs.g,
            lhs.b * rhs.r - lhs.r * rhs.b,
            lhs.r * rhs.g - lhs.g * rhs.r
            );
      }


      inline void Colour::Expose(float exposure)
      {
         assert(exposure > 0.0f);

         Set(
            1.0f - (float)exp(-r * exposure), 
            1.0f - (float)exp(-g * exposure), 
            1.0f - (float)exp(-b * exposure), 
            a);
      }


      inline Colour Colour::Swiz(
         Colour::Component comp1, 
         Colour::Component comp2, 
         Colour::Component comp3, 
         Colour::Component comp4) const
      {
         return Colour(
            comp1 == COMPONENT_RED   ? r : 
           (comp1 == COMPONENT_GREEN ? g : 
           (comp1 == COMPONENT_BLUE  ? b : 
           (comp1 == COMPONENT_ALPHA ? a : 0))),

            comp2 == COMPONENT_RED   ? r : 
           (comp2 == COMPONENT_GREEN ? g : 
           (comp2 == COMPONENT_BLUE  ? b : 
           (comp2 == COMPONENT_ALPHA ? a : 0))),

            comp3 == COMPONENT_RED ? r : 
           (comp3 == COMPONENT_GREEN ? g : 
           (comp3 == COMPONENT_BLUE ? b : 
           (comp3 == COMPONENT_ALPHA ? a : 0))),

            comp4 == COMPONENT_RED   ? r : 
           (comp4 == COMPONENT_GREEN ? g : 
           (comp4 == COMPONENT_BLUE  ? b : 
           (comp4 == COMPONENT_ALPHA ? a : 0))));
      }


      inline Colour Expose(const Colour &c, float exposure)
      {
         return Colour(
            1.0f - (float)exp(-c.r * exposure), 
            1.0f - (float)exp(-c.g * exposure), 
            1.0f - (float)exp(-c.b * exposure), 
            c.a);
      }


      inline int Colour::ToInteger(
         int redMask, 
         int redShift, 
         int greenMask, 
         int greenShift, 
         int blueMask, 
         int blueShift) const
      {
         Colour temp = GF1::Clamp(*this);
         
         return 
            ((int)(temp.r * redMask  ) << redShift  ) | 
            ((int)(temp.g * greenMask) << greenShift) | 
            ((int)(temp.b * blueMask ) << blueShift );
      }


      inline int Colour::ToInteger(
         int redMask, 
         int redShift, 
         int greenMask, 
         int greenShift, 
         int blueMask, 
         int blueShift, 
         int alphaMask, 
         int alphaShift) const
      {
         Colour temp = GF1::Clamp(*this);

         return 
            (int(temp.r * redMask  ) << redShift  ) | 
            (int(temp.g * greenMask) << greenShift) | 
            (int(temp.b * blueMask ) << blueShift ) | 
            (int(temp.a * alphaMask) << alphaShift);
      }


      inline void Colour::FromInteger(
         int c, 
         int redMask, 
         int redShift, 
         int greenMask, 
         int greenShift, 
         int blueMask, 
         int blueShift, 
         int alphaMask, 
         int alphaShift)
      {
         r = ((c >> redShift  ) & redMask  ) / (float)redMask;
         g = ((c >> greenShift) & greenMask) / (float)greenMask;
         b = ((c >> blueShift ) & blueMask ) / (float)blueMask;
         a = ((c >> alphaShift) & alphaMask) / (float)alphaMask;
      }


      inline void Colour::FromInteger(
         int c, 
         int redMask, 
         int redShift, 
         int greenMask, 
         int greenShift, 
         int blueMask, 
         int blueShift)
      {
         r = ((c >> redShift  ) & redMask  ) / (float)redMask;
         g = ((c >> greenShift) & greenMask) / (float)greenMask;
         b = ((c >> blueShift ) & blueMask ) / (float)blueMask;
         a = 1.0f;
      }


      inline void Colour::FromIntegerComponents(
         int redValue, 
         int greenValue, 
         int blueValue, 
         int alphaValue, 
         int redMask, 
         int greenMask, 
         int blueMask, 
         int alphaMask)
      {
         r = (redValue   & redMask  ) / (float)redMask;
         g = (greenValue & greenMask) / (float)greenMask;
         b = (blueValue  & blueMask ) / (float)blueMask;
         a = (alphaValue & alphaMask) / (float)alphaMask;
      }


      inline void Colour::FromIntegerComponents(
         int redValue, 
         int greenValue, 
         int blueValue, 
         int redMask, 
         int greenMask, 
         int blueMask)
      {
         r = (redValue   & redMask  ) / (float)redMask;
         g = (greenValue & greenMask) / (float)greenMask;
         b = (blueValue  & blueMask ) / (float)blueMask;
      }

   }  // end namespace GF1




//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
