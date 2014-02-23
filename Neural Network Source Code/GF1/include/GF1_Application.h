#ifndef GF1_APPLICATION_H
#define GF1_APPLICATION_H
//****************************************************************************
//**
//**    GF1_Application.h
//**    Application Module
//**    Contains main application class with that manages calling game control 
//**    functions such as Logic() and Render() at appropriate times.
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//**    Dale Freya   25/11/2003
//**        *  Added bieGF1APIVersion to the Application constructor to 
//             guarantee compatibility between GF1 headers and DLLs.
//****************************************************************************
#include <GF1_Def.h>

   namespace GF1
   {
      class  IGame;
         // Game Interface.

      struct ApplicationImpl;

      // =====================================================================
      // Application
      // =====================================================================
      // Class controlling game function timing, I.e. logic and rendering.
      // =====================================================================
      class GF1_API Application
      {
      public:
         // ---------------------------------------------------------------------------
         // Constructor
         // ---------------------------------------------------------------------------
         // The Application constructor.
         //
         // bieGF1APIVersion
         // This will ensure that your gf1 dlls are the same version as your gf1 header 
         // files.  Should be GF1_API_VERSION.
         // ---------------------------------------------------------------------------
         Application(const char *bieGF1APIVersion = GF1_API_VERSION);

         virtual ~Application();
            // The Application destructor to release all allocated resources.
            // Note: Base class Destructor must be virtual for destructors to 
            //       work with inheritance.

         virtual int GetLogicFrequency() const;
            // Obtain the number of calls to IGame::Logic() per second.

         virtual int GetLogicInterval() const;
            // Obtain the number of milliseconds between calls to IGame::Logic()

         virtual void Run(IGame &game, bool fullscreen = true);
            // Runs game calling IGame::Logic() and IGame::Render() at 
            // appropriate times until IGame::IsOver() returns true.
            //
            // game
            //    The game to run.

         virtual void SetLogicFreqency(int logicFrequency);
            // Set the number of calls to IGame::Logic() per second.  If 
            // IGame::Logic() and IGame::Render() cannot complete within the 
            // time required to maintain the desired frequency, the game 
            // speed and frame rate will drop.
            //
            // logicFrequency
            //    The number of calls to IGame::Logic() in one second.
            //    PRE:  0 < logicFrequency

         virtual void SetRenderWindowClientSize(int width, int height);
            // Set the window dimensions of the client area of the render 
            // window
            //
            // width, height
            //    The width and height of the client area of the render 
            //    window.

         virtual int GetRenderWindowClientWidth() const;
            // Returns the width of the client render window

         virtual int GetRenderWindowClientHeight() const;
            // Returns the height of the client render window

         virtual float WindowClientToWorldX(int windowClientX);
            // Convert Window Client X positon to a world X position

         virtual float WindowClientToWorldY(int windowClientY);
            // Convert Window Client Y positon to a world Y position

      private:
         ApplicationImpl *m_impl;
      };

   }  // end namespace GF1


//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
