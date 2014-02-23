//****************************************************************************
//**
//**    GamerTimer.cpp
//**
//**    Copyright (c) 2009 CarDemo Studios
//**
//**    Author:  Matthew Robbins
//**    Created: 12/2009 - 02/2010
//**
//****************************************************************************

#include <windows.h>
#include <windowsx.h>

#include "GameTimer.h"

#include "MemoryLeak.h"

namespace CarDemo
{

	GameTimer::GameTimer()
	:	mSecondsPerCount (0.0f)
	,	mDeltaTime(-1.0f)
	,	mBaseTime(0)
	,	mPrevTime(0)
	,	mCurrTime(0)
	,   mAvSecsPerFrame(0)
	,   numFrames(0)
	,   timeElapsed(0.0f)
	{
		__int64 countsPerSec = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		mSecondsPerCount=1.0f/(double)countsPerSec;
	}

	void GameTimer::Tick()
	{
		//Get the current time for this frame
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mCurrTime=currTime;

		//calculate the delta between current frame and last frame in seconds
		mDeltaTime=(mCurrTime-mPrevTime)*mSecondsPerCount;

		//set the currnt frame time to previous to prep for next frame
		mPrevTime=mCurrTime;

		//Force nonnegative. The DXSDK's CDXUTTimer mentions that if the
		//processor goes into a power save mode or we get shuffled to 
		//another processor, then mDeltaTime can be negative
		if(mDeltaTime<0)
		{
			mDeltaTime=0;
		}

		timeElapsed += this->getDeltaTime();
		numFrames++;

		if (timeElapsed >= 1.0f)
		{
			this->FPS = numFrames;
			mAvSecsPerFrame = (timeElapsed / numFrames);
			numFrames = 0;
			timeElapsed = 0.0f;
		}
	}

	float GameTimer::GetSecsPerFrame() const
	{
		return (float)mAvSecsPerFrame;
	}

	float GameTimer::getDeltaTime() const
	{
		return (float)mDeltaTime;
	}

	float GameTimer::getGameTime() const
	{
		return(float)((mCurrTime-mPrevTime)*mSecondsPerCount);		
	}

	int GameTimer::GetFPS() const
	{
		return FPS;
	}


}; // End namespace CarDemo