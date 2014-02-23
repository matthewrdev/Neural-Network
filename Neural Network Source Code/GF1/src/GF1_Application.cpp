//****************************************************************************
//**
//**    GF1_Application.cpp
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Application.h"
#include "GF1_IGame.h"
#include "GF1_GraphicsInternal.h"
#include "GF1_InputInternal.h"
#include "il/il.h"
#include "il/ilu.h"
#include <iostream>

#include "GF1_MemoryLeak.h"
using std::cout;
using std::endl;
using std::cerr;


   namespace GF1
   {

      bool g_fullscreen = true;
      struct ApplicationImpl
      {
         int m_logicFrequency;
         int m_logicIntervalMS;
         unsigned int m_nextLogicMS;
         int m_width, m_height;

         // world dimensions
         float m_left, m_right, m_world_width;
         float m_bottom, m_top, m_world_height;
         float m_zNear, m_zFar, m_world_depth;
      };

      namespace
      {
         HGLRC hRC;  // Rendering Context
         HDC hDC;		// GDI Device Context
         Application *g_app  = NULL;
         IGame       *g_game = NULL;

	      // This Will Be Called Right After The GL Window Is Created
         GLvoid InitGL()
         {
		      // This Will Clear The Background Color To Black
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            // Enables Clearing Of The Depth Buffer
            glClearDepth(1.0);							

            // The Type Of Depth Test To Do
            glDepthFunc(GL_LEQUAL);

				// Enables Depth Testing
            glEnable(GL_DEPTH_TEST);

            // Enables Smooth Color Shading
            glShadeModel(GL_SMOOTH);

            // To mask our sprites we can use the alpha channel of the tga texture.
            // We set up alpha testing so pixels are not drawn if their corresponding alpha
            // channel value is less than 0.1.
            // If you want to change the blending or alpha test state at any point 
            // always change it back to these values.
            // glAlphaFunc(GL_GREATER,0.005f);
            glAlphaFunc(GL_GREATER,0.005f);
         }

         GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
         {
            // Prevent A Divide By Zero If The Window Is Too Small
            Height = (Height == 0) ? 1 : Height;

            // Reset The Current Viewport
            glViewport(0, 0, Width, Height);
         }


         LRESULT CALLBACK WndProc(	
            HWND hWnd,
            UINT message,
            WPARAM wParam,
            LPARAM lParam)
         {
            // Used Later On To Get The Size Of The Window
            RECT	Screen;
            GLuint	PixelFormat;
            static	PIXELFORMATDESCRIPTOR pfd=
            {
               sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
                  1,									   // Version Number (?)
                  PFD_DRAW_TO_WINDOW |				// Format Must Support Window
                  PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
                  PFD_DOUBLEBUFFER,					// Must Support Double Buffering
                  PFD_TYPE_RGBA,						// Request An RGBA Format
                  16,									// Select A 16Bit Color Depth
                  0, 0, 0, 0, 0, 0,					// Color Bits Ignored (?)
                  0,									   // No Alpha Buffer
                  0,									   // Shift Bit Ignored (?)
                  0,								   	// No Accumulation Buffer
                  0, 0, 0, 0,							// Accumulation Bits Ignored (?)
                  16,									// 16Bit Z-Buffer (Depth Buffer)  
                  0,									   // No Stencil Buffer
                  0,									   // No Auxiliary Buffer (?)
                  PFD_MAIN_PLANE,					// Main Drawing Layer
                  0,									   // Reserved (?)
                  0, 0, 0								// Layer Masks Ignored (?)
            };

            // Tells Windows We Want To Check The Message
            switch (message)						
            {
            case WM_CREATE:
               // Gets A Device Context For The Window
               hDC = GetDC(hWnd);				

               // Finds The Closest Match To The Pixel Format We Set Above
               PixelFormat = ChoosePixelFormat(hDC, &pfd);		

               if (!PixelFormat)
               {
                  MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
                  PostQuitMessage(0);			// This Sends A 'Message' Telling The Program To Quit
                  break;						// Prevents The Rest Of The Code From Running
               }

               if(!SetPixelFormat(hDC,PixelFormat,&pfd))
               {
                  MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
                  PostQuitMessage(0);
                  break;
               }

               hRC = wglCreateContext(hDC);
               if(!hRC)
               {
                  MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
                  PostQuitMessage(0);
                  break;
               }

               if(!wglMakeCurrent(hDC, hRC))
               {
                  MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
                  PostQuitMessage(0);
                  break;
               }

               GetClientRect(hWnd, &Screen);
               InitGL();
               break;

            case WM_DESTROY:
            case WM_CLOSE:
               ChangeDisplaySettings(NULL, 0);

               wglMakeCurrent(hDC,NULL);
               wglDeleteContext(hRC);
               ReleaseDC(hWnd,hDC);

               PostQuitMessage(0);
               break;

            case WM_SIZE:
               ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
               break;

            case WM_MOUSEMOVE:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_NONE, MOUSE_EVENT_MOVE,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_LBUTTONDBLCLK:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_LEFT, 
                     MOUSE_EVENT_BUTTON_DOUBLE_CLICK,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_LBUTTONDOWN:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_LEFT, 
                     MOUSE_EVENT_BUTTON_DOWN,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_LBUTTONUP:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_LEFT, 
                     MOUSE_EVENT_BUTTON_UP,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;
               
            case WM_MBUTTONDBLCLK:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_MIDDLE, 
                     MOUSE_EVENT_BUTTON_DOUBLE_CLICK,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_MBUTTONDOWN:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_MIDDLE, 
                     MOUSE_EVENT_BUTTON_DOWN,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_MBUTTONUP:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_MIDDLE, 
                     MOUSE_EVENT_BUTTON_UP,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_RBUTTONDBLCLK:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_RIGHT, 
                     MOUSE_EVENT_BUTTON_DOUBLE_CLICK,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_RBUTTONDOWN:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_RIGHT, 
                     MOUSE_EVENT_BUTTON_DOWN,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_RBUTTONUP:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_RIGHT, 
                     MOUSE_EVENT_BUTTON_UP,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            case WM_MOUSEHOVER:
               if (g_game != NULL)
               {
                  WORD xPosScreen = LOWORD(lParam);
                  WORD yPosScreen = HIWORD(lParam);
                  float xPosWorld = g_app->WindowClientToWorldX(xPosScreen);
                  float yPosWorld = g_app->WindowClientToWorldY(yPosScreen);

                  g_game->OnMouseEvent(MOUSE_BUTTON_NONE, 
                     MOUSE_EVENT_HOVER,
                     xPosScreen, yPosScreen, xPosWorld, yPosWorld);
               }
               break;

            default:
               return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            return (0);
         }


      void SetupCamera(IGame &game, ApplicationImpl *m_impl)
      {
         // Set up the camera
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();

         float left, right, bottom, top, zNear, zFar;
         game.GetCamera(left, right, bottom, top, zNear, zFar);

         m_impl->m_left   = left;
         m_impl->m_right  = right;
         m_impl->m_world_width = right - left;
         m_impl->m_bottom = bottom;
         m_impl->m_top    = top;
         m_impl->m_world_height = top - bottom;
         m_impl->m_zNear  = zNear;
         m_impl->m_zFar   = zFar;
         m_impl->m_world_depth = zNear - zFar;

         glOrtho(left, right, bottom, top, zNear, zFar);
         // Set up the model matrix
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
      }

      }  // end namespace



      Application::Application(const char *bieGF1APIVersion)
      {
         if (strcmp(bieGF1APIVersion, GF1_API_VERSION) != 0)
         {
            cerr << "BIE GF1 Header/DLL version mismatch" << endl;
            cerr << "Header Version: " << bieGF1APIVersion << endl;
            cerr << "DLL Version: " << GF1_API_VERSION << endl;
            abort();
         }

		

         m_impl = new ApplicationImpl;

         // default logic runs at 30 logic calls per second
         SetLogicFreqency(30);

         // default render window client area is 600 x 600
         SetRenderWindowClientSize(600, 600);

         // Intialise the sound system
         FSOUND_Init(44100, 32, 0);

         // Initialize Devil Image Library
         ilInit();
         iluInit();

         // Enable the conversion of the origin of all images to the top left
         // If this is not enabled .tga files saved in photoshop appear upside down
         ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
         ilEnable(IL_ORIGIN_SET);
         ilSetInteger(IL_KEEP_DXTC_DATA,IL_TRUE);

         // Initialise our key input system
         InitKeys();
      }


      Application::~Application()
      {
         ilShutDown();

         FSOUND_Close();

         delete m_impl;
      }


      int Application::GetLogicFrequency() const
      {
         return m_impl->m_logicFrequency;
      }


      int Application::GetLogicInterval() const
      {
         return m_impl->m_logicIntervalMS;
      }


      void Application::Run(IGame &game, bool fullscreen)
      {
         MSG      msg;     // Windows Message Structure
         WNDCLASS	wc;      // Windows Class Structure Used To Set Up The Type Of Window
         HWND     hWnd;    // Storage For Window Handle

         wc.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
         wc.lpfnWndProc    = (WNDPROC) WndProc;
         wc.cbClsExtra     = 0;
         wc.cbWndExtra		= 0;
         wc.hInstance      = NULL; // hInstance;
         wc.hIcon          = NULL;
         wc.hCursor        = NULL;
         wc.hbrBackground  = NULL;
         wc.lpszMenuName   = NULL;
         wc.lpszClassName  = "GF1_WinClass";

         if(!RegisterClass(&wc))
         {
            MessageBox(0,"Failed To Register The Window Class.","Error",MB_OK|MB_ICONERROR);
            return;
         }

		 // WesC - Default to windowed in debug mode.
#ifndef _DEBUG
		 // Ask The User Which Screen Mode They Prefer
//		if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?"
//			,MB_YESNO|MB_ICONQUESTION) == IDNO)		
			g_fullscreen = fullscreen;							// Windowed Mode		
#else
		 g_fullscreen = false;
#endif
		
		DWORD style;
		
		
		RECT clientRect;
		clientRect.left = 0;
		clientRect.right = m_impl->m_width;
		clientRect.top = 0;
		clientRect.bottom = m_impl->m_height;
		
		
		
		//if (g_fullscreen)
		//{
			//style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;		
		//}
		//else
		//{
			style = WS_OVERLAPPED;
			AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);
		//}

		int width = clientRect.right - clientRect.left;
		int height = clientRect.bottom - clientRect.top;





         hWnd = CreateWindow(
            "GF1_WinClass",
            "Game Framework 1",		// Title Appearing At The Top Of The Window

			// WesC - Changed this based on fullscreen or window selection, see the MessageBox
			// call up above
            /*WS_POPUP |
            WS_CLIPCHILDREN |
            WS_CLIPSIBLINGS,*/
			style,

            0, 0,                      // The Position Of The Window On The Screen
            width, height,

            NULL,
            NULL,
            NULL, // hInstance,
            NULL);

		 

         if(!hWnd)
         {
            MessageBox(0,"Window Creation Error.","Error",MB_OK|MB_ICONERROR);
            return;
         }

		 if (g_fullscreen)
		 {
//#ifndef _DEBUG
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, '\0', sizeof(DEVMODE));
			dmScreenSettings.dmSize = sizeof(DEVMODE);
			dmScreenSettings.dmPelsWidth        = m_impl->m_width;
			dmScreenSettings.dmPelsHeight       = m_impl->m_height;
			dmScreenSettings.dmFields           = DM_PELSWIDTH | DM_PELSHEIGHT;

			// TODO: Check result and throw exception on failure
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);			
		 }
//#endif

         ShowWindow(hWnd, SW_SHOW);
         UpdateWindow(hWnd);
         SetFocus(hWnd);
         SetCursor(LoadCursor(NULL, IDC_ARROW));

         // The game is launched.
         m_impl->m_nextLogicMS = timeGetTime() + m_impl->m_logicFrequency;

         // Most basic game loop involves running Logic() and Render() coupled.
         // 

         // Need to call a setup camera before any window events are processed 
         // as we could get called back with a mouse event or similar and
         // need to convert from screen to world coordinates.
         SetupCamera(game, m_impl);

         for (;;)
         {
            if (game.IsOver())
            {
               SendMessage(hWnd,WM_CLOSE,0,0);
            }

            // Process All Messages
            g_app = this;
            g_game = &game;

            while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
            {
               if (GetMessage(&msg, NULL, 0, 0))
               {
                  TranslateMessage(&msg);
                  DispatchMessage(&msg);
               }
               else
               {
                  return;
               }
            }

            g_app = NULL;
            g_game = NULL;

            // Poll keys once per frame to determine when keys are hit and 
            // lifted
            PollKeys();

            // Run one frame of logic coupled to one frame of rendering.
            game.Logic();

		      // Clear The Screen And The Depth Buffer
	         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            SetupCamera(game, m_impl);

            game.Render();

            RenderPolygons();

            SwapBuffers(hDC);

            unsigned int currentTimeMS = timeGetTime();


			// This has been changed because it results in a GIGANTIC pause in the application if you are in debugger.
			// I have taken out the addition of the delta between this frame and the last frame because it is bad ju ju
			// for the reason stated above.
			// Matt Robbins.
            m_impl->m_nextLogicMS = currentTimeMS + m_impl->m_logicIntervalMS;

			/*m_impl->m_nextLogicMS = currentTimeMS + m_impl->m_logicIntervalMS - 
               (m_impl->m_nextLogicMS - currentTimeMS);*/
         }
      }


      void Application::SetLogicFreqency(int logicFrequency)
      {
         assert(0 < logicFrequency);
         m_impl->m_logicIntervalMS = static_cast<int>(1.0f / logicFrequency * 1000.0f);
         m_impl->m_logicFrequency = logicFrequency;
      }


      void Application::SetRenderWindowClientSize(int width, int height)
      {
         m_impl->m_width = width;
         m_impl->m_height = height;
      }


      int Application::GetRenderWindowClientWidth() const
      {
         return m_impl->m_width;
      }


      int Application::GetRenderWindowClientHeight() const
      {
         return m_impl->m_height;
      }

      float Application::WindowClientToWorldX(int windowClientX)
      {
         // Calculate the x screen pos from 0.0 - 1.0
         float normalisedScreenPos = windowClientX / (float)m_impl->m_width;
         float xPosWorld = (normalisedScreenPos * m_impl->m_world_width) + m_impl->m_left;
         return xPosWorld;
      }

      float Application::WindowClientToWorldY(int windowClientY)
      {
         float normalisedScreenPos = windowClientY / (float)m_impl->m_height;
         float yPosWorld = -((normalisedScreenPos * m_impl->m_world_height) + m_impl->m_bottom);
         return yPosWorld;
      }


   }  // end namespace GF1


//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
