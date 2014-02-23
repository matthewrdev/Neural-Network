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
#include "GF1_Graphics.h"
#include "GF1_Colour.h"
#include "GF1_Vector3.h"
#include "GF1_Types.h"
#include "GF1_Math.h"

   namespace GF1
   {

      namespace
      {
         // ------------------------------------------------------------------
         // PolyPrimitive
         // ------------------------------------------------------------------
         struct PolyPrimitive
         {
            // ---------------------------------------------------------------
            // PolyPrimitiveTypes
            // ---------------------------------------------------------------
            enum PolyPrimitiveTypes
            {
               POLY_LINE,
               POLY_VECTOR,
               POLY_RECTANGLE,
               POLY_CIRCLE,
               POLY_FILLED_RECTANGLE,
               POLY_FILLED_CIRCLE
            };

            PolyPrimitiveTypes m_type;
            Colour m_colour1;
            Colour m_colour2;
            Colour m_colour3;
            Colour m_colour4;
            Vector3 m_pos1;
            Vector3 m_pos2;
            float m_data1;
            float m_data2;
            float m_width;
            bool m_blend;
         };

         const fdword MAX_PRIMITIVES = 10000;
         fdword polyPrimitiveCount = 0;
         PolyPrimitive polyPrimitives[MAX_PRIMITIVES];
      }


      int GetMaxPrimitives()
      {
         return MAX_PRIMITIVES;
      }


      void RenderLine(const PolyPrimitive &p)
      {
         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);
         glLineWidth(p.m_width);

         glBegin(GL_LINES);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);
            glVertex3f(p.m_pos1.x, p.m_pos1.y, p.m_pos1.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x, p.m_pos2.y, p.m_pos2.z);

         glEnd();
      }


      void RenderRectangle(const PolyPrimitive &p)
      {
         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);
         glLineWidth(p.m_width);

         glBegin(GL_LINE_LOOP);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);
            glVertex3f(p.m_pos1.x, p.m_pos1.y, p.m_pos1.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x, p.m_pos1.y, p.m_pos2.z);

            glColor4f(p.m_colour4.r, p.m_colour4.g, p.m_colour4.b, p.m_colour4.a);
            glVertex3f(p.m_pos2.x, p.m_pos2.y, p.m_pos2.z);

            glColor4f(p.m_colour3.r, p.m_colour3.g, p.m_colour3.b, p.m_colour3.a);
            glVertex3f(p.m_pos1.x, p.m_pos2.y, p.m_pos1.z);

         glEnd();
      }


      void RenderFilledRectangle(const PolyPrimitive &p)
      {
         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);

         glBegin(GL_QUADS);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);
            glVertex3f(p.m_pos1.x, p.m_pos1.y, p.m_pos1.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x, p.m_pos1.y, p.m_pos2.z);

            glColor4f(p.m_colour4.r, p.m_colour4.g, p.m_colour4.b, p.m_colour4.a);
            glVertex3f(p.m_pos2.x, p.m_pos2.y, p.m_pos2.z);

            glColor4f(p.m_colour3.r, p.m_colour3.g, p.m_colour3.b, p.m_colour3.a);
            glVertex3f(p.m_pos1.x, p.m_pos2.y, p.m_pos1.z);

         glEnd();
      }


      void RenderVector(const PolyPrimitive &p)
      {
         Vector3 normal = p.m_pos2 - p.m_pos1;
         normal.Normalise();

         Vector3 arrow1 = p.m_pos2 - normal * p.m_data1 + 
            Vector3(normal.y,-normal.x,normal.z)*p.m_data2;

         Vector3 arrow2 = p.m_pos2 - normal * p.m_data1 + 
            Vector3(-normal.y,normal.x,normal.z)*p.m_data2;

         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);
         glLineWidth(p.m_width);

         glBegin(GL_LINES);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);
            glVertex3f(p.m_pos1.x,p.m_pos1.y,p.m_pos1.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x,p.m_pos2.y,p.m_pos2.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(arrow1.x,arrow1.y,arrow1.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x,p.m_pos2.y,p.m_pos2.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(arrow2.x,arrow2.y,arrow2.z);

            glColor4f(p.m_colour2.r, p.m_colour2.g, p.m_colour2.b, p.m_colour2.a);
            glVertex3f(p.m_pos2.x,p.m_pos2.y,p.m_pos2.z);

         glEnd();
      }


      void RenderCircle(const PolyPrimitive &p)
      {
         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);
         glLineWidth(p.m_width);

         glBegin(GL_LINE_LOOP);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);

            for (float a = 0; a<3.14159265f*2.0f; a+=3.14159265f*2.0f/p.m_data1)
            {
               glVertex3f(
                  p.m_pos1.x + p.m_pos2.x * (float)cos(a), 
                  p.m_pos1.y + p.m_pos2.y * (float)sin(a), 
                  p.m_pos1.z);
            }

         glEnd();
      }


      void RenderFilledCircle(const PolyPrimitive &p)
      {
         if (p.m_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
         }
         else
         {
            glDisable(GL_BLEND);
         }

         glDisable(GL_TEXTURE_2D);
         glLineWidth(p.m_width);

         glBegin(GL_TRIANGLE_FAN);

            glColor4f(p.m_colour1.r, p.m_colour1.g, p.m_colour1.b, p.m_colour1.a);
            glVertex3f(p.m_pos1.x, p.m_pos1.y, p.m_pos1.z);

            for (float a = 0; a < PI * 2.0f; a += PI * 2.0f / p.m_data1)
            {
               glVertex3f(
                  p.m_pos1.x + p.m_pos2.x * (float)cos(a), 
                  p.m_pos1.y + p.m_pos2.y * (float)sin(a), 
                  p.m_pos1.z);
            }

            glVertex3f(
               p.m_pos1.x + p.m_pos2.x * (float)cos(0.0f), 
               p.m_pos1.y + p.m_pos2.y * (float)sin(0.0f), 
               p.m_pos1.z);

         glEnd();
      }


      void RenderPolygons()
      {
         for (fdword i = 0; i < polyPrimitiveCount; i++)
         {
            switch(polyPrimitives[i].m_type)
            {
            case PolyPrimitive::POLY_LINE:
               RenderLine(polyPrimitives[i]);
               break;

            case PolyPrimitive::POLY_VECTOR:
               RenderVector(polyPrimitives[i]);
               break;

            case PolyPrimitive::POLY_RECTANGLE:
               RenderRectangle(polyPrimitives[i]);
               break;

            case PolyPrimitive::POLY_CIRCLE:
               RenderCircle(polyPrimitives[i]);
               break;

            case PolyPrimitive::POLY_FILLED_RECTANGLE:
               RenderFilledRectangle(polyPrimitives[i]);
               break;

            case PolyPrimitive::POLY_FILLED_CIRCLE:
               RenderFilledCircle(polyPrimitives[i]);
               break;

            }
         }

         polyPrimitiveCount = 0;
      }


      void DrawLine(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c, 
         bool blend, 
         float width)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_LINE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = startPos;
         polyPrimitives[polyPrimitiveCount].m_pos2 = endPos;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitiveCount++;
      }


      void DrawLine(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c1, 
         const Colour &c2, 
         bool blend, 
         float width)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_LINE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = startPos;
         polyPrimitives[polyPrimitiveCount].m_pos2 = endPos;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c1;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c2;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitiveCount++;
      }


      void DrawVector(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c, 
         float arrowSize1, 
         float arrowSize2, 
         bool blend, 
         float width)
      {
         if(polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }
         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_VECTOR;
         polyPrimitives[polyPrimitiveCount].m_pos1 = startPos;
         polyPrimitives[polyPrimitiveCount].m_pos2 = endPos;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitives[polyPrimitiveCount].m_data1 = arrowSize1; 
         polyPrimitives[polyPrimitiveCount].m_data2 = arrowSize2;
         polyPrimitiveCount++;
      }


      void DrawVector(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c1, 
         const Colour &c2, 
         float arrowSize1, 
         float arrowSize2, 
         bool blend, 
         float width)
      {
         if(polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_VECTOR;
         polyPrimitives[polyPrimitiveCount].m_pos1 = startPos;
         polyPrimitives[polyPrimitiveCount].m_pos2 = endPos;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c1;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c2;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitives[polyPrimitiveCount].m_data1 = arrowSize1; 
         polyPrimitives[polyPrimitiveCount].m_data2 = arrowSize2;
         polyPrimitiveCount++;
      }


      void DrawCircle(
         const Vector3 &center, 
         float radius, 
         const Colour &c, 
         bool blend, 
         float width, 
         int segments)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_CIRCLE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = center;
         polyPrimitives[polyPrimitiveCount].m_pos2.Set(radius,radius,0);
         polyPrimitives[polyPrimitiveCount].m_colour1 = c;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitives[polyPrimitiveCount].m_data1 = float(segments); 
         polyPrimitiveCount++;
      }


      void DrawFilledCircle(
         const Vector3 &center, 
         float radius, 
         const Colour &c, 
         bool blend, 
         int segments)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_FILLED_CIRCLE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = center;
         polyPrimitives[polyPrimitiveCount].m_pos2.Set(radius,radius,0);
         polyPrimitives[polyPrimitiveCount].m_colour1 = c;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_data1 = float(segments); 
         polyPrimitiveCount++;
      }


      void DrawRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c, 
         bool blend, 
         float width)
      {
         DrawRectangle(corner1, corner2, c, c, c, c, blend, width);
      }


      void DrawRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c1, 
         const Colour &c2, 
         const Colour &c3, 
         const Colour &c4, 
         bool blend, 
         float width)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }

         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_RECTANGLE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = corner1;
         polyPrimitives[polyPrimitiveCount].m_pos2 = corner2;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c1;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c2;
         polyPrimitives[polyPrimitiveCount].m_colour3 = c3;
         polyPrimitives[polyPrimitiveCount].m_colour4 = c4;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitives[polyPrimitiveCount].m_width = width;
         polyPrimitiveCount++;
      }

      void DrawFilledRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c, 
         bool blend)
      {
         DrawFilledRectangle(corner1, corner2, c, c, c, c, blend);
      }


      void DrawFilledRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c1, 
         const Colour &c2, 
         const Colour &c3, 
         const Colour &c4, 
         bool blend)
      {
         if (polyPrimitiveCount >= MAX_PRIMITIVES)
         {
            return;
         }
         polyPrimitives[polyPrimitiveCount].m_type = PolyPrimitive::POLY_FILLED_RECTANGLE;
         polyPrimitives[polyPrimitiveCount].m_pos1 = corner1;
         polyPrimitives[polyPrimitiveCount].m_pos2 = corner2;
         polyPrimitives[polyPrimitiveCount].m_colour1 = c1;
         polyPrimitives[polyPrimitiveCount].m_colour2 = c2;
         polyPrimitives[polyPrimitiveCount].m_colour3 = c3;
         polyPrimitives[polyPrimitiveCount].m_colour4 = c4;
         polyPrimitives[polyPrimitiveCount].m_blend = blend;
         polyPrimitiveCount++;
      }

   }  // end namespace GF1


//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
