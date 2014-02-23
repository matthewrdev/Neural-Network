//****************************************************************************
//**
//**    TrackPolygon.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <cmath>
#include <windows.h>

#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "TrackPolygon.h"
#include "GameGlobals.h"

#include <GF1_Sprite.h>
#include <GF1_Colour.h>
#include <GF1_Graphics.h>

#include <Clarity/Math/Circle.h>
#include <Clarity/Math/Math.h>

#include "MemoryLeak.h"

using GF1::Sprite;

using std::ofstream;
using std::cout;
using std::endl;


namespace CarDemo 
{		
	enum PolygonReadMode
	{
		PolyInner,
		PolyOuter,
		PolyInvalid,
	};

	const int INVALID_POLY_SECTION = -1;

	TrackPolygon::TrackPolygon()
	{
		currentSectionInner = INVALID_POLY_SECTION;
		currentSectionOuter = INVALID_POLY_SECTION;

		mode = CarDemo::POLY_EDIT_OUTER;

		drawNormals = true;

		pointSprite = new Sprite("Resources/PolyPoint.png", 8, 8, 1, 1, false);
		pointSpriteHighlight = new Sprite("Resources/PolyPointHighlighted.png", 8, 8, 1, 1, false);
	}

	TrackPolygon::~TrackPolygon()
	{
		if (pointSprite != NULL)
		{
			delete pointSprite;
			pointSprite = NULL;
		}

		if (pointSpriteHighlight != NULL)
		{
			delete pointSpriteHighlight;
			pointSpriteHighlight = NULL;
		}
	}
	
	void TrackPolygon::LoadPolygon(char* filename)
	{
		FILE* file = fopen(filename,"rt");
		int tempID = 0;

		if(file!=NULL)
		{
			PolygonReadMode mode = PolyInvalid;

			Clarity::Vector2 normal;
			Clarity::Vector2 start;
			Clarity::Vector2 end;

			char buffer[1024] ={0};

			while(fgets(buffer,1024,file))
			{
				char buff[1024] = {0};

				if(buffer[strlen(buffer)-1] == '\n')
				{
					for(unsigned int i = 0; i<strlen(buffer)-1;i++)
					{
						buff[i] = buffer[i];
					}
				}

				if(0 == strcmp(buff, "<PolyInner>"))
				{
					// Set mode to inner polygon loading.
					mode = PolyInner;
				}
				else if (0 == strcmp(buff,"</PolyInner>"))
				{
					// Do nothing, just there for structure.
				}
				else if (0 == strcmp(buff,"<PolyOuter>"))
				{
					// Set mode to outer polygon loading.
					mode = PolyOuter;
				}
				else if (0 == strcmp(buff,"</PolyOuter>"))
				{
					// Do nothing, just there for structure.
				}
				else if (0 == strcmp(buff,"<Segment>"))
				{
					// Clear segment data.
					start.Set(0.0f, 0.0f);
					end.Set(0.0f, 0.0f);
					normal.Set(0.0f, 0.0f);
				}
				else if (0 == strcmp(buff,"</Segment>"))
				{
					// Create segment data
					PolySection ps;
					ps.section.Set(end, start);
					switch (mode)
					{
					case PolyInner:
						polygonInner.push_back(ps);
						break;
					case PolyOuter:
						polygonOuter.push_back(ps);
						break;
					};
				}
			
				else
				{
					char* token = strtok(buff, "=");

					if (token != NULL)
					{
						char* value = strtok(NULL,"=");


						if (0 == strcmp(token,"sX"))
						{
							start.x = (float)atof(value);
						}
						else if (0 == strcmp(token,"sY"))
						{
							start.y = (float)atof(value);
						}
						else if (0 == strcmp(token,"eX"))
						{
							end.x = (float)atof(value);
						}
						else if (0 == strcmp(token,"eY"))
						{
							end.y = (float)atof(value);
						}
						else if (0 == strcmp(token,"nX"))
						{
							normal.x = (float)atof(value);
						}
						else if (0 == strcmp(token,"nY"))
						{
							normal.y = (float)atof(value);
						}
					}
				}
			}
			fclose(file);
		}
	}

	void TrackPolygon::ExportPolygon(char* filename)
	{
		std::ofstream file;
		file.open(filename);

		file << "<PolyInner>" << endl;
		for (unsigned int i = 0; i < polygonInner.size(); i++)
		{
			file << "<Segment>" << endl;
			file << "sX=" << polygonInner[i].section.GetHead().x << endl;
			file << "sY=" << polygonInner[i].section.GetHead().y << endl;
			file << "eX=" << polygonInner[i].section.GetTail().x << endl;
			file << "eY=" << polygonInner[i].section.GetTail().y << endl;
			file << "nX=" << polygonInner[i].normal.x << endl;
			file << "nY=" << polygonInner[i].normal.y << endl;
			file << "</Segment>" << endl;
		}
		file << "</PolyInner>" << endl;

		file << "<PolyOuter>" << endl;
		for (unsigned int i = 0; i < polygonOuter.size(); i++)
		{
			file << "<Segment>" << endl;
			file << "sX=" << polygonOuter[i].section.GetHead().x << endl;
			file << "sY=" << polygonOuter[i].section.GetHead().y << endl;
			file << "eX=" << polygonOuter[i].section.GetTail().x << endl;
			file << "eY=" << polygonOuter[i].section.GetTail().y << endl;
			file << "nX=" << polygonOuter[i].normal.x << endl;
			file << "nY=" << polygonOuter[i].normal.y << endl;
			file << "</Segment>" << endl;
		}
		file << "</PolyOuter>" << endl;

		file.close();
	}

	void TrackPolygon::BuildSection(Clarity::Vector2 start, Clarity::Vector2 end)
	{
		PolySection polySection;
		polySection.section.Set(start, end);

		// Calculate the normal value.
		polySection.normal = polySection.section.GetNormal();

		// Create a poly section that joins the final point to the start point.
		switch (mode)
		{
		case POLY_EDIT_INNER:
			{
				polygonInner.push_back(polySection);
				currentSectionInner = polygonInner.size() - 1;
			}
			break;
		case POLY_EDIT_OUTER:
			{
				polygonOuter.push_back(polySection);
				currentSectionOuter = polygonOuter.size() - 1;
			}
			break;
		default:
			break;
		};

	}

	void TrackPolygon::DrawTrack()
	{
		// Draw the points that represent the vertices.
		for (unsigned int i = 0; i < pointsInner.size(); i++)
		{
			pointSprite->SetPosition(pointsInner[i]);
			pointSprite->Render();
		}
		for (unsigned int i = 0; i < pointsOuter.size(); i++)
		{
			pointSprite->SetPosition(pointsOuter[i]);
			pointSprite->Render();
		}

		// Draw the selection highlights
		switch (this->mode)
		{
		case POLY_EDIT_INNER:
			{
				if (currentSectionInner != INVALID_POLY_SECTION)
				{
					GF1::Vector3 s = ToGF1Vector(this->polygonInner[this->currentSectionInner].section.GetHead());
					GF1::Vector3 e = ToGF1Vector(this->polygonInner[this->currentSectionInner].section.GetTail());

					GF1::DrawCircle(s, 10.0f, GF1::Colour::YELLOW, false, 2);
					GF1::DrawCircle(e, 10.0f, GF1::Colour::YELLOW, false, 2);
				}
			}
			break;
		case POLY_EDIT_OUTER:
			{
				if (currentSectionOuter != INVALID_POLY_SECTION)
				{
					GF1::Vector3 s = ToGF1Vector(this->polygonOuter[this->currentSectionOuter].section.GetHead());
					GF1::Vector3 e = ToGF1Vector(this->polygonOuter[this->currentSectionOuter].section.GetTail());
					
					GF1::DrawCircle(s, 10.0f, GF1::Colour::YELLOW, false, 2);
					GF1::DrawCircle(e, 10.0f, GF1::Colour::YELLOW, false, 2);
				}
			}
			break;
		default:
			break;
		};

		// Draw the lines for the inner polygon.
		for (unsigned int i = 0; i < polygonInner.size(); i++)
		{
			GF1::DrawLine(ToGF1Vector(polygonInner[i].section.GetHead()),
									  ToGF1Vector(polygonInner[i].section.GetTail()),
									  GF1::Colour::BLACK, false, 3.0f);

			pointSprite->SetPosition(ToGF1Vector(polygonInner[i].section.GetHead()));
			pointSprite->Render();


		}

		
		if (polygonInner.size() > 0)
		{
			pointSprite->SetPosition(ToGF1Vector(polygonInner[polygonInner.size() - 1].section.GetTail()));
			pointSprite->Render();
		}

		// Draw the lines for the outer polygon.
		for (unsigned int i = 0; i < polygonOuter.size(); i++)
		{
			GF1::DrawLine(ToGF1Vector(polygonOuter[i].section.GetHead()),
									  ToGF1Vector(polygonOuter[i].section.GetTail()),
									  GF1::Colour::BLACK, false, 3.0f);
			pointSprite->SetPosition(ToGF1Vector(polygonOuter[i].section.GetHead()));
			pointSprite->Render();
		}

		if (polygonOuter.size() > 0)
		{
			pointSprite->SetPosition(ToGF1Vector(polygonOuter[polygonOuter.size() - 1].section.GetTail()));
			pointSprite->Render();
		}

		if (drawNormals)
		{
			DrawPolySegmentNormals();
		}
	}

	void TrackPolygon::DrawPolySegmentNormals()
	{
		GF1::Vector3 start;
		GF1::Vector3 end;
		// Calculate the positions for the segment normals.
		for (unsigned int i = 0; i < polygonInner.size(); i++)
		{ 
			start = ToGF1Vector(polygonInner[i].section.Midpoint());
			end = start + (ToGF1Vector(polygonInner[i].normal) * 5.0f);
			GF1::DrawLine(start, end,
				GF1::Colour::RED, false, 3.0f);
		}

		// Calculate the positions for the segment normals.
		for (unsigned int i = 0; i < polygonOuter.size(); i++)
		{ 
			start = ToGF1Vector(polygonOuter[i].section.Midpoint());
			end = start + (ToGF1Vector(polygonOuter[i].normal) * 5.0f);
			GF1::DrawLine(start, end,
				GF1::Colour::RED, false, 3.0f);
		}
	}

	void TrackPolygon::DrawIntersectingPolySections()
	{
		GF1::Vector3 start;
		GF1::Vector3 end;
		if (intersectingInner.size() > 0)
		{
			for (unsigned int i = 0; i < intersectingInner.size(); i++)
			{
				start = ToGF1Vector(polygonInner[intersectingInner[i]].section.GetHead());
				end = ToGF1Vector(polygonInner[intersectingInner[i]].section.GetTail());
				GF1::DrawLine(start,  end,  GF1::Colour::ORANGE, false, 1.0f);
			}
		}

		if (intersectingOuter.size() > 0)
		{
			for (unsigned int i = 0; i < intersectingOuter.size(); i++)
			{
				start = ToGF1Vector(polygonOuter[intersectingOuter[i]].section.GetHead());
				end = ToGF1Vector(polygonOuter[intersectingOuter[i]].section.GetTail());
				GF1::DrawLine(start, end, GF1::Colour::ORANGE, false, 1.0f);
			}
		}

		intersectingInner.clear();
		intersectingOuter.clear();
	}



	// Editor options.
	void TrackPolygon::AddPoint(GF1::Vector3 point)
	{
		switch (this->mode)
		{
		case POLY_EDIT_INNER:
			pointsInner.push_back(point);
			if (pointsInner.size() > 1)
			{
				BuildSection(ToClarityVector(pointsInner[pointsInner.size() - 2]),
							 ToClarityVector(pointsInner[pointsInner.size() - 1]));
			}
			break;
		case POLY_EDIT_OUTER:
			pointsOuter.push_back(point);
			if (pointsOuter.size() > 1)
			{
				BuildSection(ToClarityVector(pointsOuter[pointsOuter.size() - 2]), 
							 ToClarityVector(pointsOuter[pointsOuter.size() - 1]));
			}
			break;
		default:
			break;
		};
	}

	void TrackPolygon::FlipNormal()
	{
		switch (mode)
		{
		case POLY_EDIT_INNER:
			polygonInner[this->currentSectionInner].normal *= -1;
			break;
		case POLY_EDIT_OUTER:
			polygonOuter[currentSectionOuter].normal *= -1;
			break;
		default:
			break;
		};
	}
	
	void TrackPolygon::SwapMode(PolyMode mode)
	{
		this->mode = mode;
	}

	void TrackPolygon::CycleUp()
	{
		switch (mode)
		{
		case POLY_EDIT_INNER:
			{
				currentSectionInner++;
				if (currentSectionInner >= polygonInner.size())
					currentSectionInner = 0;
			}
			break;
		case POLY_EDIT_OUTER:
			{
				currentSectionOuter++;
				if (currentSectionOuter >= polygonOuter.size())
					currentSectionOuter = 0;
			}
			break;
		default:
			break;
		};

	}

	void TrackPolygon::CycleDown()
	{
		switch (mode)
		{
		case POLY_EDIT_INNER:
			{
				currentSectionInner--;
				if (currentSectionInner < 0)
					currentSectionInner = polygonInner.size() - 1;
			}
			break;
		case POLY_EDIT_OUTER:
			{
				currentSectionOuter--;
				if (currentSectionOuter < 0)
					currentSectionOuter = polygonOuter.size() - 1;
			}
			break;
		default:
			break;
		};

	}


	void TrackPolygon::ClosePolygon(PolyMode poly)
	{
		// Create a poly section that joins the final point to the start point.
		switch (poly)
		{
		case POLY_EDIT_INNER:
			{
				BuildSection(ToClarityVector(pointsInner[0]), ToClarityVector(pointsInner[pointsInner.size() - 1]));
			}
			break;
		case POLY_EDIT_OUTER:
			{
				BuildSection(ToClarityVector(pointsOuter[0]), ToClarityVector(pointsOuter[pointsOuter.size() - 1]));
			}
			break;
		default:
			break;
		};
	}

	
	PolyMode TrackPolygon::GetMode()
	{
		return mode;
	}
	
	void TrackPolygon::Undo()
	{
		switch (this->mode)
		{
		case POLY_EDIT_INNER:
			{
				if (polygonInner.size() > 0)
				{
					pointsInner.pop_back();
					polygonInner.pop_back();
					currentSectionInner--;
					if (polygonInner.size() == 0)
					{
						currentSectionInner = INVALID_POLY_SECTION;
					}
				}
			}
			break;
		case POLY_EDIT_OUTER:
			{
				if (polygonOuter.size() > 0)
				{
					pointsOuter.pop_back();
					polygonOuter.pop_back();
					currentSectionOuter--;
					if (polygonOuter.size() == 0)
					{
						currentSectionOuter = INVALID_POLY_SECTION;
					}
				}
			}
			break;
		default:
			break;
		};
	}
	
	void TrackPolygon::ToggleNormalRendering()
	{
		drawNormals = !drawNormals;
	}

	bool TrackPolygon::IsDrawingNormals() const
	{
		return drawNormals;
	}

	void TrackPolygon::QueryPossibleCollisions(const Clarity::Circle& circle, std::vector<Clarity::LineSegment2> &out)
	{
		// Ray to test intersections against the circle.
		Clarity::Ray2 ray(Clarity::Vector2::ZERO, Clarity::Vector2::UNIT_X);
		Clarity::Ray2 ray2(Clarity::Vector2::ZERO, Clarity::Vector2::UNIT_X);
		float distance = 0; // Unused, needed so that the function will work.

		// Test inner polygon sections to the circle.
		for (unsigned int i = 0; i < polygonInner.size(); i++)
		{
			ray.Set(polygonInner[i].section.GetTail(), polygonInner[i].section.GetDirection());
			ray2.Set(polygonInner[i].section.GetHead(), polygonInner[i].section.GetDirection() * -1);
			if (Clarity::Intersects(circle, ray, &distance) && Clarity::Intersects(circle, ray2, &distance))
			{
				out.push_back(polygonInner[i].section);
				intersectingInner.push_back(i);
				continue;
			}

		}

		// Test outer polygon sections to the circle.
		for (unsigned int i = 0; i < polygonOuter.size(); i++)
		{
			ray.Set(polygonOuter[i].section.GetTail(), polygonOuter[i].section.GetDirection());
			ray2.Set(polygonOuter[i].section.GetHead(), polygonOuter[i].section.GetDirection() * -1);
			if (Clarity::Intersects(circle, ray, &distance) && Clarity::Intersects(circle, ray2, &distance))
			{
				out.push_back(polygonOuter[i].section);
				intersectingOuter.push_back(i);
				continue;
			}
		}
	}
	
}; // End namespace CarDemo.
