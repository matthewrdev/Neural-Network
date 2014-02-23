#ifndef GF1_INPUT_H
#define GF1_INPUT_H
//****************************************************************************
//**
//**    GF1_Input.h
//**    Input Module
//**    Contains Functionality for obtaining user input.
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include <GF1_Def.h>

   namespace GF1
   {
      enum Key
      {
         KEY_ESCAPE,

         KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, 
         KEY_F9, KEY_F10, KEY_F11, KEY_F12,

         KEY_PRINT_SCREEN, KEY_SCROLL, 
         
         // KEY_PAUSE
         // Left out deliberately. Doesn't work like other keys.

         KEY_APOSTROPHE, KEY_TAB, KEY_CAPS, 
         KEY_LSHIFT, KEY_LCONTROL, KEY_LALT, 
         KEY_SPACE, 
         KEY_RSHIFT, KEY_RCONTROL, KEY_RALT, 
         KEY_SUBTRACT, KEY_EQUALS, KEY_BACKSLASH, KEY_BACKSPACE, KEY_ENTER, 

         KEY_LSQUARE_BRACKET, KEY_RSQUARE_BRACKET, 
         KEY_SEMICOLON, KEY_QUOTE,
         KEY_COMMA, KEY_FULLSTOP, KEY_FORWARD_SLASH,

         KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,

         KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
         KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
         KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

         KEY_INSERT, KEY_HOME, KEY_PAGE_UP, 
         KEY_DELETE, KEY_END, KEY_PAGE_DOWN,

         KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN,

         KEY_NUM_LOCK, 
         KEY_NUM_DIVIDE, KEY_NUM_MULTIPLY, KEY_NUM_MINUS, KEY_NUM_ADD,
         KEY_NUM_1, KEY_NUM_2, KEY_NUM_3,
         KEY_NUM_4, KEY_NUM_5, KEY_NUM_6,
         KEY_NUM_7, KEY_NUM_8, KEY_NUM_9,
         KEY_NUM_0, KEY_NUM_DECIMAL,
         KEY_NUM_CLEAR /* 5 on the Num Pad when Num Lock not on */,

         KEY_COUNT,  // Not an actual key, tells how many keys in the enum
         KEY_INVALID = KEY_COUNT,
      };
         // Standard Keyboard Only
         // Windows Keys Not Included

      // ---------------------------------------------------------------------
      // IsKeyDown
      // ---------------------------------------------------------------------
      // Determines whether a key is up or down at the time the function is 
      // called based on one of the Key enumerations above.
      //
      // key
      //    Specifies the key we wish to check.
      //
      // Example
      //    if (IsKeyDown(KEY_LEFT))
      //       xPos -= 1.0f;
      // ---------------------------------------------------------------------
      GF1_API bool IsKeyDown(int key);


      // ---------------------------------------------------------------------
      // IsKeyHit, IsKeyLifted
      // ---------------------------------------------------------------------
      // Determines whether a key has been hit or lifted this logic frame.  
      // Only signals true when the key is first hit or lifted, not while it 
      // is held down or left up.
      //
      // key
      //    Specifies the key we wish to check.
      //
      // Example
      //    if (IsKeyHit(KEY_LEFT))
      //       xPos -= 1.0f;
      // ---------------------------------------------------------------------
      GF1_API bool IsKeyHit(int key);
      GF1_API bool IsKeyLifted(int key);


      // ---------------------------------------------------------------------
      // Key Names
      // ---------------------------------------------------------------------
      // The following functions KeyToString and StringToKey convert between
      // string and enum representations of each key.  The following chart
      // shows the accepted string representations of all keys in the same
      // order that they appear in the enum.
      // ---------------------------------------------------------------------
      // "Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", 
      // "F11", "F12", "PrintScreen", "Scroll", "`", "Tab", "CapsLock", 
      // "LShift", "LCtrl", "LAlt", "Space", "RShift", "RCtrl", "RAlt", "-",
      // "=", "\\", "Backspace", "Enter", "[", "]", ";", "'", ",", ".", "/"
      // "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D",
      // "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
      // "S", "T", "U", "V", "W", "X", "Y", "Z", "Insert", "Home", "PageUp", 
      // "Delete", "End", "Page Down", "Left", "Up", "Right", "Down", 
      // "NumLock", "Num/", "Num*", "Num-", "Num+", "Num1", "Num2", "Num3", 
      // "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Num.", 
      // "NumClear"
      // ---------------------------------------------------------------------

      // ---------------------------------------------------------------------
      // KeyToString
      // ---------------------------------------------------------------------
      // Converts a key into its string representation.
      //
      // key
      //    The key to convert.
      // 
      // E.g.
      //    KEY_A is converted to "A"
      //    KEY_F1 is converted to "F1"
      //    KEY_LSQUARE_BRACKET is converted to "["
      // ---------------------------------------------------------------------
      GF1_API const char *KeyToString(int key);


      // ---------------------------------------------------------------------
      // StringToKey
      // ---------------------------------------------------------------------
      // Converts a string into a key enumeration.  Performs a case 
      // insensitive comparision.  Strings that do not match keys are returned
      // as KEY_INVALID.
      //
      // PERFORMANCE WARNING
      // This function performs a linear search through the each key string 
      // looking for a match.
      //
      // s
      //    The string to convert.
      // 
      // E.g.
      //    "A" is converted to KEY_A
      //    "F1" is converted to KEY_F1
      //    "[" is converted to KEY_LSQUARE_BRACKET
      // ---------------------------------------------------------------------
      GF1_API int StringToKey(const char *s);


      // ---------------------------------------------------------------------
      // MouseButton
      // ---------------------------------------------------------------------
      // This enumeration identifies the standard mouse buttons and is used in
      // the IGame::OnMouseEvent mouse event handler.
      // ---------------------------------------------------------------------
      enum MouseButton
      {
         MOUSE_BUTTON_NONE,
         MOUSE_BUTTON_LEFT,
         MOUSE_BUTTON_MIDDLE,
         MOUSE_BUTTON_RIGHT
      };


      // ---------------------------------------------------------------------
      // MouseEvent
      // ---------------------------------------------------------------------
      // This enumeration captures the types of mouse events that are 
      // possible.
      // ---------------------------------------------------------------------
      enum MouseEvent
      {
         MOUSE_EVENT_MOVE,
         MOUSE_EVENT_BUTTON_DOWN,
         MOUSE_EVENT_BUTTON_UP,

         // Dale Freya 28/11/03:
         // Mouse Double Click Fixed for release 1.6
         // Had to add double click style to the main window.
         MOUSE_EVENT_BUTTON_DOUBLE_CLICK, 

         // Dale Freya 28/11/03: 
         // Mouse Hover is not working.  It needs more work.  Let me know on 
         // the forum if you think this would be useful.
         MOUSE_EVENT_HOVER 
      };


      // ---------------------------------------------------------------------
      // DefaultCursorIsEnabled
      // ---------------------------------------------------------------------
      // Determine whether or not the mouse cursor is enabled.
      // ---------------------------------------------------------------------
      GF1_API bool DefaultCursorIsEnabled();


      // ---------------------------------------------------------------------
      // DefaultCursorEnable
      // ---------------------------------------------------------------------
      // Enable or disable the default cursor.
      //
      // enable
      //    true if you want to enable otherwise false.
      // ---------------------------------------------------------------------
      GF1_API void DefaultCursorEnable(bool enable);

   }  // end namespace GF1



//****************************************************************************
//**
//**    END INTERFACE
//**
//****************************************************************************
#endif
