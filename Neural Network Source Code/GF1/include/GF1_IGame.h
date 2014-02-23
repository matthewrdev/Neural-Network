#ifndef GF1_IGAME_H
#define GF1_IGAME_H
//****************************************************************************
//**
//**    GF1_IGame.h
//**    Game Interface
//**    This interface is provided for the user to override to create his own
//**    game.  The user must implement the Logic() and Render() functions.
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include <GF1_Def.h>
#include <GF1_Input.h>

   namespace GF1
   {

      // =====================================================================
      // IGame
      // =====================================================================
      // Interface class representing the game.
      // =====================================================================
      class GF1_API IGame
      {
      public:
         virtual ~IGame();
            // The Game destructor to release all allocated resources.
            // Note: Interface classes must have a virtual non-inline 
            //       destructor and all other members pure virtual.

         virtual bool IsOver() const = 0;
            // Returns false until a condition occurs which causes the game to
            // terminate, such as the user quitting.

         virtual void GetCamera(
            float &left,   float &right, 
            float &bottom, float &top,
            float &zNear,  float &zFar) const = 0;
            // This function specifies what rectangular section of the world 
            // is visible through the render window.  
            // With 2D games it is best to match pixel size to texel size 
            // where possible so if the screen width is 600 pixels, the 
            // visible world width should also be 600 pixels.  
            // For world coordinates it is probably a good idea to follow 
            // standard mathematical convention and make:
            //    X Positive => Right
            //    Y Positive => Up
            // E.g.
            // left     = -320,  right = +320, 
            // bottom   = -240,  top = +240, 
            // zNear    = +280,  zFar = -280

         virtual void Logic() = 0;
            // Called periodically, this function updates the game state over 
            // time based on the previous game state and gameplay logic.  
            // Override this function and insert the client gameplay logic.
            // into it.

         virtual void Render() = 0;
            // Called perioidcally, this function Renders the current game 
            // state.

         virtual void OnMouseEvent(
            MouseButton button, 
            MouseEvent event,
            int xPosWindow, int yPosWindow,
            float xPosWorld, float yPosWorld) = 0;
            // Called when a mouse event occurs.  See Input.h for more 
            // details.
            //
            // button
            //    If the event was a button press, release or double click
            //    this contains the id of the button that initiated the event.
            // event
            //    The type of event being received.
            // xPosWindow, yPosWindow
            //    The render window coorindates of the mouse.
            // xPosWorld, yPosWorld
            //    The world coordinates of the mouse.
      };

   }  // end namespace GF1


//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
