#ifndef _CAR_H
#define _CAR_H

//****************************************************************************
//**
//**    Car
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>

#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/LineSegment2.h>
#include <Clarity/Math/Circle.h>

// Forward Declarations
namespace GF1
{
	class Sprite;
};

namespace CarDemo
{
	class NeuralNet;
	class Genome;
};

namespace CarDemo 
{
	enum NeuralNetOuputs
	{
		NN_OUTPUT_RIGHT_FORCE,
		NN_OUTPUT_LEFT_FORCE,

		NN_OUTPUT_COUNT,
	};

	// The identifiers for the feelers of the agnet
	enum SensorFeelers
	{
		FEELER_EAST,
		FEELER_NORTH_EAST,
		FEELER_NORTH,
		FEELER_NORTH_WEST,
		FEELER_WEST,

		FEELER_COUNT,
	};


	enum AgentBoundsCorners
	{
		CORNER_TOP_LEFT,
		CORNER_TOP_RIGHT,
		CORNER_BOTTOM_RIGHT,
		CORNER_BOTTOM_LEFT,

		CORNER_COUNT,
	};


	struct Sensor
	{
		Clarity::Vector2 feelerEnds[FEELER_COUNT];
		Clarity::Vector2 feelers[FEELER_COUNT];
	};

	class Agent
	{
	private:
		bool hasFailed;
		float distanceDelta;

		int collidedCorner;
		GF1::Sprite* sprite;
		Sensor sensor;

		NeuralNet* neuralNet;

		Clarity::Vector2 position;
		Clarity::Circle sensorBounds;
		Clarity::Vector2 corners[CORNER_COUNT];

		float intersectionDepths[FEELER_COUNT];

		float headingAngle; // Degrees.

		void BuildBounds();
		void BuildFeelers();

		void DrawFeelers();
		void DrawAgentBounds();
	protected:
	public:

		Agent();
		~Agent();

		void Initilise(float headingIn);

		void SetPosition(const Clarity::Vector2& p);
		const Clarity::Vector2& GetPosition() const;
		void SetRotation(float theta);
		void CreateNewNet();

		void Update(float t);
		void Render();

		void GetIntersectionDepths(std::vector<float> &out);

		const Clarity::Circle& GetSensorBounds() const;
		void GetLocalBounds(std::vector<Clarity::LineSegment2> &out);

		void UpdateSensors(std::vector<Clarity::LineSegment2> polySections);

		// Tests the agent against the polygon walls to see if it has collided with the wall.
		// Uses a plane equation for each vertice and poly segment to deduce this.
		bool CheckForCollision(std::vector<Clarity::LineSegment2> polySections);

		void Attach(NeuralNet* net);
		NeuralNet* GetNeuralNet();

		void ClearFailure();

		float GetDistanceDelta();

		bool HasFailed();
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _CAR_H