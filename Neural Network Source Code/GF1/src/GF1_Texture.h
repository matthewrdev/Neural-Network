#ifndef TEXTURE_H
#define TEXTURE_H
//****************************************************************************
//**
//**    Texture.h
//**
//**    Copyright (c) 2002 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include "GF1_Types.h"
#include "GF1_Colour.h"

   namespace GF1
   {
      struct TextureImpl;

      class Texture
      {
      public:
         enum Type
         {
            TYPE_RGB,
            TYPE_RGBA
         };

         // ------------------------------------------------------------------
         // Filter
         // ------------------------------------------------------------------
         // The texture mapping filter used to render the texture.
         //
         // NEAREST
         //    The fastest/simplest method which produced blocky results when
         //    scaled however this is the default as it prevents the bleeding 
         //    between sprite frames that can occur with LINEAER filtering.
         //
         // LINEAR
         //    This method samples surronding points in the texture when 
         //    choosing the colour of the destination pixel resulting in a
         //    smoother final image when scaled.
         // ------------------------------------------------------------------
         enum Filter
         {
            FILTER_NEAREST,
            FILTER_LINEAR
         };

         // creates the texture and loads the header
         // sets the bad flag if file cannot be opened or the header is invalid
         Texture(const std::string &filename);

         ~Texture();

         // loads the texture into memory
         // true on success
         bool CacheIn();

         // unloads the Texture from memory
         void CacheOut();

         // makes this the current active OpenGL Texture
         // Texture must be successfully cached in
         void Activate();

         // true if the Texture is currently cached in
         bool IsCachedIn() const;

         // true if the header or image failed to load
         bool Bad() const;

         // obtain the width of the Texture
         fdword GetWidth() const;

         // obtain the height of the Texture
         fdword GetHeight() const;

         // obtain the width of the Texture rounded up to a power of 2
         fdword GetWidthP2() const;

         // obtain the height of the Texture rounded up to a power of 2
         fdword GetHeightP2() const;

         // obtain the type of the Texture
         Type GetType() const;

         // obtain the filename of the texture
		 std::string GetFileName() const;


         // ------------------------------------------------------------------
         // GetMinificationFilter
         // ------------------------------------------------------------------
         // Obtain the type of texture mapping filter used when the area being
         // texture mapped is smaller than the actual texture.
         // ------------------------------------------------------------------
         Filter GetMinificationFilter() const;


         // ------------------------------------------------------------------
         // GetMagnificationFilter
         // ------------------------------------------------------------------
         // Obtain the type of texture mapping filter used when the area being
         // texture mapped is larger than the actual texture.
         // ------------------------------------------------------------------
         Filter GetMagnificationFilter() const;


         // Enable and disable automatic generation of alpha channels. See Sprite.h
         // for more info.
         void EnableAutoAlphaMask(const Colour &c, float tolerance, bool fade);
         void DisableAutoAlphaMask();

		   void Revert();
         fdword *Lock();
         void Unlock();
         void BuildDynamicSurface();
         void UpdateRegion(fdword y1, fdword y2);
         void UpdateDirty();
         bool IsLocked();
         fdword *GetCurrentLock();
         void SetDirty(fdword y);

         // ------------------------------------------------------------------
         // SetFilters
         // ------------------------------------------------------------------
         // Specify the type of texture mapping filter used when the area being
         // texture mapped is smaller or larger than the actual texture.
         // ------------------------------------------------------------------
         void SetFilter(Filter minFilter, Filter magFilter);


      private:
         Texture(const Texture &rhs);              // not implemented
         Texture &operator=(const Texture &rhs);   // not implemented

         TextureImpl *m_impl;
      };

   }  // end namespace GF1



//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
