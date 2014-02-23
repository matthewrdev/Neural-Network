//****************************************************************************
//**
//**    GF1_Colour.cpp
//**    Float Colour Class and Operations
//**
//**    Copyright (c) 2003 
//**
//**    Author:  Greg Q
//**    Created: 16/11/03
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include <GF1_Colour.h>
#include <cmath>

   namespace GF1
   {

      const Colour Colour::RED     = Colour(1,0,0);
      const Colour Colour::GREEN   = Colour(0,1,0);
      const Colour Colour::BLUE    = Colour(0,0,1);
      const Colour Colour::WHITE   = Colour(1,1,1);
      const Colour Colour::BLACK   = Colour(0,0,0);
      const Colour Colour::YELLOW  = Colour(1,1,0);
      const Colour Colour::ORANGE  = Colour(1,0.5,0);
      const Colour Colour::CYAN    = Colour(0,1,1);
      const Colour Colour::MAGENTA = Colour(1,0,1);
      const Colour Colour::PINK    = Colour(1.0f, 0.1f, 0.5f);

      float Colour::Length() const
      {
         return (float)sqrt(r * r + g * g + b * b);
      }


      float Colour::Normalise()
      {
         float length_squared = LengthSquared();
         float length = 0;

         if (length_squared != 0.0f)
         {
            length = static_cast<float>(sqrt(length_squared));
            float length_inverse = 1.0f / length;

            r *= length_inverse;
            g *= length_inverse;
            b *= length_inverse;
         }

         return length;
      }


      Colour Normalise(const Colour &v)
      {
         float length_squared = v.LengthSquared();
         float length_inverse = 0;

         if (length_squared != 0.0f)
         {
            length_inverse = 1.0f / static_cast<float>(sqrt(length_squared));
         }

         return Colour(
            v.r * length_inverse, 
            v.g * length_inverse, 
            v.b * length_inverse);
      }


      float Colour::Luminance(Colour::LuminanceStyle s) const
      {
         switch(s)
         {
         case LUMINANCE_REC709:
            return (0.212671f * r + 0.715160f * g + 0.072169f * b);
            break;

         case LUMINANCE_REC601:
            return (0.299f * r + 0.587f * g + 0.114f * b);
            break;

         case LUMINANCE_MAX:
            {
               float rg = r > g ? r : g;
               return rg > b ? rg : b;
            }
            break;

         case LUMINANCE_EQUAL:
         default:
            return (r + g + b)/3.0f;
         }
      }


   }  // end namespace GF1



//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
