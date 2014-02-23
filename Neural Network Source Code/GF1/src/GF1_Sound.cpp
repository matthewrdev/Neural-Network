//****************************************************************************
//**
//**    GF1_Sound.cpp
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 18/11/2003
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Sound.h"
#include <fmod.h>

#include <iostream>
using namespace std;

   namespace GF1
   {
      struct SoundImpl
      {
         char fileName[MAX_PATH];
         FSOUND_SAMPLE *sample;
         int channel;
         int frequency;
         bool paused;
         bool looped;

         bool streamed;
         FSOUND_STREAM *stream;
      };

      const int Sound::MIN_FREQUENCY = 100;
      const int Sound::MAX_FREQUENCY = 705600;

      Sound::Sound(const char *sampleFileName, bool streamed)
      {
         m_impl = new SoundImpl;

         strncpy(m_impl->fileName, sampleFileName, MAX_PATH);
         m_impl->fileName[MAX_PATH] = '\0';

         m_impl->streamed = streamed;

         if (m_impl->streamed)
         {
            m_impl->stream = FSOUND_Stream_Open(m_impl->fileName, 
               FSOUND_NORMAL | 0, 0, 0);
            m_impl->sample = FSOUND_Stream_GetSample(m_impl->stream);
         }
         else
         {
            m_impl->sample = FSOUND_Sample_Load(FSOUND_FREE, 
               m_impl->fileName, FSOUND_NORMAL, 0, 0);
         }

         // Initially the channel is invalid (-1)
         m_impl->channel = -1;

         FSOUND_Sample_GetDefaults(m_impl->sample,
            &(m_impl->frequency), NULL, NULL, NULL);

         m_impl->paused = false;
         m_impl->looped = false;

         SetLooped(m_impl->looped);
      }


      Sound::Sound(const Sound &rhs)
      {
         m_impl = new SoundImpl;

         *m_impl = *(rhs.m_impl);

         if (m_impl->streamed)
         {
            m_impl->stream = FSOUND_Stream_Open(m_impl->fileName, 
               FSOUND_NORMAL | 0, 0, 0);
            m_impl->sample = FSOUND_Stream_GetSample(m_impl->stream);
         }
         else
         {
            m_impl->sample = FSOUND_Sample_Load(FSOUND_FREE, 
               m_impl->fileName, FSOUND_NORMAL, 0, 0);
         }

         // Initially the channel is invalid (-1)
         m_impl->channel = -1;

         FSOUND_Sample_GetDefaults(m_impl->sample,
            &(m_impl->frequency), NULL, NULL, NULL);

         SetLooped(m_impl->looped);
      }


      Sound::~Sound()
      {
         if (!Bad())
         {
            if (m_impl->streamed)
            {
               FSOUND_Stream_Close(m_impl->stream);
            }
            else
            {
               FSOUND_Sample_Free(m_impl->sample);
            }
         }

         delete m_impl;
      }

      
      bool Sound::Bad() const
      {
         return (m_impl->sample == NULL);
      }


      const char *Sound::GetFileName() const
      {
         return m_impl->fileName;
      }


      bool Sound::IsPlaying() const
      {
         return (FSOUND_IsPlaying(m_impl->channel) != FALSE);
      }


      bool Sound::IsLooped() const
      {
         return m_impl->looped;
      }


      bool Sound::IsStreaming() const
      {
         return m_impl->streamed;
      }


      bool Sound::IsPaused() const
      {
         return m_impl->paused;
      }


      int Sound::GetFrequency() const
      {
         return m_impl->frequency;
      }


      void Sound::Play()
      {
         if (!IsPlaying())
         {
            if (m_impl->streamed)
            {
               m_impl->channel = FSOUND_Stream_Play(FSOUND_FREE, 
                  m_impl->stream);
            }
            else
            {
               m_impl->channel = FSOUND_PlaySound(FSOUND_FREE, 
                  m_impl->sample);
            }

            FSOUND_SetFrequency(m_impl->channel, m_impl->frequency);

            if (m_impl->paused)
            {
               FSOUND_SetPaused(m_impl->channel, TRUE);
            }
            else
            {
               FSOUND_SetPaused(m_impl->channel, FALSE);
            }
         }
      }


      void Sound::Stop()
      {
         if (m_impl->channel != -1)
         {
            if (m_impl->streamed)
            {
               FSOUND_Stream_Stop(m_impl->stream);
            }
            else
            {
               FSOUND_StopSound(m_impl->channel);
            }

            m_impl->channel = -1;
         }
      }
   

      void Sound::Pause(bool pause)
      {
         if (pause)
         {
            if (!m_impl->paused)
            {
               FSOUND_SetPaused(m_impl->channel, TRUE);
               m_impl->paused = true;
            }
         }
         else
         {
            if (m_impl->paused)
            {
               FSOUND_SetPaused(m_impl->channel, FALSE);
               m_impl->paused = false;
            }
         }
      }
      

      void Sound::SetLooped(bool looped)
      {
         if (m_impl->streamed)
         {
            if (looped)
            {
               FSOUND_Stream_SetLoopCount(m_impl->stream, -1);
            }
            else
            {
               FSOUND_Stream_SetLoopCount(m_impl->stream, 1);
            }
         }
         else
         {
            if (looped)
            {
               FSOUND_Sample_SetMode(m_impl->sample, FSOUND_LOOP_NORMAL);
            }
            else
            {
               FSOUND_Sample_SetMode(m_impl->sample, FSOUND_LOOP_OFF);
            }
         }
      }


      void Sound::SetFrequency(int frequency)
      {
         assert(frequency >= MIN_FREQUENCY && frequency <= MAX_FREQUENCY);
         m_impl->frequency = frequency;

         if (IsPlaying())
         {
            FSOUND_SetFrequency(m_impl->channel, m_impl->frequency);
         }
      }


   }  // end namespace GF1



//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
