#ifndef GF1_VECTOR3_INL
#define GF1_VECTOR3_INL
//****************************************************************************
//**
//**    GF1_Vector3.inl
//**    3D Vector Class and Operations
//**    Inline Implmentation
//**
//**    Copyright (c) 2003 Dale Freya
//**
//**    Author:  Dale Freya
//**    Created: 03/09/2003
//**
//****************************************************************************

   namespace GF1
   {

      inline Vector3::Vector3()
      {
         SetZero();
      }


      inline Vector3::Vector3(float x_in, float y_in, float z_in)
      {
         Set(x_in, y_in, z_in);
      }


      inline Vector3::Vector3(float v_in[3])
      {
         Set(v_in);
      }


      inline Vector3::~Vector3()
      {
      }


      inline bool Vector3::IsZero() const
      {
         return (x == 0 && y == 0 && z == 0);
      }


      inline void Vector3::Set(float x_in, float y_in, float z_in)
      {
         x = x_in;
         y = y_in;
         z = z_in;
      }


      inline void Vector3::Set(float v_in[3])
      {
         x = v_in[0];
         y = v_in[1];
         z = v_in[2];
      }


      inline void Vector3::SetZero()
      {
         Set(0, 0, 0);
      }


      inline float Vector3::LengthSquared() const
      {
         return (x * x + y * y + z * z);
      }


      inline Vector3 &Vector3::operator+=(const Vector3 &rhs)
      {
         x += rhs.x;
         y += rhs.y;
         z += rhs.z;

         return *this;
      }

      inline Vector3 &Vector3::operator-=(const Vector3 &rhs)
      {
         x -= rhs.x;
         y -= rhs.y;
         z -= rhs.z;

         return *this;
      }

      inline Vector3 &Vector3::operator*=(const Vector3 &rhs)
      {
         x *= rhs.x;
         y *= rhs.y;
         z *= rhs.z;

         return *this;
      }

      inline Vector3 &Vector3::operator/=(const Vector3 &rhs)
      {
         x /= rhs.x;
         y /= rhs.y;
         z /= rhs.z;

         return *this;
      }

      inline Vector3 &Vector3::operator*=(float rhs)
      {
         x *= rhs;
         y *= rhs;
         z *= rhs;

         return *this;
      }

      inline Vector3 &Vector3::operator/=(float rhs)
      {
         x /= rhs;
         y /= rhs;
         z /= rhs;

         return *this;
      }



      inline Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
      {
         return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
      }



      inline Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
      {
         return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
      }


      inline Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs)
      {
         return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
      }


      inline Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs)
      {
         return Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
      }

      inline Vector3 operator*(const Vector3 &lhs, float rhs)
      {
         return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
      }

      inline Vector3 operator/(const Vector3 &lhs, float rhs)
      {
         return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
      }

      inline Vector3 operator*(float lhs, const Vector3 &rhs)
      {
         return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
      }

      inline Vector3 operator/(float lhs, const Vector3 &rhs)
      {
         return Vector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
      }

      inline std::ostream &operator<<(std::ostream &os, const Vector3 &rhs)
      {
         os << "<" << rhs.x << ", " << rhs.y << ", " << rhs.z << ">";

         return os;
      }


      inline float DotProduct(const Vector3 &lhs, const Vector3 &rhs)
      {
         return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
      }

      inline Vector3 CrossProduct(const Vector3 &lhs, const Vector3 &rhs)
      {
         return Vector3(
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
            );
      }


   }  // end namespace GF1



//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif