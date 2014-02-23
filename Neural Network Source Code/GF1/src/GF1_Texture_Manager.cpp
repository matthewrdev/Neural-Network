//****************************************************************************
//**
//**    GF1_Texture_Manager.cpp
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_texture_manager.h"
#include "GF1_texture.h"
#include <string>

#pragma warning ( push )
#pragma warning( disable : 4702 )

#include <map>

#pragma warning ( pop )


   namespace GF1
   {
      namespace
      {
         struct TextureManagerRec
         {
            Texture *texture;
            int refCount;
         };

		 typedef std::map<std::string, TextureManagerRec> TextureManagerDB;
      }


      struct TextureManagerImpl
      {
         TextureManagerDB texdb;
      };


      TextureManager &TextureManager::Instance()
      {
         static TextureManager instance;
         return instance;
      }


      TextureManager::TextureManager()
      {
         m_impl = new TextureManagerImpl;
      }


      TextureManager::~TextureManager()
      {
         TextureManagerDB::iterator it;

         for (it = m_impl->texdb.begin(); it != m_impl->texdb.end(); it++)
         {
            delete it->second.texture;
         }

         delete m_impl;
      }



      void TextureManager::CacheIn()
      {
         TextureManagerDB::iterator it;

         for (it = m_impl->texdb.begin(); it != m_impl->texdb.end(); it++)
         {
            TextureManagerRec &rec = it->second;

            if (rec.refCount > 0)
            {
               rec.texture->CacheIn();
            }
         }
      }


      void TextureManager::CacheOut()
      {
         TextureManagerDB::iterator it;

         for (it = m_impl->texdb.begin(); it != m_impl->texdb.end(); it++)
         {
            TextureManagerRec &rec = it->second;

            if (rec.texture != NULL)
            {
               rec.texture->CacheOut();
            }
         }
      }


      void TextureManager::CollectGarbage()
      {
         TextureManagerDB::iterator it;

         for (it = m_impl->texdb.begin(); it != m_impl->texdb.end(); it++)
         {
            TextureManagerRec &rec = it->second;

            if (rec.texture != NULL && rec.refCount <= 0)
            {
               rec.texture->CacheOut();
            }
         }
      }


	  Texture *TextureManager::AddReference(const std::string &filename)
      {
         TextureManagerDB::iterator it;

         it = m_impl->texdb.begin();

         while (it != m_impl->texdb.end())
         {
            if (stricmp(it->second.texture->GetFileName().c_str(), filename.c_str()) == 0)
            {
               break;
            }

            it++;
         }

         Texture *resultTexture = NULL;

         if (it == m_impl->texdb.end())
         {
            // not found
            TextureManagerRec newRec;
            newRec.texture = new Texture(filename);
            newRec.refCount = 1;
            m_impl->texdb[filename] = newRec;
            resultTexture = newRec.texture;
         }
         else
         {
            (it->second.refCount)++;
            resultTexture = it->second.texture;
         }

         return resultTexture;
      }


      void TextureManager::Release(const std::string &filename)
      {
         TextureManagerDB::iterator it;

         it = m_impl->texdb.find(filename);

         if (it != m_impl->texdb.end())
         {
            (it->second.refCount)--;

            if (it->second.refCount < 0)
            {
               // ERROR - shouldn't happen
               it->second.refCount = 0;
            }
         }
         // else
         //    Attempt to release unreferenced texture
      }


      int TextureManager::GetReferenceCount(const std::string &filename) const
      {
         TextureManagerDB::iterator it;

         it = m_impl->texdb.find(filename);

         if (it == m_impl->texdb.end())
         {
            return 0;
         }
         else
         {
            return it->second.refCount;
         }
      }

   }  // end namespace GF1




//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
