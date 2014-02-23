#ifndef _EDITOR_INTERFACE_H
#define _EDITOR_INTERFACE_H

//****************************************************************************
//**
//**    EditorInterface.h
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

#include <Clarity/Math/LineSegment2.h>


namespace CarDemo
{
	class EditorInterface : public GF1::IGame
	{
	private:
		bool drawCollisionData;
		 GF1::Sprite* m_font;
		 GF1::Sprite* imageSource;
		 GF1::Sprite* imageDest;

         GF1::Vector3 m_mouseOld;
		 GF1::Vector3 m_mouseCurrent;
		 GF1::Vector3 m_delta;

		 bool m_gameOver;
         float m_patternAlpha;
         bool m_patternAlphaForward;
		 bool drawFPS;
		 GameTimer* m_timer;
		 GameSettings* m_settings;
		 GF1::Sprite* background;
		 GF1::Sprite* cursor;

		 TrackPolygon* polygon;
		 std::vector<Clarity::LineSegment2> checkpoints;

         void VerifySprite(const GF1::Sprite &s);
         void VerifySound(const GF1::Sound &s);

		 void DisplayFPS();

		 void ExportCheckpoints();

	protected:
	public:
         EditorInterface();
         ~EditorInterface();

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

#endif // #ifndef _EDITOR_INTERFACE_H