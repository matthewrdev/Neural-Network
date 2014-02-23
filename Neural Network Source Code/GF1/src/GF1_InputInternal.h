#ifndef INPUT_INTERNAL_H
#define INPUT_INTERNAL_H
//****************************************************************************
//**
//**    GF1_InputInternal.h
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 08/12/2003
//**
//****************************************************************************

   namespace GF1
   {
      // ---------------------------------------------------------------------
      // InitKeys
      // ---------------------------------------------------------------------
      // Initialises the state of all the keys on the keyboard each frame as a
      // starting point to work out when keys are hit or lifted.  To be used 
      // internally, not by clients.
      // ---------------------------------------------------------------------
      GF1_API void InitKeys();


      // ---------------------------------------------------------------------
      // PollKeys
      // ---------------------------------------------------------------------
      // Reads the state of all the keys on the keyboard each frame to 
      // determine when keys are hit or lifted.  To be used internally, not by
      // clients.
      // ---------------------------------------------------------------------
      GF1_API void PollKeys();

   }  // end namespace GF1




//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
