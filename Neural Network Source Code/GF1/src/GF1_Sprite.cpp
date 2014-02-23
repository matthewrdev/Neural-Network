//****************************************************************************
//**
//**    GF1_Sprite.cpp
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Sprite.h"
#include "GF1_Texture.h"
#include "GF1_Texture_Manager.h"
#include "GF1_Vector3.h"

#include <iostream>
#include <string>
using namespace std;

   namespace GF1
   {
      struct SpriteImpl
      {
         Texture *m_tex;
		 std::string m_texName;

         unsigned int m_frameWidth;
         unsigned int m_frameHeight;

         unsigned int m_currentFrame;
         unsigned int m_frameCount;
         bool m_finished;
         bool m_loops;

         unsigned int m_frameHold;
         unsigned int m_framesHeld;

         Vector3 m_position;
         float m_angle;
         float m_scaleX;
         float m_scaleY;

         float m_texLeft;
         float m_texRight;
         float m_texTop;
         float m_texBottom;
         Colour m_cornerColours[4];

         Sprite::BlendMode m_blendMode;

         bool m_bad;
      };


      Sprite::Sprite(
         const char *texName,
         unsigned int frameWidth,
         unsigned int frameHeight,
         unsigned int frameCount,
         unsigned int frameHold,
         bool loops)
      {
         m_impl = new SpriteImpl;

         m_impl->m_texName = texName;
         m_impl->m_tex = TextureManager::Instance().AddReference(m_impl->m_texName);

         m_impl->m_frameWidth = frameWidth;
         m_impl->m_frameHeight = frameHeight;

         m_impl->m_frameCount = frameCount;
         m_impl->m_currentFrame = 0;
         m_impl->m_frameHold = frameHold;
         m_impl->m_framesHeld = 0;

         m_impl->m_finished = false;
         m_impl->m_loops = loops;

         m_impl->m_position.SetZero();
         m_impl->m_angle = 0;

         m_impl->m_scaleX = 1.0f;
         m_impl->m_scaleY = 1.0f;

         if (m_impl->m_tex->GetType() == Texture::TYPE_RGB)
         {
            m_impl->m_blendMode = BLEND_MODE_NONE;
         }
         else
         {
            m_impl->m_blendMode = BLEND_MODE_TRANSPARENT;
         }

         SetColour(Colour::WHITE);

         m_impl->m_texLeft = 0.0f;
         m_impl->m_texRight = 1.0f;
         m_impl->m_texTop = 0.0f;
         m_impl->m_texBottom = 1.0f;

         m_impl->m_bad = false;
      }


      Sprite::Sprite(const Sprite &rhs)
      {
         m_impl = new SpriteImpl;
         *m_impl = *(rhs.m_impl);

         m_impl->m_tex = TextureManager::Instance().AddReference(m_impl->m_texName);
      }


      Sprite::~Sprite()
      {
         TextureManager::Instance().Release(m_impl->m_texName);
         delete m_impl;
      }


      bool Sprite::Bad() const
      {
         return m_impl->m_bad;
      }


      const Vector3 &Sprite::GetPosition() const
      {
         return m_impl->m_position;
      }


      float Sprite::GetAngle() const
      {
         return m_impl->m_angle;
      }

      void Sprite::SetScale(float scaleX, float scaleY)
      {
         m_impl->m_scaleX = scaleX;
         m_impl->m_scaleY = scaleY;
      }

      float Sprite::GetScaleX() const
      {
         return m_impl->m_scaleX;
      }

      float Sprite::GetScaleY() const
      {
         return m_impl->m_scaleY;
      }

      unsigned int Sprite::GetFrameWidth() const
      {
         return m_impl->m_frameWidth;
      }


      unsigned int Sprite::GetFrameHeight() const
      {
         return m_impl->m_frameHeight;
      }


      unsigned int Sprite::GetFrameCount() const
      {
         return m_impl->m_frameCount;
      }


      unsigned int Sprite::GetCurrentFrame() const
      {
         return m_impl->m_currentFrame;
      }


      bool Sprite::IsAnimationFinished() const
      {
         return m_impl->m_finished;
      }


      Sprite::BlendMode Sprite::GetBlendMode() const
      {
         return m_impl->m_blendMode;
      }


	  const char *Sprite::GetTextureName() const
      {
         return m_impl->m_texName.c_str();
      }


      Sprite::Filter Sprite::GetMinificationFilter() const
      {
         return static_cast<Sprite::Filter>(
            m_impl->m_tex->GetMinificationFilter());
      }


      Sprite::Filter Sprite::GetMagnificationFilter() const
      {
         return static_cast<Sprite::Filter>(
            m_impl->m_tex->GetMagnificationFilter());
      }

      Sprite &Sprite::operator=(const Sprite &rhs)
      {
         TextureManager::Instance().Release(m_impl->m_texName);
         *m_impl = *(rhs.m_impl);
         m_impl->m_tex = TextureManager::Instance().AddReference(m_impl->m_texName);
         return *this;
      }


      void Sprite::AutoFrameAdvance()
      {
         if (m_impl->m_frameHold != 0)
         {
            if (m_impl->m_framesHeld == m_impl->m_frameHold - 1)
            {
               m_impl->m_framesHeld = 0;
               NextFrame();
            }
            else
            {
               m_impl->m_framesHeld++;
            }
         }
      }


      void Sprite::Render()
      {
         glEnable(GL_TEXTURE_2D);
         if (m_impl->m_blendMode == BLEND_MODE_TRANSPARENT)
         {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);
         }
         else if (m_impl->m_blendMode == BLEND_MODE_ADDITIVE)
         {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glEnable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);
         }
         else if (m_impl->m_blendMode == BLEND_MODE_ADDITIVE_COLOUR)
         {
            glBlendFunc(GL_SRC_COLOR, GL_ONE);
            glEnable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);
         }
         else
         {
            glDisable(GL_BLEND);
            if (m_impl->m_tex->GetType() == Texture::TYPE_RGB)
            {
               glDisable(GL_ALPHA_TEST);
            }
            else
            {
               glEnable(GL_ALPHA_TEST);
            }
         }

         bool firstLoad = !m_impl->m_tex->IsCachedIn();

         m_impl->m_tex->Activate();

         if (m_impl->m_tex->Bad())
         {
            m_impl->m_bad = true;
         }
         else
         {
            if (firstLoad)
            {
               if(m_impl->m_frameWidth > m_impl->m_tex->GetWidth() || 
                m_impl->m_frameHeight > m_impl->m_tex->GetHeight())
               {
                  cout<< "Frame size is too large for texture. " << 
                     m_impl->m_tex->GetFileName() << " is " << 
                     m_impl->m_tex->GetWidth() << "x" << m_impl->m_tex->GetHeight() <<
                     " but the requested frame size is " << 
                     m_impl->m_frameWidth << "x" << m_impl->m_frameHeight << endl;
                  m_impl->m_bad = true;
               }
               else if(m_impl->m_frameWidth == 0 || m_impl->m_frameHeight == 0)
               {
                  m_impl->m_frameWidth = m_impl->m_tex->GetWidth();
                  m_impl->m_frameHeight = m_impl->m_tex->GetHeight();
               }
            }
         }


         // If the texture failed to load draw a pink quad in place of the 
         // sprite
         if (Bad())
         {
            SetColour(Colour::PINK);
            glDisable(GL_TEXTURE_2D);
         }
         else
         {
            CalculateTextureCoords();

            if (!m_impl->m_tex->IsLocked())
            {
               m_impl->m_tex->UpdateDirty();
            }
         }

         // Work out the width and height of the frame to be drawn based
         // on the frame width of the sprite and the current scale this 
         // determines what values the verticies will have.
         float width = (m_impl->m_frameWidth) * m_impl->m_scaleX;
         float height = (m_impl->m_frameHeight) * m_impl->m_scaleY;

         float negHalfWidth  = 
            static_cast<float>(-(static_cast<int>(width)>>1));

         float negHalfHeight = 
            static_cast<float>(-(static_cast<int>(height)>>1));

         // About to start making local changes to the world matrix so save it
         glPushMatrix();

         if (m_impl->m_angle == 0)
         {
            // No rotation is required so we can optimise the 2 translations 
            // required into one
            glTranslatef(
               m_impl->m_position.x + negHalfWidth, 
               m_impl->m_position.y + negHalfHeight, 
               m_impl->m_position.z);
         }
         else
         {
            // Tranformations are applied in the reverse order than they are 
            // declared in code.  We are defining the verticies from the 
            // bottom left corner but we want to rotate from the centre so
            // we have to translate to the centre before we do the rotate.
            // Then translate the rest of the way into position.

            // 3. Now that the sprite is rotated correctly we can move it to
            //    its correct position on the screen.
            glTranslatef(m_impl->m_position.x, m_impl->m_position.y, 
               m_impl->m_position.z);

            // 2. Now that the centre of the sprite is at 0, 0, 0 we can 
            // rotate around the z axis (the one coming into and out of the 
            // screen)
            glRotatef(m_impl->m_angle, 0.0f, 0.0f, 1.0f);

            // 1. Translate the verticies so 0, 0, 0 is in the centre of the
            //    sprite ready for rotation.
            glTranslatef(negHalfWidth, negHalfHeight, 0.0f);
         }

         // Draw the sprite as a textured quad
         // The sprite frame determines the texture coordinates at each vertex
         // Each vertex has an individual colour/alpha value which is normally
         // white (1, 1, 1, 1) unless otherwise specified.
         glBegin(GL_QUADS);

            // top left
            glTexCoord2f(m_impl->m_texLeft, m_impl->m_texTop); 
            glColor4f(m_impl->m_cornerColours[0].r, 
               m_impl->m_cornerColours[0].g, 
               m_impl->m_cornerColours[0].b, 
               m_impl->m_cornerColours[0].a);
            glVertex3f(0, height, 0);

            // top right
            glTexCoord2f(m_impl->m_texRight, m_impl->m_texTop); 
            glColor4f(m_impl->m_cornerColours[1].r, 
               m_impl->m_cornerColours[1].g, 
               m_impl->m_cornerColours[1].b, 
               m_impl->m_cornerColours[1].a);
            glVertex3f( width, height, 0);

            // bottom right
            glTexCoord2f(m_impl->m_texRight, m_impl->m_texBottom); 
            glColor4f(m_impl->m_cornerColours[3].r, 
               m_impl->m_cornerColours[3].g, 
               m_impl->m_cornerColours[3].b, 
               m_impl->m_cornerColours[3].a);
            glVertex3f( width, 0, 0);

            // bottom left
            glTexCoord2f(m_impl->m_texLeft, m_impl->m_texBottom); 
            glColor4f(m_impl->m_cornerColours[2].r, 
               m_impl->m_cornerColours[2].g, 
               m_impl->m_cornerColours[2].b, 
               m_impl->m_cornerColours[2].a);
            glVertex3f(0, 0, 0);

         glEnd();

         // Finished with all the local changes to the world matrix so 
         // restore it
         glPopMatrix();
      } 


      void Sprite::SetCurrentFrame(unsigned int currentFrame)
      {
         assert(currentFrame < m_impl->m_frameCount);
         m_impl->m_currentFrame = currentFrame;
         CalculateTextureCoords();
      }


      void Sprite::SetPosition(const Vector3 &pos)
      {
         m_impl->m_position = pos;
      }


      void Sprite::SetAngle(float angle)
      {
         m_impl->m_angle = angle;
      }


      void Sprite::ResetAnimation()
      {
         m_impl->m_currentFrame = 0;
         CalculateTextureCoords();
         m_impl->m_framesHeld = 0;
         m_impl->m_finished = false;
      }


      void Sprite::CalculateTextureCoords()
      {
         if (Bad() || !m_impl->m_tex->IsCachedIn())
         {
            return;
         }

         float tex_frameWidth;
         float tex_frameHeight;

         tex_frameWidth = m_impl->m_frameWidth / (float)m_impl->m_tex->GetWidthP2();
         tex_frameHeight = m_impl->m_frameHeight / (float)m_impl->m_tex->GetHeightP2();

         m_impl->m_texLeft = tex_frameWidth * int(m_impl->m_currentFrame 
                           % (m_impl->m_tex->GetWidth() / m_impl->m_frameWidth));
         m_impl->m_texRight = m_impl->m_texLeft + tex_frameWidth;
         m_impl->m_texTop = tex_frameHeight * int(m_impl->m_currentFrame 
                          / (m_impl->m_tex->GetWidth() / m_impl->m_frameWidth));
         m_impl->m_texBottom = m_impl->m_texTop + tex_frameHeight;
      }


      void Sprite::NextFrame()
      {
         if (m_impl->m_currentFrame == m_impl->m_frameCount - 1)
         {
            if (m_impl->m_loops)
            {
               m_impl->m_currentFrame = 0;
               CalculateTextureCoords();
            }
            else
            {
               m_impl->m_finished = true;
            }
         }
         else
         {
            m_impl->m_currentFrame++;
            CalculateTextureCoords();
         }
      }


      void Sprite::SetBlendMode(BlendMode newBlendMode)
      {
         m_impl->m_blendMode = newBlendMode;
      }


      void Sprite::EnableAutoAlphaMask(const Colour &c, float tolerance, bool fade)
      {
         m_impl->m_tex->EnableAutoAlphaMask(c, tolerance, fade);
      }


      void Sprite::DisableAutoAlphaMask()
      {
         m_impl->m_tex->DisableAutoAlphaMask();
      }


      void Sprite::SetColour(const Colour &c)
      {
         m_impl->m_cornerColours[0] = c;
         m_impl->m_cornerColours[1] = c;
         m_impl->m_cornerColours[2] = c;
         m_impl->m_cornerColours[3] = c;
      }


      void Sprite::SetColour(const Colour &c, Corner corner)
      {
         switch(corner)
         {
         case CORNER_TOP_LEFT:
            m_impl->m_cornerColours[0] = c;
            break;
         case CORNER_TOP_RIGHT:
            m_impl->m_cornerColours[1] = c;
            break;
         case CORNER_BOTTOM_LEFT:
            m_impl->m_cornerColours[2] = c;
            break;
         case CORNER_BOTTOM_RIGHT:
            m_impl->m_cornerColours[3] = c;
            break;
         }
      }


      Colour Sprite::GetColour(Corner corner) const
      {
         switch(corner)
         {
         case CORNER_TOP_LEFT:
            return m_impl->m_cornerColours[0];
            break;
         case CORNER_TOP_RIGHT:
            return m_impl->m_cornerColours[1];
            break;
         case CORNER_BOTTOM_LEFT:
            return m_impl->m_cornerColours[2];
            break;
         case CORNER_BOTTOM_RIGHT:
            return m_impl->m_cornerColours[3];
            break;
         }
         return Colour::BLACK;
      }


	   void Sprite::Revert()
	   {
		   m_impl->m_tex->Revert();
	   }


      fdword *Sprite::Lock()
      {
         return m_impl->m_tex->Lock();
      }


      void Sprite::Unlock()
      {
         m_impl->m_tex->Unlock();
      }


      void Sprite::UpdateRegion(fdword y1, fdword y2)
      {
         m_impl->m_tex->UpdateRegion(y1, y2);
      }


      void Sprite::SetPixelRGBA(fdword x, fdword y, fdword c)
      {
         if(x<m_impl->m_tex->GetWidth() && y<m_impl->m_tex->GetHeight())
         {
            if(m_impl->m_tex->IsLocked())
            {
               m_impl->m_tex->GetCurrentLock()[x + y * m_impl->m_tex->GetWidth()] = c;
               m_impl->m_tex->SetDirty(y);
            }
         }
      }

      void Sprite::ClearPixelsRGBA(fdword c)
      {
         if(m_impl->m_tex->IsLocked())
         {
            fdword *lock = m_impl->m_tex->GetCurrentLock();
            fdword count = m_impl->m_tex->GetWidth() * m_impl->m_tex->GetHeight();
            for(fdword i = 0; i < count; i++)
            {
               lock[i]=c;
            }
            m_impl->m_tex->UpdateRegion(0, m_impl->m_tex->GetHeight()-1);
         }
      }

      void Sprite::ClearPixelsColour(const Colour &c)
      {
         ClearPixelsRGBA(c.ToInteger(255,0,255,8,255,16,255,24));
      }

      void Sprite::SetPixelColour(fdword x, fdword y, const Colour &c)
      {
         if(x<m_impl->m_tex->GetWidth() && y<m_impl->m_tex->GetHeight())
         {
            if(m_impl->m_tex->IsLocked())
            {
               m_impl->m_tex->GetCurrentLock()[x + y * m_impl->m_tex->GetWidth()] = c.ToInteger(255,0,255,8,255,16,255,24);
               m_impl->m_tex->SetDirty(y);
            }
         }
      }


      fdword Sprite::GetPixelRGBA(fdword x, fdword y)
      {
         if(x<m_impl->m_tex->GetWidth() && y<m_impl->m_tex->GetHeight())
         {
            if(m_impl->m_tex->IsLocked())
            {
               return m_impl->m_tex->GetCurrentLock()[x + y * m_impl->m_tex->GetWidth()];
            }
         }
         return 0;
      }


      Colour Sprite::GetPixelColour(fdword x, fdword y)
      {
         Colour c;
         if(x<m_impl->m_tex->GetWidth() && y<m_impl->m_tex->GetHeight())
         {
            if(m_impl->m_tex->IsLocked())
            {
               c.FromInteger(m_impl->m_tex->GetCurrentLock()[x + y * m_impl->m_tex->GetWidth()], 255,0,255,8,255,16,255,24);
            }
         }
         return c;
      }

      void Sprite::SetFilter(Filter minFilter, Filter magFilter)
      {
         m_impl->m_tex->SetFilter(
            static_cast<Texture::Filter>(minFilter),
            static_cast<Texture::Filter>(magFilter));
      }

   }  // end namespace GF1



//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
