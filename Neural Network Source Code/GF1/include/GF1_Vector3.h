#ifndef GF1_VECTOR3_H
#define GF1_VECTOR3_H
//****************************************************************************
//**
//**    GF1_Vector3.h
//**    3D Vector Class and Operations
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Dale Freya
//**    Created: 03/09/2003
//**
//****************************************************************************
#include <GF1_Def.h>
#include <iostream>

   namespace GF1
   {

      class GF1_API Vector3
      {
      public:
         // PUBLIC DATA MEMBERS
         float x, y, z;
         // Allowing public access to data breaks object oriented
         // encapsulation.  The vector class is an exception to
         // the general rule.

         // CREATORS

         // Construct a vector by default (0, 0, 0), by 3 components
         // or by an array of floats.
         Vector3();
         Vector3(float x_in, float y_in, float z_in);
         Vector3(float v_in[3]);

         // Destruct a vector
         ~Vector3();


         // ACCESSORS

         // Are all elements of the vector zero
         bool IsZero() const;

         // Determine the length of a vector
         float Length() const;

         // Determine the squared length of the vector.
         // Useful for comparing the relative length of vectors.
         // Faster than Length
         float LengthSquared() const;


         // MANIPULATORS

         // Set the elements of the vector
         void Set(float x_in, float y_in, float z_in);
         void Set(float v_in[3]);

         // Set each element of the vector to zero
         void SetZero();

         // Change the length of the vector to 1 (unit length)
         // Direction of vector stays the same
         // Returns the length of the vector
         // The zero vector remains the zero vector
         float Normalise();

         // Vector addition/subtraction/multiplication/division
         Vector3 &operator+=(const Vector3 &rhs);
         Vector3 &operator-=(const Vector3 &rhs);
         Vector3 &operator*=(const Vector3 &rhs);
         Vector3 &operator/=(const Vector3 &rhs);

         // Scalar multiplication/division
         Vector3 &operator*=(float rhs);
         Vector3 &operator/=(float rhs);
      };



      // Compute the dot product (ratio) between two vectors
      // Allows us to calculate the angle between the vectors.
      GF1_API float DotProduct(const Vector3 &lhs, const Vector3 &rhs);


      // Compute the cross product of two vectors.  The result
      // is a vector normal to the plane formed by the original
      // two vectors.  The result vector is at 90 degrees to
      // the original two vectors.
      GF1_API Vector3 CrossProduct(const Vector3 &lhs, const Vector3 &rhs);

      // Non member normalise.
      GF1_API Vector3 Normalise(const Vector3 &lhs);


      // Vector addition/subtraction/multiply/divide
      GF1_API Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);
      GF1_API Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);
      GF1_API Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs);
      GF1_API Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs);

      // Scalar multiplication/division
      GF1_API Vector3 operator*(const Vector3 &lhs, float rhs);
      GF1_API Vector3 operator*(float lhs, const Vector3 &rhs);
      GF1_API Vector3 operator/(const Vector3 &lhs, float rhs);
      GF1_API Vector3 operator/(float lhs, const Vector3 &rhs);

      // Overload the << (stream insertion operator) for the
      // Vector3 class so we can easily print out vectors.
      GF1_API std::ostream &operator<<(std::ostream &os, const Vector3 &rhs);


   }  // end namespace GF1


#include "GF1_Vector3.inl"
  // Include the inline implementation

//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif