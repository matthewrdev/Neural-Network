#ifndef _TRACK_POLYGON_H
#define _TRACK_POLYGON_H

//****************************************************************************
//**
//**    TrackPolygon
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>

#include <GF1_Vector3.h>
#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/LineSegment2.h>

// Forward Declarations
namespace GF1
{
	class Sprite;
};

namespace Clarity
{
	class Circle;
};

using Clarity::Vector3;
using Clarity::LineSegment3;
using GF1::Sprite;

namespace CarDemo 
{
	struct PolySection
	{
		Clarity::LineSegment2 section;
		Clarity::Vector2 normal;
		PolySection()
			: section(Clarity::Vector2::ZERO, Clarity::Vector2::ZERO)
			, normal(Clarity::Vector2::ZERO)
		{	
		}

		~PolySection()
		{		}
	};

	enum PolyMode
	{
		POLY_EDIT_INNER,
		POLY_EDIT_OUTER,
		POLY_NON_EDIT,
	};


	class TrackPolygon
	{
	private:
		std::vector<PolySection> polygonInner;
		std::vector<PolySection> polygonOuter;
		std::vector<GF1::Vector3> pointsInner;
		std::vector<GF1::Vector3> pointsOuter;

		// Debugging feature that shows intersecting polysegments.
		std::vector<int> intersectingInner;
		std::vector<int> intersectingOuter;

		PolyMode mode;
		GF1::Vector3 position;

		Sprite* pointSprite;
		Sprite* pointSpriteHighlight;
		Sprite* normalArrow;

		int currentSectionInner;
		int currentSectionOuter;

		bool drawNormals;

		//
		void BuildSection(Clarity::Vector2 start, Clarity::Vector2 end);
	protected:
	public:
		TrackPolygon();
		~TrackPolygon();

		void DrawTrack();
		void DrawPolySegmentNormals();
		void DrawIntersectingPolySections();

		void LoadPolygon(char* filename);
		void ExportPolygon(char* filename);

	
		// Game functions.
		void QueryPossibleCollisions(const Clarity::Circle& circle, std::vector<Clarity::LineSegment2> &out);
		void GetPolySections(std::vector<Clarity::LineSegment2> &polyInner, std::vector<Clarity::LineSegment2> &polyOuter);
		
		// Editor functions.
		void AddPoint(GF1::Vector3 point);
		void FlipNormal();
		void SwapMode(PolyMode mode);
		void CycleUp();
		void CycleDown();
		void ClosePolygon(PolyMode poly);
		PolyMode GetMode();
		void ToggleNormalRendering();
		bool IsDrawingNormals() const;
		void Undo();

	};
	
}; // End namespace CarDemo.

#endif // #ifndef _TRACK_POLYGON_H