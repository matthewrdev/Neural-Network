#ifndef _MEMORY_LEAK_H
#define _MEMORY_LEAK_H

//****************************************************************************
//**
//**    MemoryLeak.h
//**
//**    Copyright (c) 2009 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 12/2009 / 02/2010
//**
//****************************************************************************


// -------------------------------EXTREMELY IMPORTANT----------------------------------
// When including the file always include AFTER all windows, directx, GF1 etc structures.
// Failure to do so will result in errors appearing the associated header file and will
// make you flip out.

// Enable / disable memory leak checking
// Comment this block out to disable memory leak checking.
#ifndef _CHECK_MEM_LEAKS
#define _CHECK_MEM_LEAKS
#endif //#ifndef _CHECK_MEM_LEAKS

#ifdef _CHECK_MEM_LEAKS

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#endif // #ifdef _DEBUG
#endif // #ifdef _CHECK_MEM_LEAKS
#endif // #ifndef _MEMORY_LEAK_H