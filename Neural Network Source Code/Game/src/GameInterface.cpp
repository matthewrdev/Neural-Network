#include <GF1.h>
#include <iostream>
#include <iomanip>
#include <windows.h>

#include "GameInterface.h"
#include "GameTimer.h"
#include "GameSettings.h"
#include "Agent.h"
#include "GameGlobals.h"
#include "EntityManager.h"

#include <Clarity/Math/Math.h>
#include <Clarity/Math/LineSegment2.h>

#include "MemoryLeak.h"


using std::cout;
using std::endl;
using std::hex;

const float minGameScaling = 0.3f;
const float maxGameScaling = 12.50f;
float gameTimeScaling = 1.0f;

namespace CarDemo
{
	using namespace GF1;
	using namespace std;	 

	GameInterface::GameInterface()
		: drawFPS(true)
		, background(NULL)
	{
		m_mouseOld.SetZero();
		m_font = new GF1::Sprite("Resources/TimesNewRomanWhite.png", 16, 16, 16*16, 1, false);

		m_timer = new GameTimer();
		m_timer->Tick();

		m_mouseCurrent.SetZero();
		m_gameOver = false;

		background = new GF1::Sprite("Resources/raceTrackWBlackBacker.png", 800, 650,1,1,false);

		polygon = new TrackPolygon();
		polygon->LoadPolygon("Resources/Track1Polygon.txt");

		entityManager = new EntityManager();
		entityManager->LoadCheckPoints("Resources/Track1Checkpoints.txt");
	}

	GameInterface::~GameInterface()
	{

		if (m_font != NULL)
		{
		  delete m_font;
		  m_font = NULL;
		}

		if (m_timer != NULL)
		{
		  delete m_timer;
		  m_timer = NULL;
		}

		if (background != NULL)
		{
			delete background;
			background = NULL;
		}

		if (polygon != NULL)
		{
			delete polygon;
			polygon = NULL;
		}

		if (entityManager != NULL)
		{
			delete entityManager;
			entityManager = NULL;
		}
	}

	bool GameInterface::IsOver() const
	{
		return m_gameOver;
	}

	void GameInterface::GetCamera(
	float &left,   float &right, 
	float &bottom, float &top,
	float &zNear,  float &zFar) const
	{
		left   = gSettings.WORLD_LEFT;
		right  = gSettings.WORLD_RIGHT;
		top    = gSettings.WORLD_TOP;
		bottom = gSettings.WORLD_BOTTOM;
		zNear  = gSettings.WORLD_NEAR;
		zFar   = gSettings.WORLD_FAR;
	}


	void GameInterface::Logic() 
	{
		m_timer->Tick();
		const float delta = Clamp(m_timer->getDeltaTime(), 0.001f, MAX_FRAME_DELTA);

		if (IsKeyDown(KEY_ESCAPE))
		{
			m_gameOver = true;
		}

		if (IsKeyHit(KEY_R))
		{
			RestartSimulation();
		}
		else
		{
			if (IsKeyHit(KEY_SPACE))
			{
				entityManager->ForceToNextAgent();
			}
			// Test the cars feelers to the track polygon.
			entityManager->Update(delta * gameTimeScaling);
			std::vector<Clarity::LineSegment2> polygons;
			polygon->QueryPossibleCollisions(entityManager->GetAgentSensorBounds(), polygons);
			entityManager->TestAgentToPolySections(polygons);
			entityManager->Update(delta * gameTimeScaling);
		}
	}

	void GameInterface::RestartSimulation()
	{
		if (entityManager != NULL)
		{
			delete entityManager;
			entityManager = NULL;
		}

		entityManager = new EntityManager();
		entityManager->LoadCheckPoints("Resources/Track1Checkpoints.txt");
	}

	
	void GameInterface::Render() 
	{
		background->Render();
		entityManager->Render();
		polygon->DrawTrack();
		entityManager->RenderStatistics();
		polygon->DrawIntersectingPolySections();
		UpdateAndDisplaySimulationScaling(m_timer->getDeltaTime());

		if (drawFPS)
		{
			DisplayFPS();
		}
	}

	void GameInterface::DisplayFPS()
	{
		static char buff[512] = {0};
		ZeroMemory(buff, sizeof(char) * 512);
		GF1::Vector3 printPos(static_cast<float>(-(gSettings.WORLD_WIDTH/2)),
						 static_cast<float>(-(gSettings.WORLD_HEIGHT/2)+16.0f),
						 0.0f);
		sprintf(buff, "FPS:%i", m_timer->GetFPS());
		GF1::print(m_font, printPos, buff);

	}

	void GameInterface::UpdateAndDisplaySimulationScaling(float delta)
	{
		GF1::Vector3 printPos(static_cast<float>(-(gSettings.WORLD_WIDTH/2) + 250.0f),
						 static_cast<float>(-(gSettings.WORLD_HEIGHT/2)+16.0f),
						 0.0f);

		// Check for input.
		if (GF1::IsKeyDown(GF1::KEY_UP))
		{
			gameTimeScaling += 1.0f * delta;
		}
		if (GF1::IsKeyDown(GF1::KEY_DOWN))
		{
			gameTimeScaling -= 1.0f * delta;
		}

		if (gameTimeScaling < minGameScaling)
			gameTimeScaling = minGameScaling;

		if (gameTimeScaling > maxGameScaling)
			gameTimeScaling = maxGameScaling;

		char buff[512] = {0};
		ZeroMemory(buff, sizeof(char) * 512);
		sprintf(buff, "Time Scale :%f", gameTimeScaling);
		GF1::print(m_font, printPos, buff);

	}

	void GameInterface::OnMouseEvent(MouseButton button, 
									 MouseEvent event,
									 int /* xPosWindow */, 
									 int /* yPosWindow */,
									 float xPosWorld, 
									 float yPosWorld)
	{
		m_mouseCurrent.Set(xPosWorld, yPosWorld, 0);
		switch (event)
		{
		case MOUSE_EVENT_BUTTON_DOWN:
			switch (button)
			{
			case MOUSE_BUTTON_LEFT:
			   break;

			case MOUSE_BUTTON_RIGHT:
			   break;
			}
			break;

		case MOUSE_EVENT_BUTTON_UP:
			switch (button)
			{
			case MOUSE_BUTTON_LEFT:
			   break;
			}
			break;

		case MOUSE_EVENT_MOVE:
			break;

		case MOUSE_EVENT_BUTTON_DOUBLE_CLICK:
			switch (button)
			{
			case MOUSE_BUTTON_LEFT:
			   break;

			case MOUSE_BUTTON_RIGHT:
			   break;

			case MOUSE_BUTTON_MIDDLE:
			   break;
			}
			break;

		case MOUSE_EVENT_HOVER:
			break;
		}
		m_mouseOld.Set(m_mouseCurrent.x, m_mouseCurrent.y, 0);
	}



}  // end namespace CarDemo

//****************************************************************************
//**
//**    END IMPLEMENTATION
//**
//****************************************************************************
