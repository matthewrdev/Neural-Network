#ifndef _GAME_TIMER_H
#define _GAME_TIMER_H

//****************************************************************************
//**
//**    GameTimer.h
//**
//**    Copyright (c) 2009 CarDemo Studios
//**
//**    Author:  Matthew Robbins / Brendan Stemner
//**    Created: 12/2009 - 02/2010
//**
//****************************************************************************

namespace CarDemo
{
	class GameTimer
	{
	public:
		GameTimer();

		float getGameTime() const;	//returns game time in seconds
		float getDeltaTime() const;	//returns the change in time in seconds

		void Tick();

		int GetFPS() const;
		float GetSecsPerFrame() const;

	private:
		double mSecondsPerCount;
		double mDeltaTime;
		double mAvSecsPerFrame;

		int FPS;

		int numFrames;
		float timeElapsed;

		__int64 mBaseTime;
		__int64 mPrevTime;
		__int64 mCurrTime;
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _GAME_TIMER_H