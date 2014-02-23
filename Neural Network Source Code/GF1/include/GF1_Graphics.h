#ifndef GF1_GRAPHICS_H
#define GF1_GRAPHICS_H
//****************************************************************************
//**
//**    GF1_Graphics.h
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Greg Quincey
//**    Created: 28/11/2003
//**
//****************************************************************************
#include <GF1_Def.h>

   namespace GF1
   {
      class Colour;
      class Vector3;

      // ---------------------------------------------------------------------
      // GetMaxPrimitives
      // ---------------------------------------------------------------------
      // Obtain the maximum number of primitives that may be drawn in a single
      // frame.  Any primitive render attempts in excess of this number will 
      // not be drawn.
      //
      // If this number is insufficient, post a message on the bulletin board
      // and we may increase it or add a method to set it.
      // ---------------------------------------------------------------------
      int GetMaxPrimitives();


      // ---------------------------------------------------------------------
      // DrawLine
      // ---------------------------------------------------------------------
      // Draw a line between 2 points. The line can have a single colour,
      // or a different colour at each end.
      //
      // startPos
      //    Coordinate of the line's start.
      // endPos
      //    Coordinate of the line's end.
      // c
      //    Single colour for the entire line.
      // c1
      //    Start colour.
      // c2
      //    End colour.
      // blend
      //    Enables alpha blending.
      // width
      //    Specifies the width of the line.
      // ---------------------------------------------------------------------
      GF1_API void DrawLine(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c, 
         bool blend = false, 
         float width = 1.0f);

      GF1_API void DrawLine(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c1, 
         const Colour &c2, 
         bool blend = false, 
         float width = 1.0f);


      // ---------------------------------------------------------------------
      // DrawVector
      // ---------------------------------------------------------------------
      // Draw a vector between 2 points. The vector can have a single colour,
      // or a different colour at each end. Arrow heads are drawn at endPos.
      //
      // startPos
      //    Coordinate of the vector's start.
      // endPos
      //    Coordinate of the vector's end.
      // c
      //    Single colour for the entire vector.
      // c1
      //    Start colour.
      // c2
      //    End colour.
      // arrowSize1
      //    Length of the arrow head along the vector.
      // arrowSize2
      //    length of the arrow head perpendicular to the vector.
      // blend
      //    Enables alpha blending.
      // width
      //    Specifies the width of the vector.
      // ---------------------------------------------------------------------
      GF1_API void DrawVector(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c, 
         float arrowSize1, 
         float arrowSize2, 
         bool blend = false, 
         float width = 1.0f);

      GF1_API void DrawVector(
         const Vector3 &startPos, 
         const Vector3 &endPos, 
         const Colour &c1, 
         const Colour &c2, 
         float arrowSize1, 
         float arrowSize2, 
         bool blend = false, 
         float width = 1.0f);


      // ---------------------------------------------------------------------
      // DrawCircle
      // DrawFilledCircle
      // ---------------------------------------------------------------------
      // Draw a circle, either as wireframe or filled.
      //
      // startPos
      //    Coordinate of the circle's center.
      // radius
      //    Radius of the circle.
      // c
      //    Colour of the circle.
      // blend
      //    Enables alpha blending.
      // width
      //    Specifies the width of the circle's wireframe lines.
      // segments
      //    Number of line segments to use to draw the circle. More segments
      //    results in a rounder circle.
      // ---------------------------------------------------------------------
      GF1_API void DrawCircle(
         const Vector3 &startPos, 
         float radius, 
         const Colour &c, 
         bool blend = false, 
         float width = 1.0f, 
         int segments = 32);

      GF1_API void DrawFilledCircle(
         const Vector3 &startPos, 
         float radius, 
         const Colour &c, 
         bool blend = false, 
         int segments = 32);


      // ---------------------------------------------------------------------
      // DrawRectangle
      // DrawFilledRectangle
      // ---------------------------------------------------------------------
      // Draws a rectangle, either as a wireframe or filled. Colour can be
      // controlled at each corner or a single colour used for all four 
      // corners.
      //
      // corner1
      //    One corner of the rectangle.
      // corner2
      //    opposite corner of the rectangle.
      // c
      //    Colour of the rectangle.
      // c1, c2, c3, c4
      //    Colour of each corner.
      // blend
      //    Enables alpha blending.
      // width
      //    Specifies the width of the rectangle's wireframe lines.
      // ---------------------------------------------------------------------
      GF1_API void DrawRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c, 
         bool blend = false, 
         float width = 1.0f);

      GF1_API void DrawFilledRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c, 
         bool blend = false);

      GF1_API void DrawRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c1, 
         const Colour &c2, 
         const Colour &c3, 
         const Colour &c4, 
         bool blend = false, 
         float width = 1.0f);

      GF1_API void DrawFilledRectangle(
         const Vector3 &corner1, 
         const Vector3 &corner2, 
         const Colour &c1, 
         const Colour &c2, 
         const Colour &c3, 
         const Colour &c4, 
         bool blend = false);

   }

//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
