//****************************************************************************
//**
//**    Agent.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <cmath>

#include "Agent.h"

#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Matrix3.h>
#include <Clarity/Math/Math.h>

#include <GF1_Sprite.h>
#include <GF1_Colour.h>
#include <GF1_Graphics.h>
#include <GF1_Input.h>

#include "GameGlobals.h"
#include "NeuralNet.h"

#include "MemoryLeak.h"

using Clarity::Matrix3;
using Clarity::Vector2;


namespace CarDemo 
{


	Agent::Agent()
		: sprite(NULL)
		, headingAngle(0.0f) // Degrees.
		, neuralNet(NULL)
		, collidedCorner(-1)
		, hasFailed(false)
		, distanceDelta(0.0f)
	{
		sprite = new GF1::Sprite("Resources/Car.png", 21, 47, 1, 1, false);

		sensorBounds.SetRadius(CarDemo::FEELER_LENGTH);
		sensorBounds.SetCentre(this->position);
	}

	Agent::~Agent()
	{
		if (sprite != NULL)
		{
			delete sprite; 
			sprite = NULL;
		}
	}

	void Agent::BuildFeelers()
	{
		Matrix3 mat;
		Vector2 heading(0, 1); 
		heading *= FEELER_LENGTH;

		Vector2 northFeeler = heading;
		mat = mat.FromRotationZ(Clarity::RADIANS_PER_DEGREE * (headingAngle + NORTH_THETA));
		northFeeler = northFeeler.Transform(mat);
		sensor.feelerEnds[FEELER_NORTH] = this->position + northFeeler;
		sensor.feelers[FEELER_NORTH] = northFeeler;
		sensor.feelers[FEELER_NORTH].Normalise();

		// Build the east feeler.
		Vector2 eastFeeler = heading;
		mat = mat.FromRotationZ(Clarity::RADIANS_PER_DEGREE * (headingAngle + EAST_THETA));
		eastFeeler = eastFeeler.Transform(mat);
		sensor.feelerEnds[FEELER_EAST] = this->position + eastFeeler;
		sensor.feelers[FEELER_EAST] = eastFeeler;
		sensor.feelers[FEELER_EAST].Normalise();

		// Build the north east feeler.
		Vector2 northEastFeeler = heading;
		mat = mat.FromRotationZ(Clarity::RADIANS_PER_DEGREE * (headingAngle + NORTH_EAST_THETA));
		northEastFeeler = northEastFeeler.Transform(mat);
		sensor.feelerEnds[FEELER_NORTH_EAST] = this->position + northEastFeeler;
		sensor.feelers[FEELER_NORTH_EAST] = northEastFeeler;
		sensor.feelers[FEELER_NORTH_EAST].Normalise();

		// Build the north west feeler
		Vector2 northWestFeeler = heading;
		mat = mat.FromRotationZ(Clarity::RADIANS_PER_DEGREE * (headingAngle + NORTH_WEST_THETA));
		northWestFeeler = northWestFeeler.Transform(mat);
		sensor.feelerEnds[FEELER_NORTH_WEST] = this->position + northWestFeeler;
		sensor.feelers[FEELER_NORTH_WEST] = northWestFeeler;
		sensor.feelers[FEELER_NORTH_WEST].Normalise();

		// Build the west feeler.
		Vector2 westFeeler = heading;
		mat = mat.FromRotationZ(Clarity::RADIANS_PER_DEGREE * (headingAngle + WEST_THETA));
		westFeeler = westFeeler.Transform(mat);
		sensor.feelerEnds[FEELER_WEST] = this->position + westFeeler;
		sensor.feelers[FEELER_WEST] = westFeeler;
		sensor.feelers[FEELER_WEST].Normalise();
		
	}

	void Agent::BuildBounds()
	{
		// THis could be done more cleanly if i made a vertex based bounding box on the same principles however
		// seeing as Clarity doesnt have one and I'm to lazy to port mine over from my engine I'm just going to do
		// it this nice and messy way.

		// Create each of the feelers in local position.
		corners[CORNER_TOP_LEFT].Set(-(float)(sprite->GetFrameWidth()) / 2, (float)(sprite->GetFrameHeight()) / 2);
		corners[CORNER_TOP_RIGHT].Set((float)(sprite->GetFrameWidth()) / 2, (float)(sprite->GetFrameHeight()) / 2);
		corners[CORNER_BOTTOM_LEFT].Set(-(float)(sprite->GetFrameWidth()) / 2, -(float)(sprite->GetFrameHeight()) / 2);
		corners[CORNER_BOTTOM_RIGHT].Set((float)(sprite->GetFrameWidth()) / 2, -(float)(sprite->GetFrameHeight()) / 2);

		Clarity::Matrix3 rot;
		rot = rot.FromRotationZ(headingAngle * Clarity::RADIANS_PER_DEGREE);

		corners[CORNER_TOP_LEFT] = corners[CORNER_TOP_LEFT].Transform(rot);
		corners[CORNER_TOP_RIGHT] = corners[CORNER_TOP_RIGHT].Transform(rot);
		corners[CORNER_BOTTOM_LEFT] = corners[CORNER_BOTTOM_LEFT].Transform(rot);
		corners[CORNER_BOTTOM_RIGHT] = corners[CORNER_BOTTOM_RIGHT].Transform(rot);

		corners[CORNER_TOP_LEFT] += position;
		corners[CORNER_TOP_RIGHT] += position;
		corners[CORNER_BOTTOM_LEFT] += position;
		corners[CORNER_BOTTOM_RIGHT] += position;
	}

	void Agent::DrawFeelers()
	{
		GF1::DrawLine(ToGF1Vector(position), ToGF1Vector(sensor.feelerEnds[FEELER_NORTH]), GF1::Colour::BLUE, false, 2); 
		GF1::DrawLine(ToGF1Vector(position), ToGF1Vector(sensor.feelerEnds[FEELER_EAST]), GF1::Colour::BLUE, false, 2);
		GF1::DrawLine(ToGF1Vector(position), ToGF1Vector(sensor.feelerEnds[FEELER_NORTH_EAST]), GF1::Colour::BLUE, false, 2);
		GF1::DrawLine(ToGF1Vector(position), ToGF1Vector(sensor.feelerEnds[FEELER_NORTH_WEST]), GF1::Colour::BLUE, false, 2);
		GF1::DrawLine(ToGF1Vector(position), ToGF1Vector(sensor.feelerEnds[FEELER_WEST]), GF1::Colour::BLUE, false, 2); 
	}

	void Agent::DrawAgentBounds()
	{
		GF1::DrawLine(ToGF1Vector(corners[CORNER_TOP_LEFT]), ToGF1Vector(corners[CORNER_TOP_RIGHT]), GF1::Colour::WHITE, false, 1); 
		GF1::DrawLine(ToGF1Vector(corners[CORNER_TOP_RIGHT]), ToGF1Vector(corners[CORNER_BOTTOM_RIGHT]), GF1::Colour::WHITE, false, 1);
		GF1::DrawLine(ToGF1Vector(corners[CORNER_BOTTOM_RIGHT]), ToGF1Vector(corners[CORNER_BOTTOM_LEFT]), GF1::Colour::WHITE, false, 1);
		GF1::DrawLine(ToGF1Vector(corners[CORNER_BOTTOM_LEFT]), ToGF1Vector(corners[CORNER_TOP_LEFT]), GF1::Colour::WHITE, false, 1);
	}

	void Agent::Initilise(float headingIn)
	{
		headingAngle = headingIn;

		BuildBounds();
	}

	void Agent::SetPosition(const Clarity::Vector2& p)
	{
		position = p;
		sprite->SetPosition(ToGF1Vector(p));
		sensorBounds.SetCentre(this->position);
		sensorBounds.SetCentre(position);
		BuildFeelers();
		BuildBounds();
	}

	void Agent::Update(float t)
	{
		if (this->hasFailed == false)
		{
			// Our NN inputs are the intersection depths normalised and then fliped.
			// Eg if the intersection depth is the feeler length, then we normalise it
			// and subtract it from one. This way we get a gauge of how far the feeler is
			// into the wall.
			std::vector<float> inputs;
			for (unsigned int i = 0; i < FEELER_COUNT; i++)
			{
				// Normalise the depth value.
				float depth = intersectionDepths[i] / FEELER_LENGTH;

				// Subtract the normalised depth from 1 to end up with how close a wall is.
				// If a feeler has sensed no wall it will be FEELER_LENGTH for intersection depth.
				// So dividing depth / FEELER_LENGTH will result in 1.
				// If we then subtract the normalised depth from 1 -> 1 - 1 == 0.
				// Using this as our input for our NNet, it will guarentee that input to not fire.
				inputs.push_back(1 - depth);
			}

			neuralNet->SetInput(inputs);
			neuralNet->Update();

			// Retrieve outputs. These will be normalised 0 - 1 values.
			float leftForce = neuralNet->GetOutput(NN_OUTPUT_LEFT_FORCE);
			float rightForce = neuralNet->GetOutput(NN_OUTPUT_RIGHT_FORCE);

			// Convert the outputs to a proportion of how much to turn.
			float leftTheta = MAX_ROTATION_PER_SECOND * leftForce;
			float rightTheta = MAX_ROTATION_PER_SECOND * rightForce;

			headingAngle += (leftTheta - rightTheta) * t;
			float speed = (fabs(leftForce + rightForce)) / 2;
			speed *= SPEED;

			speed = Clamp(speed, -SPEED, SPEED);

			Clarity::Vector2 heading;
			heading.x = -sin(Clarity::RADIANS_PER_DEGREE *headingAngle);
			heading.y = cos(Clarity::RADIANS_PER_DEGREE *headingAngle);
			heading *= speed * t;
			distanceDelta = heading.Magnitude();
			this->position += heading;
			
			// Setup the agents sensors.
			sensorBounds.SetCentre(position);
			BuildFeelers();
			BuildBounds();
		}
	}

	float Agent::GetDistanceDelta()
	{
		return distanceDelta;
	}

	void Agent::Render()
	{
		sprite->SetPosition(ToGF1Vector(position));
		sprite->SetAngle(headingAngle);
		sprite->Render();
		DrawFeelers();
		DrawAgentBounds();

		// Draw feeler intersections.
		for (unsigned int i = 0; i < FEELER_COUNT; i++)
		{
			// Only draw if the depths as less than the feeler length, other wise we will get green
			// dots floating around even through they arent touching anything.
			if (this->intersectionDepths[i] < FEELER_LENGTH)
			{
				Clarity::Vector2 vec = sensor.feelers[i];
				if (vec.MagnitudeSquared() > 0.0f)
				{
					vec.Normalise();
				}
				vec *= intersectionDepths[i];
				vec += position;
				GF1::DrawFilledCircle(ToGF1Vector(vec), 5, GF1::Colour::GREEN);
			}
		}


		// Draw the boundingCircle
		GF1::DrawCircle(ToGF1Vector(position), FEELER_LENGTH, GF1::Colour::BLUE, false, 1);

		// Draw the collision point against the wall if this bot sucks
		if (this->collidedCorner != -1)
		{
			GF1::DrawFilledCircle(ToGF1Vector(corners[collidedCorner]), 3, GF1::Colour::RED, false); 
		}
	}
	
	void Agent::ClearFailure()
	{
		hasFailed = false;
		collidedCorner = -1;
	}
	
	bool Agent::HasFailed()
	{
		return hasFailed;
	}

	bool Agent::CheckForCollision(std::vector<Clarity::LineSegment2> polySections)
	{
		// For referece...
		// 0 = CORNER_TOP_LEFT
		// 1 = CORNER_TOP_RIGHT
		// 2 = CORNER_BOTTOM_RIGHT
		// 3 = CORNER_BOTTOM_LEFT
		// 4 = CORNER_COUNT

		std::vector<Clarity::LineSegment2> localBounds;
		this->GetLocalBounds(localBounds);

		
		Clarity::Ray2 ray(Clarity::Vector2::ZERO, Clarity::Vector2::ZERO);
		float distance = 0.0f;

		// Test the agent against the active checkpoints.
		for (unsigned int i = 0; i < polySections.size(); i++)
		{

			for (unsigned int j = 0; j < localBounds.size(); j++)
			{
				ray.Set(localBounds[j].GetTail(), localBounds[j].GetDirection());
				if (Clarity::Intersects(polySections[i], false, ray, &distance))
				{
					if (distance < localBounds[j].GetLength())
					{
						hasFailed = true;
						return true;
					}
				}
			}
		}
		// On falllthrough there was no collision with the walls.
		return false;
	}

	void Agent::Attach(NeuralNet* net)
	{
		neuralNet = net;
	}

	NeuralNet* Agent::GetNeuralNet()
	{
		return neuralNet;
	}

	void Agent::CreateNewNet()
	{
		neuralNet->ReleaseNet();
		neuralNet->CreateNet(1, FEELER_COUNT, HIDDEN_LAYER_NEURONS, NN_OUTPUT_COUNT);
	}

	const Clarity::Vector2& Agent::GetPosition() const
	{
		return position;
	}
	
	void Agent::SetRotation(float theta)
	{
		this->headingAngle = theta;
	}
	
	const Clarity::Circle& Agent::GetSensorBounds() const
	{
		return this->sensorBounds;
	}

	void Agent::GetLocalBounds(std::vector<Clarity::LineSegment2> &out)
	{
		// Create linesegments.
		Clarity::LineSegment2 left(corners[CORNER_TOP_LEFT], corners[CORNER_BOTTOM_LEFT]);
		Clarity::LineSegment2 right(corners[CORNER_TOP_RIGHT], corners[CORNER_BOTTOM_RIGHT]);
		Clarity::LineSegment2 top(corners[CORNER_TOP_LEFT], corners[CORNER_TOP_RIGHT]);
		Clarity::LineSegment2 bottom(corners[CORNER_BOTTOM_RIGHT], corners[CORNER_BOTTOM_LEFT]);

		out.push_back(left);
		out.push_back(right);
		out.push_back(top);
		out.push_back(bottom);
	}

	void Agent::UpdateSensors(std::vector<Clarity::LineSegment2> polySections)
	{
		// I could do this section in a for loop and make it nice and clean...
		// Or I could unwrap the loop and be explicit about whats hapenning with the tests.
		// Im going to choose the latter...

		// Clear intersection depths.
		for (unsigned int i = 0; i < FEELER_COUNT; i++)
		{
			intersectionDepths[i] = FEELER_LENGTH;
		}


		// --------------------------------------------------------------------------------
		Clarity::Ray2 ray(Clarity::Vector2::ZERO, Clarity::Vector2::UNIT_X);
		float distance = 0;
		float bestDistance = 999999.0f; // Very large number for best distance tests...
		// --------------------------------------------------------------------------------

		
		// --------------------------------------------------------------------------------
		// EAST Feeler.
		ray.Set(position, sensor.feelers[FEELER_EAST]);
		for (unsigned int i = 0; i < polySections.size(); i++)
		{
			if (Clarity::Intersects(polySections[i], true, ray, &distance))
			{
				if (distance <= CarDemo::FEELER_LENGTH)
				{
					bestDistance =  distance;
				}
			}
		}

		if (bestDistance <= FEELER_LENGTH)
		{
			this->intersectionDepths[FEELER_EAST] = bestDistance;
		}
		// --------------------------------------------------------------------------------

		distance = 0;
		bestDistance = 999999.0f;
		// --------------------------------------------------------------------------------
		// NORTH_EAST Feeler.
		ray.Set(position, sensor.feelers[FEELER_NORTH_EAST]);
		for (unsigned int i = 0; i < polySections.size(); i++)
		{
			if (Clarity::Intersects(polySections[i], true, ray, &distance))
			{
				if (distance <= CarDemo::FEELER_LENGTH)
				{
					bestDistance =  distance;
				}
			}
		}

		if (bestDistance <= FEELER_LENGTH)
		{
			this->intersectionDepths[FEELER_NORTH_EAST] = bestDistance;
		}
		// --------------------------------------------------------------------------------

		distance = 0;
		bestDistance = 999999.0f;
		// --------------------------------------------------------------------------------
		// NORTH Feeler.
		ray.Set(position, sensor.feelers[FEELER_NORTH]);
		for (unsigned int i = 0; i < polySections.size(); i++)
		{

			if (Clarity::Intersects(polySections[i], true, ray, &distance))
			{
				if (distance <= CarDemo::FEELER_LENGTH)
				{
					bestDistance =  distance;
				}
			}
		}

		if (bestDistance <= FEELER_LENGTH)
		{
			this->intersectionDepths[FEELER_NORTH] = bestDistance;
		}
		// --------------------------------------------------------------------------------

		distance = 0;
		bestDistance = 999999.0f;
		// --------------------------------------------------------------------------------
		// NORTH WEST Feeler.
		ray.Set(position, sensor.feelers[FEELER_NORTH_WEST]);
		for (unsigned int i = 0; i < polySections.size(); i++)
		{
			if (Clarity::Intersects(polySections[i], true, ray, &distance))
			{
				if (distance <= CarDemo::FEELER_LENGTH)
				{
					bestDistance = distance;
				}
			}
		}

		if (bestDistance <= FEELER_LENGTH)
		{
			this->intersectionDepths[FEELER_NORTH_WEST] = bestDistance;
		}
		// --------------------------------------------------------------------------------

		distance = 0;
		bestDistance = 999999.0f;
		// --------------------------------------------------------------------------------
		// WEST Feeler.
		ray.Set(position, sensor.feelers[FEELER_WEST]);
		for (unsigned int i = 0; i < polySections.size(); i++)
		{

			if (Clarity::Intersects(polySections[i], true, ray, &distance))
			{
				if (distance <= CarDemo::FEELER_LENGTH)
				{
					bestDistance = distance;
				}
			}
		}

		if (bestDistance <= FEELER_LENGTH)
		{
			this->intersectionDepths[FEELER_WEST] = bestDistance;
		}
		// --------------------------------------------------------------------------------
	}
	
}; // End namespace CarDemo.