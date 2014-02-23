#include <GF1.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "EditorInterface.h"
#include "GameTimer.h"
#include "GameGlobals.h"
#include "GameSettings.h"

#include "MemoryLeak.h"

using std::cout;
using std::endl;
using std::hex;

namespace CarDemo
{
	using namespace GF1;
	using namespace std;	 

	enum EditMode
	{
		POLYGON_INNER,
		POLYGON_OUTER,
		ADD_CHECKPOINT,

		EDIT_MODE_COUNT,
	};

	int mode = POLYGON_OUTER;
	int currentCheckpoint = -1;

	GF1::Sprite* pointSprite= NULL;

	GF1::Vector3 checkPointStart;
	GF1::Vector3 checkPointEnd;

	EditorInterface::EditorInterface()
		: drawFPS(true)
		, drawCollisionData(false)
	{

		checkPointStart.SetZero();
		checkPointEnd.SetZero();
		m_mouseOld.SetZero();
		m_font = new GF1::Sprite("Resources/TimesNewRomanWhite.png", 16, 16, 16*16, 1, false);

		m_timer = new GameTimer();
		m_timer->Tick();

		m_mouseCurrent.SetZero();
		m_gameOver = false;
		m_patternAlpha = 0.5f;
		m_patternAlphaForward = true;		

		background = new GF1::Sprite("Resources/raceTrackWBlackBacker.png", 800, 650,1,1,false);
		
		cursor = new GF1::Sprite("Resources/Cursor.png", 16, 16, 1, 1, false);
		cursor->SetBlendMode(Sprite::BLEND_MODE_TRANSPARENT);

		polygon = new TrackPolygon();

		pointSprite = new Sprite("Resources/PolyPointHighlighted.png", 8, 8, 1, 1, false);

		// Disable the windows cursor.
		ShowCursor(FALSE);
		
	}

	EditorInterface::~EditorInterface()
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
		if (polygon != NULL)
		{
		  delete polygon;
		  polygon = NULL;
		}
		if (background != NULL)
		{
		  delete background;
		  background = NULL;
		}
		if (cursor != NULL)
		{
		  delete cursor;
		  cursor = NULL;
		}
	}

	void EditorInterface::VerifySound(const Sound &s)
	{
		if (s.Bad())
		{
		cerr << "Error Loading Sound: " << s.GetFileName() << endl;
		m_gameOver = true;
		}
	}

	void EditorInterface::VerifySprite(const Sprite &s)
	{
		if (s.Bad())
		{
		cerr << "Error Loading Sprite: " << s.GetTextureName() << endl;
		m_gameOver = true;
		}
	}
	bool EditorInterface::IsOver() const
	{
		return m_gameOver;
	}


	void EditorInterface::GetCamera(
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


	void EditorInterface::Logic() 
	{
		m_timer->Tick();
		const float delta = m_timer->getDeltaTime();

		if (IsKeyDown(KEY_ESCAPE))
		{
			m_gameOver = true;
		}

		if (IsKeyHit(KEY_ENTER))
		{
			int result = MessageBox(0, "Are you sure you want to export the polygon?", 0, MB_YESNO | MB_ICONEXCLAMATION);
			if (result == IDYES)
			{
				polygon->ExportPolygon("Resources/polygon.txt");
				ExportCheckpoints();
			}
		}

		if (GF1::IsKeyHit(KEY_SPACE))
		{
			(int)mode++;
			if (mode >= EDIT_MODE_COUNT)
			{
				mode = POLYGON_INNER;
			}

			if (mode == POLYGON_INNER)
			{
				polygon->SwapMode(POLY_EDIT_INNER);
			}
			else if (mode == POLYGON_OUTER)
			{
				polygon->SwapMode(POLY_EDIT_OUTER);
			}
			else
			{
				polygon->SwapMode(POLY_NON_EDIT);
			}
		}

		if (GF1::IsKeyDown(KEY_LCONTROL) && GF1::IsKeyHit(KEY_Z))
		{
			if (mode != ADD_CHECKPOINT)
			{
				polygon->Undo();
			}
			else
			{
				checkpoints.pop_back();
			}
		}

		if (GF1::IsKeyHit(KEY_C))
		{
			if (mode != ADD_CHECKPOINT)
			{
				polygon->ClosePolygon(polygon->GetMode());
			}
		}

		if (GF1::IsKeyHit(KEY_UP))
		{
			if (mode != ADD_CHECKPOINT)
			{
				polygon->CycleUp();
			}
			else
			{
				if (currentCheckpoint >= 0)
				{
					currentCheckpoint++;
					if (currentCheckpoint >= this->checkpoints.size())
					{
						currentCheckpoint = 0;
					}
				}
			}
		}

		if (GF1::IsKeyHit(KEY_DOWN))
		{
			if (mode != ADD_CHECKPOINT)
			{
				polygon->CycleDown();
			}
			else
			{
				if (currentCheckpoint >= 0)
				{
					currentCheckpoint--;
					if (currentCheckpoint < 0)
					{
						currentCheckpoint = checkpoints.size() - 1;
					}
				}
			}
		}

		if (GF1::IsKeyHit(KEY_F))
		{
			if (mode != ADD_CHECKPOINT)
			{
				polygon->FlipNormal();
			}
		}

	}

	
	void EditorInterface::Render() 
	{
		
		background->Render();
		polygon->DrawTrack();
		// Render the checkpoints.
		for (unsigned int i = 0; i < checkpoints.size(); i++)
		{
			GF1::Vector3 start = ToGF1Vector(checkpoints[i].GetHead());
			GF1::Vector3 end = ToGF1Vector(checkpoints[i].GetTail());
			GF1::DrawLine(start, end, GF1::Colour::WHITE, false, 2.0f);
			pointSprite->SetPosition(start);
			pointSprite->Render();
			pointSprite->SetPosition(end);
			pointSprite->Render();
		}

		if (!checkPointStart.IsZero() && !checkPointEnd.IsZero())
		{
			GF1::DrawLine(checkPointStart, checkPointEnd, GF1::Colour::GREEN, false, 3);
		}

		DisplayFPS();

		static char buff[64] = {0};
		ZeroMemory(buff, sizeof(char) * 64);
		GF1::Vector3 printPos(static_cast<float>(-(gSettings.WORLD_WIDTH/2)),
						 static_cast<float>(-(gSettings.WORLD_HEIGHT/2)+32.0f),
						 0.0f);
		if (mode == POLYGON_INNER)
		{
			sprintf(buff, "Edit mode: Inner Polygon");
		}
		else if(mode == POLYGON_OUTER)
		{
			sprintf(buff, "Edit mode: Outer Polygon");
		}
		else
		{
			sprintf(buff, "Edit mode: Check point placment.");
		}
		GF1::print(m_font, printPos, buff);

		cursor->Render();

	}

	
	void EditorInterface::ExportCheckpoints()
	{
		std::ofstream file;
		file.open("Checkpoints.txt");

		file << "<Declaration>" << endl;
		file << "TotalCheckpoints=" << checkpoints.size() << endl;
		file << "-Build-" << endl;
		for (unsigned int i = 0; i < checkpoints.size(); i++)
		{
			file << "<Checkpoint>" << endl;
			file << "sX=" << checkpoints[i].GetHead().x << endl;
			file << "sY=" << checkpoints[i].GetHead().y << endl;
			file << "eX=" << checkpoints[i].GetTail().x << endl;
			file << "eY=" << checkpoints[i].GetTail().y << endl;
			file << "</Checkpoint>" << endl;
		}

		file << "</Declaration>" << endl;
	}

	void EditorInterface::DisplayFPS()
	{
		static char buff[512] = {0};
		ZeroMemory(buff, sizeof(char) * 512);
		GF1::Vector3 printPos(static_cast<float>(-(gSettings.WORLD_WIDTH/2)),
						 static_cast<float>(-(gSettings.WORLD_HEIGHT/2)+16.0f),
						 0.0f);
		sprintf(buff, "FPS:%i", m_timer->GetFPS());
		GF1::print(m_font, printPos, buff);

	}

	void EditorInterface::OnMouseEvent(MouseButton button, 
									 MouseEvent event,
									 int /* xPosWindow */, 
									 int /* yPosWindow */,
									 float xPosWorld, 
									 float yPosWorld)
	{
		static bool mouseDown = false;
		m_mouseCurrent.Set(xPosWorld, yPosWorld, 0);
		cursor->SetPosition(m_mouseCurrent);
		switch (event)
		{
		case MOUSE_EVENT_BUTTON_DOWN:
			switch (button)
			{
			case MOUSE_BUTTON_LEFT:
				mouseDown = true;
				if (mode != ADD_CHECKPOINT)
				{
					polygon->AddPoint(m_mouseCurrent);
				}
				else
				{
					checkPointStart = m_mouseCurrent;
					checkPointEnd = m_mouseCurrent;
				}
			   break;

			case MOUSE_BUTTON_RIGHT:
			   break;
			}
			break;

		case MOUSE_EVENT_BUTTON_UP:
			switch (button)
			{
			case MOUSE_BUTTON_LEFT:
				{
					mouseDown = false;

					if (mode == ADD_CHECKPOINT)
					{
						// Create a new checkpoint.
						Clarity::LineSegment2 cp(ToClarityVector(checkPointStart), ToClarityVector(checkPointEnd));
						checkpoints.push_back(cp);
					}
				}
			   break;
			}
			break;

		case MOUSE_EVENT_MOVE:
			if (mouseDown)
			{
				checkPointEnd = m_mouseCurrent;
			}
				
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
