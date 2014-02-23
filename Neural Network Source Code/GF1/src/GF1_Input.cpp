//****************************************************************************
//**
//**    GF1_input.cpp
//**
//**    Copyright (c) 2003 QANTM CMC Australia
//**
//**    Author:  Dale Freya
//**    Created: 21/09/2003
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Input.h"


   namespace GF1
   {

      namespace
      {
         const SHORT KEY_DOWN_MASK = (SHORT)0x8000U;

         struct KeyData
         {
            int virtualKey;
            const char *stringRep;
         };

         const KeyData virtualKeyMapping[] = 
         {
            { VK_ESCAPE,   "Esc"       }, // KEY_ESCAPE

            { VK_F1,       "F1"        }, // KEY_F1
            { VK_F2,       "F2"        }, // KEY_F2
            { VK_F3,       "F3"        }, // KEY_F3
            { VK_F4,       "F4"        }, // KEY_F4
            { VK_F5,       "F5"        }, // KEY_F5
            { VK_F6,       "F6"        }, // KEY_F6
            { VK_F7,       "F7"        }, // KEY_F7
            { VK_F8,       "F8"        }, // KEY_F8 
            { VK_F9,       "F9"        }, // KEY_F9
            { VK_F10,      "F10"       }, // KEY_F10
            { VK_F11,      "F11"       }, // KEY_F11
            { VK_F12,      "F12"       }, // KEY_F12

            { VK_SNAPSHOT, "PrintScreen"}, // KEY_PRINT_SCREEN, 
            { VK_SCROLL,   "Scroll"    }, // KEY_SCROLL

            { VK_OEM_3,    "`"         }, // KEY_APOSTROPHE
            { VK_TAB,      "Tab"       }, // KEY_TAB
            { VK_CAPITAL,  "CapsLock"  }, // KEY_CAPS
            { VK_LSHIFT,   "LShift"    }, // KEY_LSHIFT
            { VK_LCONTROL, "LCtrl"     }, // KEY_LCTRL
            { VK_LMENU,    "LAlt"      }, // KEY_LALT 
            { VK_SPACE,    "Space"     }, // KEY_SPACE 
            { VK_RSHIFT,   "RShift"    }, // KEY_RSHIFT
            { VK_RCONTROL, "RCtrl"     }, // KEY_RCTRL
            { VK_RMENU,    "RAlt"      }, // KEY_RALT, 
            { VK_OEM_MINUS,"-"         }, // KEY_SUBTRACT
            { VK_OEM_PLUS, "="         }, // KEY_EQUALS
            { VK_OEM_5,    "\\"        }, // KEY_BACKSLASH
            { VK_BACK,     "Backspace" }, // KEY_BACKSPACE
            { VK_RETURN,   "Enter"     }, // KEY_ENTER

            { VK_OEM_4,    "["         }, // KEY_LSQUARE_BRACKET
            { VK_OEM_6,    "]"         }, // KEY_RSQUARE_BRACKET
            { VK_OEM_1,    ";"         }, // KEY_SEMICOLON
            { VK_OEM_7,    "'"         }, // KEY_QUOTE
            { VK_OEM_COMMA,","         }, // KEY_COMMA
            { VK_OEM_PERIOD,"."        }, // KEY_FULLSTOP
            { VK_OEM_2,    "/"         }, // KEY_FORWARD_SLASH

            { '1',         "1"         }, // KEY_1
            { '2',         "2"         }, // KEY_2
            { '3',         "3"         }, // KEY_3
            { '4',         "4"         }, // KEY_4
            { '5',         "5"         }, // KEY_5
            { '6',         "6"         }, // KEY_6
            { '7',         "7"         }, // KEY_7
            { '8',         "8"         }, // KEY_8
            { '9',         "9"         }, // KEY_9
            { '0',         "0"         }, // KEY_0

            { 'A',         "A"         }, // KEY_A
            { 'B',         "B"         }, // KEY_B
            { 'C',         "C"         }, // KEY_C
            { 'D',         "D"         }, // KEY_D
            { 'E',         "E"         }, // KEY_E
            { 'F',         "F"         }, // KEY_F
            { 'G',         "G"         }, // KEY_G
            { 'H',         "H"         }, // KEY_H
            { 'I',         "I"         }, // KEY_I
            { 'J',         "J"         }, // KEY_J
            { 'K',         "K"         }, // KEY_K
            { 'L',         "L"         }, // KEY_L
            { 'M',         "M"         }, // KEY_M
            { 'N',         "N"         }, // KEY_N
            { 'O',         "O"         }, // KEY_O
            { 'P',         "P"         }, // KEY_P
            { 'Q',         "Q"         }, // KEY_Q
            { 'R',         "R"         }, // KEY_R
            { 'S',         "S"         }, // KEY_S
            { 'T',         "T"         }, // KEY_T
            { 'U',         "U"         }, // KEY_U
            { 'V',         "V"         }, // KEY_V
            { 'W',         "W"         }, // KEY_W
            { 'X',         "X"         }, // KEY_X
            { 'Y',         "Y"         }, // KEY_Y
            { 'Z',         "Z"         }, // KEY_Z

            { VK_INSERT,   "Insert"    }, // KEY_INSERT
            { VK_HOME,     "Home"      }, // KEY_HOME
            { VK_PRIOR,    "PageUp"    }, // KEY_PAGE_UP, 
            { VK_DELETE,   "Delete"    }, // KEY_DELETE
            { VK_END,      "End"       }, // KEY_END
            { VK_NEXT,     "PageDown"  }, // KEY_PAGE_DOWN,

            { VK_LEFT,     "Left"      }, // KEY_LEFT
            { VK_UP,       "Up"        }, // KEY_UP
            { VK_RIGHT,    "Right"     }, // KEY_RIGHT
            { VK_DOWN,     "Down"      }, // KEY_DOWN

            { VK_NUMLOCK,  "NumLock"   }, // KEY_NUM_LOCK

            { VK_DIVIDE,   "Num/"      }, // KEY_NUM_DIVIDE
            { VK_MULTIPLY, "Num*"      }, // KEY_NUM_MULTIPLY, 
            { VK_SUBTRACT, "Num-"      }, // KEY_NUM_SUBTRACT 
            { VK_ADD,      "Num+"      }, // KEY_NUM_ADD
         
            { VK_NUMPAD1,  "Num1"      }, // KEY_NUM_1
            { VK_NUMPAD2,  "Num2"      }, // KEY_NUM_2
            { VK_NUMPAD3,  "Num3"      }, // KEY_NUM_3
            { VK_NUMPAD4,  "Num4"      }, // KEY_NUM_4
            { VK_NUMPAD5,  "Num5"      }, // KEY_NUM_5
            { VK_NUMPAD6,  "Num6"      }, // KEY_NUM_6
            { VK_NUMPAD7,  "Num7"      }, // KEY_NUM_7
            { VK_NUMPAD8,  "Num8"      }, // KEY_NUM_8
            { VK_NUMPAD9,  "Num9"      }, // KEY_NUM_9
            { VK_NUMPAD0,  "Num0"      }, // KEY_NUM_0
            { VK_DECIMAL,  "Num."      }, // KEY_NUM_DECIMAL
            { VK_CLEAR,    "NumClear"  }, // KEY_NUM_CLEAR

            { '\0',        "Invalid"   }
         };

         bool g_cursorEnabled = true;

         struct KeyState
         {
            bool down;
            bool hit;
            bool lifted;
         };

         KeyState g_keyState[KEY_COUNT];

         // Read the hardware to find out if a key is down
         bool IsKeyDownReadHW(int key)
         {
            return ((GetAsyncKeyState(virtualKeyMapping[key].virtualKey) & KEY_DOWN_MASK) != 0);
         }
      }


      void InitKeys()
      {
         for (int i = 0; i < KEY_COUNT; i++)
         {
            g_keyState[i].down   = IsKeyDownReadHW(i);
            g_keyState[i].hit    = false;
            g_keyState[i].lifted = false;
         }
      }


      void PollKeys()
      {
         for (int i = 0; i < KEY_COUNT; i++)
         {
            bool keyCurrentlyDown = IsKeyDownReadHW(i);

            if (keyCurrentlyDown != IsKeyDown(i))
            {
               g_keyState[i].down = keyCurrentlyDown;

               if (keyCurrentlyDown)
               {
                  // key has just been pressed so set the hit flag
                  g_keyState[i].hit = true;
                  g_keyState[i].lifted = false;
               }
               else
               {
                  // key has just been lifted so set the lifted flag
                  g_keyState[i].lifted = true;
                  g_keyState[i].hit = false;
               }
            }
            else
            {
               // key state is same as before so clear hit and lifted flags
               g_keyState[i].hit = false;
               g_keyState[i].lifted = false;
            }
         }
      }

      bool IsKeyDown(int key)
      {
         assert(key < KEY_COUNT);
         return g_keyState[key].down;
      }


      bool IsKeyHit(int key)
      {
         assert(key < KEY_COUNT);
         return g_keyState[key].hit;
      }


      bool IsKeyLifted(int key)
      {
         assert(key < KEY_COUNT);
         return g_keyState[key].lifted;
      }


      const char *KeyToString(int key)
      {
         assert(key < KEY_COUNT);
         return virtualKeyMapping[key].stringRep;
      }


      int StringToKey(const char *s)
      {
         for (int i = 0; i < KEY_COUNT; i++)
         {
            if (stricmp(s,virtualKeyMapping[i].stringRep) == 0)
            {
               return i;
            }
         }

         return KEY_INVALID;
      }


      bool DefaultCursorIsEnabled()
      {
         return g_cursorEnabled;
      }


      void DefaultCursorEnable(bool enable)
      {
         if (enable && !g_cursorEnabled)
         {
            ShowCursor(TRUE);
            g_cursorEnabled = true;
         }
         else if (!enable && g_cursorEnabled)
         {
            ShowCursor(FALSE);
            g_cursorEnabled = false;
         }
      }

   }  // end namespace GF1

//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
