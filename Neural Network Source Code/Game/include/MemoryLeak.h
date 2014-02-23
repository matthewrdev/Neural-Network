#ifndef _MEMORY_LEAK_H
#define _MEMORY_LEAK_H

//****************************************************************************
//**
//**    BE_MemoryLeak.h
//**
//**    Copyright (c) 2009 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 12/2009
//**
//****************************************************************************

// This file is to enable memory leak checking.

// Enable / disable memory leak checking
// Comment this block out to disable memory leak checking.
#ifndef _CHECK_MEM_LEAKS
#define _CHECK_MEM_LEAKS
#endif //#ifndef _CHECK_MEM_LEAKS

#ifdef _CHECK_MEM_LEAKS

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG

#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#endif // #ifdef _DEBUG

#endif // #ifdef _CHECK_MEM_LEAKS

#endif // #ifndef _MEMORY_LEAK_H