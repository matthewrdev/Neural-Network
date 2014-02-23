#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
//****************************************************************************
//**
//**    TextureManager.h
//**
//**    Copyright (c) 2002 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************

   namespace GF1
   {
      struct TextureManagerImpl;
      class  Texture;

      // =====================================================================
      // The texture manager class enables automatic resource sharing of 
      // textures.  Instead of creating textures directly, clients can use the 
      // texture manager to get a reference to the texture of interest and 
      // then release it when finished.
      // ===========================================================================
      class TextureManager
      {
      public:
         static TextureManager &Instance();

         ~TextureManager();

         void CacheIn();
         // loads all referenced textures into memory

         void CacheOut();
         // unloads all textures from memory

         void CollectGarbage();
         // Caches out all unreferenced textures

         Texture *AddReference(const std::string &filename);
         // Adds and obtains a reference to the texture corresponding to filename
         // All calls to AddReference must be matched by calss to Release

         void Release(const std::string &filename);
         // Releases a reference to a texture.

         int GetReferenceCount(const std::string &filename) const;
         // true if the Texture is currently cached in

      private:
         TextureManager();

         TextureManagerImpl *m_impl;
      };

   }  // end namespace GF1




//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
