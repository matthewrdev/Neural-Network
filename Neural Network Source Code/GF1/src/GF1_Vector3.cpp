//****************************************************************************
//**
//**    GF1_Vector3.cpp
//**    3D Vector Class and Operations
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Dale Freya
//**    Created: 03/09/2003
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include <GF1_Vector3.h>

   namespace GF1
   {

      float Vector3::Length() const
      {
         return (float)sqrt(x * x + y * y + z * z);
      }


      float Vector3::Normalise()
      {
         float length_squared = LengthSquared();
         float length = 0;

         if (length_squared != 0.0f)
         {
            length = static_cast<float>(sqrt(length_squared));
            float length_inverse = 1.0f / length;

            x *= length_inverse;
            y *= length_inverse;
            z *= length_inverse;
         }

         return length;
      }

      Vector3 Normalise(const Vector3 &v)
      {
         float length_squared = v.LengthSquared();
         float length_inverse = 0;

         if (length_squared != 0.0f)
         {
            length_inverse = 1.0f / static_cast<float>(sqrt(length_squared));
         }

         return Vector3(
            v.x * length_inverse, 
            v.y * length_inverse, 
            v.z * length_inverse);
      }


   }  // end namespace GF1



//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
