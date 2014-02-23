#ifndef GF1_H
#define GF1_H
//****************************************************************************
//**
//**    GF1.h
//**    Main Interface
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include <GF1_Application.h>
#include <GF1_IGame.h>
#include <GF1_Input.h>
#include <GF1_Math.h>
#include <GF1_Vector3.h>
#include <GF1_Colour.h>
#include <GF1_Graphics.h>
#include <GF1_Sprite.h>
#include <GF1_Sound.h>
#include <GF1_Music.h>
#include <GF1_Types.h>
#include <GF1_Text.h>

   namespace GF1
   {
      // ---------------------------------------------------------------------------
      // GetVersion
      // ---------------------------------------------------------------------------
      // Obtain the version of the game framework that is being used in a string
      // format.
      // ---------------------------------------------------------------------------
      GF1_API const char *GetVersion();

	  void GF1_API ReleaseAllTexture();

   }


//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
