#ifndef _GAME_SETTINGS_H
#define _GAME_SETTINGS_H

//****************************************************************************
//**
//**    GameSettings.h
//**
//**    Copyright (c) 2010 CarDemo Studios
//**
//**    Author:  Matthew Robbins
//**    Created: 02/2010
//**
//****************************************************************************

namespace CarDemo
{
	class GameSettings
	{
	private:
		GameSettings()
		{	}
	public:
		int WORLD_WIDTH;
		int WORLD_HEIGHT;
		int WORLD_DEPTH;
		float WORLD_LEFT;
		float WORLD_RIGHT;
		float WORLD_TOP;
		float WORLD_BOTTOM;
		float WORLD_NEAR;
		float WORLD_FAR;
		int FRAME_RATE;

		void Init(int width, int height, int frameRate)
		{
			WORLD_WIDTH = width;
			WORLD_HEIGHT = height;
			WORLD_DEPTH = width;
			WORLD_LEFT = static_cast<float>(-WORLD_WIDTH / 2);
			WORLD_RIGHT = static_cast<float>(WORLD_WIDTH / 2);
			WORLD_TOP = static_cast<float>(WORLD_HEIGHT / 2);
			WORLD_BOTTOM = static_cast<float>(-WORLD_HEIGHT / 2);
			WORLD_NEAR = static_cast<float>(WORLD_DEPTH / 2);
			WORLD_FAR = static_cast<float>(-WORLD_DEPTH / 2);
			FRAME_RATE = frameRate;
		}

		~GameSettings()
		{	}

		static GameSettings& Instance()
		{
			static GameSettings instance;
			return instance;
		}
	};
	GameSettings* LoadSettingsFromFile(const char* fileName);

}; // End namespace CarDemo.

#define gSettings CarDemo::GameSettings::Instance()

#endif // #ifndef _GAME_SETTINGS_H