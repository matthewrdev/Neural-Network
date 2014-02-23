#ifndef GF1_TEXT_H
#define GF1_TEXT_H
//****************************************************************************
//**
//**    GF1_Text.h
//**
//**    Copyright (c) 2007 QANTM
//**
//**    Author:  Kojack
//**    Created: 06/06/2007
//**
//****************************************************************************
#include <GF1_Def.h>
#include <GF1_Types.h>
#include <GF1_Colour.h>
#include <GF1_Vector3.h>

   namespace GF1
   {
      class Sprite;

      GF1_API void print(Sprite *sprite, const Vector3 &start_position, const char *text, const Colour &colour = Colour::WHITE);
      
   }  // end namespace GF1


//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
