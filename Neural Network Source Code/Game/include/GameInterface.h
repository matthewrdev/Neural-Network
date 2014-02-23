#ifndef _GAME_INTERFACE_H
#define _GAME_INTERFACE_H

//****************************************************************************
//**
//**    GameInterface.h
//**
//**    Copyright (c) 2010 CarDemo Studios
//**
//**    Author:  Matthew Robbins / Brendan Stemner / Hayley Wallace
//**    Created: 02/2010
//**       
//**
//****************************************************************************

#include <vector>

#include <GF1_IGame.h>
#include <GF1_Input.h>
#include <GF1_Vector3.h>
#include <GF1_Colour.h>

#include "GameTimer.h"
#include "GameSettings.h"
#include "TrackPolygon.h"


namespace CarDemo
{
	class Agent;
	class EntityManager;

	class GameInterface : public GF1::IGame
	{
	private:
		 GF1::Sprite* m_font;

         GF1::Vector3 m_mouseOld;
		 GF1::Vector3 m_mouseCurrent;
		 GF1::Vector3 m_delta;

		 bool m_gameOver;
		 bool drawFPS;
		 GameTimer* m_timer;
		 GF1::Sprite* background;

		 EntityManager* entityManager;
		 TrackPolygon* polygon;

		 void DisplayFPS();
		 void UpdateAndDisplaySimulationScaling(float delta);

		 void RestartSimulation();

	protected:
	public:
         GameInterface();
         ~GameInterface();

         void GetCamera(float &left,   
				       float &right, 
					   float &bottom,
					   float &top,
					   float &zNear,
					   float &zFar) const;

         bool IsOver() const;
         void Logic();
         void Render();

         void OnMouseEvent(GF1::MouseButton button, 
						   GF1::MouseEvent event,
						   int xPosWindow, 
						   int yPosWindow,
						   float xPosWorld,
						   float yPosWorld);




	};
	
}; // End namespace Beatup.

#endif // #ifndef _GAME_INTERFACE_H