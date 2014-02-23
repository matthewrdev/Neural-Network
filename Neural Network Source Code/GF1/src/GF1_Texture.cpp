//****************************************************************************
//**
//**    GF1_Texture.cpp
//**
//**    Copyright (c) 2002 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Texture.h"
#include "GF1_Colour.h"
#include "GF1_Vector3.h"
#include "GF1_Math.h"
#include "il/il.h"
#include "il/ilu.h"
#include "glext.h"

#include <iostream>
#include <string>
using std::cerr;
using std::endl;


   namespace GF1
   {
      struct TextureImpl
      {
		 std::string m_filename;
         fdword m_imageSize;        // Size of image data in bytes
         fdword m_bpp;              // Image Color Depth In Bits Per Pixel
         fdword m_width;            // Image Width
         fdword m_height;           // Image Height
         fdword m_widthP2;         // Image Width rounded up to power of 2
         fdword m_heightP2;        // Image Height rounded up to power of 2
         fdword m_id;               // Texture ID Used To Select A Texture
         Texture::Type m_type;      // Image Type (GL_RGB, GL_RGBA)
         bool m_bad;                // Has a Texture load failed
         bool m_autoGenAlphaMask;
         bool m_autoGenAlphaMaskFade;
         Colour m_autoGenAlphaMaskColour;
         float m_autoGenAlphaMaskTolerance;
         fdword *m_texture_surface;
         bool *m_texture_dirty_array;
         bool m_texture_dirty_flag;
         bool m_texture_locked;
         enum {e_dxt_none=0, e_dxt1, e_dxt2, e_dxt3, e_dxt4, e_dxt5};
         int m_dxt_format;
         int m_dxt_size;

         Texture::Filter m_minificationFilter;
         Texture::Filter m_magnificationFilter;
      };

      namespace
      {
         const int c_max_texture_size_power = 12;  // Textures up to 4096 res
         const fdword c_rgba_red_mask    = 255;
         const fdword c_rgba_green_mask  = 255;
         const fdword c_rgba_blue_mask   = 255;
         const fdword c_rgba_alpha_mask  = 255;
         const fdword c_rgba_red_shift   = 0;
         const fdword c_rgba_green_shift = 8;
         const fdword c_rgba_blue_shift  = 16;
         const fdword c_rgba_alpha_shift = 24;
         const fdword c_rgb_red_mask    = 255;
         const fdword c_rgb_green_mask  = 255;
         const fdword c_rgb_blue_mask   = 255;
         const fdword c_rgb_alpha_mask  = 0;
         const fdword c_rgb_red_shift   = 0;
         const fdword c_rgb_green_shift = 8;
         const fdword c_rgb_blue_shift  = 16;
         const fdword c_rgb_alpha_shift = 0;


         void UpdateFiltering(TextureImpl *texImpl)
         {
            GLint minFilter = 
               (texImpl->m_minificationFilter == Texture::FILTER_NEAREST) 
               ? GL_NEAREST : GL_LINEAR;

            GLint magFilter = 
               (texImpl->m_magnificationFilter == Texture::FILTER_NEAREST)
               ? GL_NEAREST : GL_LINEAR;

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
         }


         void BindTextureToOpenGL(TextureImpl *texImpl, fbyte *imageData)
         {
            // generate a texture name (id)
            glGenTextures(1, &texImpl->m_id);
            glBindTexture(GL_TEXTURE_2D, texImpl->m_id);

            GLint format = ((texImpl->m_type == Texture::TYPE_RGB) ? GL_RGB : GL_RGBA);

            if(texImpl->m_dxt_format == TextureImpl::e_dxt_none)
            {
               glTexImage2D(GL_TEXTURE_2D, 0, format, texImpl->m_widthP2, texImpl->m_heightP2, 0, format, 
                  GL_UNSIGNED_BYTE, imageData);
            }
            else
            {
               PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)wglGetProcAddress("glCompressedTexImage2DARB");
               if(glCompressedTexImage2DARB)
               {
                  int openglmode;
                  switch(texImpl->m_dxt_format)
                  {
                  case TextureImpl::e_dxt1:
                     openglmode = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                     break;
                  case TextureImpl::e_dxt2:
                     openglmode = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                     break;
                  case TextureImpl::e_dxt3:
                     openglmode = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                     break;
                  case TextureImpl::e_dxt4:
                     openglmode = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                     break;
                  case TextureImpl::e_dxt5:
                     openglmode = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                     break;
                  }
                  glCompressedTexImage2DARB(GL_TEXTURE_2D,0,openglmode,texImpl->m_width,texImpl->m_height,0,texImpl->m_dxt_size,imageData);
               }
            }

            UpdateFiltering(texImpl);

            // GL_CLAMP causes texture coordinates to be clamped to the range [0,1] 
            // and is useful for preventing wrapping artifacts when mapping a single 
            // image onto an object. 
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
         }

         void UnbindTextureFromOpenGL(TextureImpl *texImpl)
         {
            glDeleteTextures(1, &texImpl->m_id);
            texImpl->m_id = 0;
         }
      }

	  Texture::Texture(const std::string &filename)
      {
         m_impl = new TextureImpl;

         m_impl->m_id = 0;
         m_impl->m_filename = filename;

         m_impl->m_bad = false;
         m_impl->m_autoGenAlphaMask = false;

         m_impl->m_imageSize = 0;
         m_impl->m_bpp = 0;
         m_impl->m_width = 0;
         m_impl->m_height = 0;
         m_impl->m_widthP2 = 0;
         m_impl->m_heightP2 = 0;
         m_impl->m_type = TYPE_RGB;
         m_impl->m_autoGenAlphaMaskFade = false;
         m_impl->m_autoGenAlphaMaskColour = Colour::PINK;
         m_impl->m_autoGenAlphaMaskTolerance = 0.0f;
         m_impl->m_texture_surface = NULL;
         m_impl->m_texture_dirty_array = NULL;
         m_impl->m_texture_dirty_flag = false;
         m_impl->m_texture_locked = false;
         m_impl->m_dxt_format = TextureImpl::e_dxt_none;
         m_impl->m_dxt_size = 0;

         m_impl->m_minificationFilter = FILTER_NEAREST;
         m_impl->m_magnificationFilter = FILTER_NEAREST;
      }


      Texture::~Texture()
      {
         CacheOut();
         delete m_impl;
      }


      bool Texture::CacheIn()
      {
         fbyte *im;
         if (Bad())
         {
            return false;
         }
         if (!IsCachedIn())
         {
            ILuint image_id;
            ILint format;
            
            ilGenImages(1, &image_id);
            ilBindImage(image_id);

            if(!ilLoadImage((ILstring)m_impl->m_filename.c_str()))
            {
               ilDeleteImages(1, &image_id);
               m_impl->m_bad = true;
               cerr << "Failed to load texture file " << m_impl->m_filename << endl;
               return false;
            }

            format=ilGetInteger(IL_DXTC_DATA_FORMAT);
            switch(format)
            {
            case IL_DXT_NO_COMP:
               break;
            case IL_DXT1:
               m_impl->m_dxt_format = TextureImpl::e_dxt1;
               break;
            case IL_DXT2:
               m_impl->m_dxt_format = TextureImpl::e_dxt2;
               break;
            case IL_DXT3:
               m_impl->m_dxt_format = TextureImpl::e_dxt3;
               break;
            case IL_DXT4:
               m_impl->m_dxt_format = TextureImpl::e_dxt4;
               break;
            case IL_DXT5:
               m_impl->m_dxt_format = TextureImpl::e_dxt5;
               break;
            }
            if(m_impl->m_dxt_format!=TextureImpl::e_dxt_none)
            {
               m_impl->m_width=ilGetInteger(IL_IMAGE_WIDTH);
               m_impl->m_height=ilGetInteger(IL_IMAGE_HEIGHT);
               m_impl->m_widthP2 = m_impl->m_width;
               m_impl->m_heightP2 = m_impl->m_height;
               m_impl->m_type = Texture::TYPE_RGBA;
               ILint s;
               char *data;
               s = ilGetDXTCData(NULL,0,format);
               m_impl->m_dxt_size = s;
               im = new fbyte[s];
               ilGetDXTCData(im,s,format);
               BindTextureToOpenGL(m_impl, im);
               delete [] im;

            }
            else
            {
               format=ilGetInteger(IL_IMAGE_FORMAT);

               if(format == IL_RGBA || format == IL_BGRA || format == IL_LUMINANCE_ALPHA || m_impl->m_autoGenAlphaMask)
               {
                  ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);
                  m_impl->m_type = Texture::TYPE_RGBA;
               }
               else
               {
                  ilConvertImage(IL_RGB,IL_UNSIGNED_BYTE);
                  m_impl->m_type = Texture::TYPE_RGB;
               }

               m_impl->m_width=ilGetInteger(IL_IMAGE_WIDTH);
               m_impl->m_height=ilGetInteger(IL_IMAGE_HEIGHT);
               m_impl->m_widthP2 = m_impl->m_width;
               m_impl->m_heightP2 = m_impl->m_height;

               if((m_impl->m_width  & (m_impl->m_width  - 1)) != 0 ||
                  (m_impl->m_height & (m_impl->m_height - 1)) != 0)
               {
                  for(fdword i=2;i<=c_max_texture_size_power;i++)
                  {
                     if((m_impl->m_width<<1) > (1UL<<i))
                     {
                        m_impl->m_widthP2 = (1UL<<i);
                     }
                     if((m_impl->m_height<<1) > (1UL<<i))
                     {
                        m_impl->m_heightP2 = (1UL<<i);
                     }
                  }

				  cerr << m_impl->m_filename << " has invalid texture size: " << 
                     m_impl->m_width << "x" << m_impl->m_height << 
                     "  resizing to " <<
                     m_impl->m_widthP2 << "x" << m_impl->m_heightP2 << endl;

                  cerr << "   Wasted space due to texture resize: " << 
                     (((m_impl->m_widthP2 * m_impl->m_heightP2) - 
                       (m_impl->m_width * m_impl->m_height)) / 
                       float(m_impl->m_widthP2 * m_impl->m_heightP2)) * 100.0f << 
                       "%" << endl;

                  iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
                  ilClearColour(1.0f,0.2f,0.8f,1.0f);

                  if(!iluEnlargeCanvas(m_impl->m_widthP2, m_impl->m_heightP2, ilGetInteger(IL_IMAGE_DEPTH)))
                  {
                     ilDeleteImages(1, &image_id);
                     m_impl->m_bad = true;
                     cerr << "Resize of texture canvas failed" << endl;
                     return false;
                  }
               }

               im = ilGetData();
               if(m_impl->m_autoGenAlphaMask)
               {
                  Colour c;
                  fdword i,j;
                  for(j=0;j<m_impl->m_height;j++)
                  {
                     for(i=0;i<m_impl->m_width;i++)
                     {
                        c.FromInteger(((fdword *)im)[j*m_impl->m_widthP2+i],
                           c_rgba_red_mask, c_rgba_red_shift,
                           c_rgba_green_mask, c_rgba_green_shift,
                           c_rgba_blue_mask, c_rgba_blue_shift,
                           c_rgba_alpha_mask, c_rgba_alpha_shift);
                        GF1::Colour cd(c - m_impl->m_autoGenAlphaMaskColour);
                        if(m_impl->m_autoGenAlphaMaskFade && m_impl->m_autoGenAlphaMaskTolerance > 0)
                        {
                           c.a = cd.Length() / m_impl->m_autoGenAlphaMaskTolerance;
                        }
                        else
                        {
                           if(cd.LengthSquared() <= m_impl->m_autoGenAlphaMaskTolerance * m_impl->m_autoGenAlphaMaskTolerance)
                           {
                              c.a=0.0f;
                           }
                           else
                           {
                              c.a=1.0f;
                           }
                        }
                        ((fdword *)im)[j*m_impl->m_widthP2+i] = c.ToInteger(255,0,255,8,255,16,255,24);
                     }
                  }
               }
               BindTextureToOpenGL(m_impl, im);
            }
            ilDeleteImages(1, &image_id);
         }
         return true;
      }

      void Texture::EnableAutoAlphaMask(const Colour &c, float tolerance, bool fade)
      {
         m_impl->m_autoGenAlphaMask = true;
         m_impl->m_autoGenAlphaMaskColour = c;
         m_impl->m_autoGenAlphaMaskTolerance = tolerance;
         m_impl->m_autoGenAlphaMaskFade = fade;
      }

      void Texture::DisableAutoAlphaMask()
      {
         m_impl->m_autoGenAlphaMask = true;
      }

      void Texture::CacheOut()
      {
         if (!Bad() && IsCachedIn())
         {
            UnbindTextureFromOpenGL(m_impl);
            delete [] m_impl->m_texture_surface;
            delete [] m_impl->m_texture_dirty_array;
            m_impl->m_texture_surface = NULL;
            m_impl->m_texture_dirty_array = NULL;
         }
      }


      void Texture::Activate()
      {
         if (!Bad())
         {
            if (IsCachedIn())
            {
               glBindTexture(GL_TEXTURE_2D, m_impl->m_id);
            }
            else
            {
               // texture not loaded try to cache in
               CacheIn();

               // make sure the cache in worked
               if (!Bad())
               {
                  glBindTexture(GL_TEXTURE_2D, m_impl->m_id);
               }
            }
         }
      }


      bool Texture::IsCachedIn() const
      {
         return (m_impl->m_id != 0);
      }


      bool Texture::Bad() const
      {
         return m_impl->m_bad;
      }


      fdword Texture::GetWidth() const
      {
         return m_impl->m_width;
      }


      fdword Texture::GetHeight() const
      {
         return m_impl->m_height;
      }

      fdword Texture::GetWidthP2() const
      {
         return m_impl->m_widthP2;
      }


      fdword Texture::GetHeightP2() const
      {
         return m_impl->m_heightP2;
      }

      Texture::Type Texture::GetType() const
      {
         return m_impl->m_type;
      }

	  std::string Texture::GetFileName() const
      {
         return m_impl->m_filename;
      }


      Texture::Filter Texture::GetMinificationFilter() const
      {
         return m_impl->m_minificationFilter;
      }


      Texture::Filter Texture::GetMagnificationFilter() const
      {
         return m_impl->m_magnificationFilter;
      }


	   void Texture::Revert()
	   {
		   if (IsCachedIn())
		   {
			   CacheOut();
			   CacheIn();
		   }
	   }


      fdword *Texture::Lock()
      {
         if(Bad() || (m_impl->m_dxt_format != TextureImpl::e_dxt_none))
         {
            return NULL;
         }
         m_impl->m_texture_locked = true;
         if(!m_impl->m_texture_surface)
         {
            BuildDynamicSurface();
         }

         return m_impl->m_texture_surface;
      }

      void Texture::Unlock()
      {
         m_impl->m_texture_locked = false;
      }

      bool Texture::IsLocked()
      {
         return m_impl->m_texture_locked;
      }

      fdword *Texture::GetCurrentLock()
      {
         if(m_impl->m_texture_locked)
         {
            return m_impl->m_texture_surface;
         }
         else
         {
            return NULL;
         }
      }

      void Texture::SetDirty(fdword y)
      {
         m_impl->m_texture_dirty_array[y] = true;
         m_impl->m_texture_dirty_flag = true;
      }


      void Texture::BuildDynamicSurface()
      {
         Activate();

         if(Bad())
         {
            return;
         }

         fdword pixelsP2 = m_impl->m_heightP2 * m_impl->m_widthP2;
         fdword pixels = m_impl->m_height * m_impl->m_width;

         fdword *texture_surfaceP2 = new fdword[pixelsP2];
         m_impl->m_texture_surface = new fdword[pixels];
         m_impl->m_texture_dirty_array = new bool[m_impl->m_height];

         glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
            texture_surfaceP2);

         fdword *dst = m_impl->m_texture_surface;
         fdword *src = texture_surfaceP2;
         fdword dstWidthBytes = m_impl->m_width * sizeof(fdword);

         // copy from the power of 2 texture so we only store the
         // original texture size in system memory
         for (unsigned int i = 0 ; i < m_impl->m_height; i++)
         {
            memcpy(dst, src, dstWidthBytes);
            dst += m_impl->m_width;
            src += m_impl->m_widthP2;
         }

         delete texture_surfaceP2;

         for (fdword i = 0; i < m_impl->m_height; i++)
         {
            m_impl->m_texture_dirty_array[i] = false;
         }
         m_impl->m_texture_dirty_flag = false;
      }


      void Texture::UpdateRegion(fdword y1, fdword y2)
      {
         for(fdword i = y1; i<=y2; i++)
         {
            m_impl->m_texture_dirty_array[i] = true;
         }
         m_impl->m_texture_dirty_flag = true;
      }

      void Texture::UpdateDirty()
      {
         if(!m_impl->m_texture_dirty_flag)
         {
            return;
         }
         fdword y1=0,y2=0;
         bool found_dirty=false;

         for(fdword i = 0; i<m_impl->m_height; i++)
         {
            if(!found_dirty)
            {
               if(m_impl->m_texture_dirty_array[i])
               {
                  found_dirty = true;
                  y1 = i;
               }
            }
            else
            {
               if(!m_impl->m_texture_dirty_array[i])
               {
                  found_dirty = false;
                  y2 = i - 1;
                  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, y1, m_impl->m_width, y2-y1+1, GL_RGBA, GL_UNSIGNED_BYTE, m_impl->m_texture_surface + m_impl->m_width*y1);
               }
            }
            m_impl->m_texture_dirty_array[i] = false;
         }
         if(found_dirty)
         {
            y2 = m_impl->m_height;
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, y1, m_impl->m_width, y2-y1, GL_RGBA, GL_UNSIGNED_BYTE, m_impl->m_texture_surface + m_impl->m_width*y1);
         }
         m_impl->m_texture_dirty_flag = false;
      }

      void Texture::SetFilter(Filter minFilter, Filter magFilter)
      {
         m_impl->m_minificationFilter = minFilter;
         m_impl->m_magnificationFilter = magFilter;

         if (IsCachedIn())
         {
            Activate();
            UpdateFiltering(m_impl);
         }
      }

   }  // end namespace GF1




//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
