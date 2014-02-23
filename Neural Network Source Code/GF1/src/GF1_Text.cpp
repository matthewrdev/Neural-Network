//****************************************************************************
//**
//**    GF1_Text.cpp
//**
//**    Copyright (c) 2007 QANTM
//**
//**    Author:  Kojack
//**    Created: 06/06/2007
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Text.h"
#include "GF1_Sprite.h"

   namespace GF1
   {
      void print(Sprite *sprite, const Vector3 &start_position, const char *text, const Colour &colour)
      {
         Vector3 pos = start_position;
         int length = strlen(text);
         sprite->SetColour(colour);
         float width = sprite->GetFrameWidth() * sprite->GetScaleX();
         float height = sprite->GetFrameHeight() * sprite->GetScaleY();

         for(int i = 0; i < length; i++)
         {
            switch(text[i])
            {
            case 13:
               break;
            case 10:
               pos.x = start_position.x;
               pos.y -= height;
               break;
            default:
               sprite->SetCurrentFrame(text[i]);
               sprite->SetPosition(pos+Vector3(width*0.5,-height*0.5,0));
               sprite->Render();
               pos.x += width;
            }
         }
      }

   }  // end namespace GF1



//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
