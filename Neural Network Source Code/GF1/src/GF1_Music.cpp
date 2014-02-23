//****************************************************************************
//**
//**    GF1_Music.cpp
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 28/11/2003
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Music.h"
#include <fmod.h>

#include <iostream>
using namespace std;

   namespace GF1
   {
      struct MusicImpl
      {
         char fileName[MAX_PATH];
         FMUSIC_MODULE *module;
         bool paused;
         bool looped;
      };

      Music::Music(const char *fileName)
      {
         m_impl = new MusicImpl;

         strncpy(m_impl->fileName, fileName, MAX_PATH);
         m_impl->fileName[MAX_PATH] = '\0';

         m_impl->module = FMUSIC_LoadSong(m_impl->fileName);
         m_impl->paused = false;
         m_impl->looped = false;
         SetLooped(m_impl->looped);
      }


      Music::Music(const Music &rhs)
      {
         m_impl = new MusicImpl;

         *m_impl = *(rhs.m_impl);

         m_impl->module = FMUSIC_LoadSong(m_impl->fileName);
         SetLooped(m_impl->looped);
      }


      Music::~Music()
      {
         if (!Bad())
         {
            FMUSIC_FreeSong(m_impl->module);
         }

         delete m_impl;
      }

      
      bool Music::Bad() const
      {
         return (m_impl->module == NULL);
      }


      const char *Music::GetFileName() const
      {
         return m_impl->fileName;
      }


      bool Music::IsPlaying() const
      {
         return (FMUSIC_IsPlaying(m_impl->module) != FALSE);
      }


      bool Music::IsLooped() const
      {
         return m_impl->looped;
      }


      bool Music::IsPaused() const
      {
         return m_impl->paused;
      }


      void Music::Play()
      {
         if (!IsPlaying())
         {
            FMUSIC_PlaySong(m_impl->module);

            if (m_impl->paused)
            {
               FMUSIC_SetPaused(m_impl->module, TRUE);
            }
            else
            {
               FMUSIC_SetPaused(m_impl->module, FALSE);
            }
         }
      }


      void Music::Stop()
      {
         if (IsPlaying())
         {
            FMUSIC_StopSong(m_impl->module);
         }
      }
   

      void Music::Pause(bool pause)
      {
         if (pause)
         {
            if (!m_impl->paused)
            {
               FMUSIC_SetPaused(m_impl->module, TRUE);
               m_impl->paused = true;
            }
         }
         else
         {
            if (m_impl->paused)
            {
               FMUSIC_SetPaused(m_impl->module, FALSE);
               m_impl->paused = false;
            }
         }
      }
      

      void Music::SetLooped(bool looped)
      {

         if (looped)
         {
            FMUSIC_SetLooping(m_impl->module, TRUE);
         }
         else
         {
            FMUSIC_SetLooping(m_impl->module, FALSE);
         }

         m_impl->looped = looped;
      }


   }  // end namespace GF1




//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
