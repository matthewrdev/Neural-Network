#ifndef _GAME_GLOBALS_H
#define _GAME_GLOBALS_H

//****************************************************************************
//**
//**    GameGlobals.h
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 03/2010
//**
//****************************************************************************

#include <GF1_Vector3.h>
#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Ray2.h>
#include <Clarity/Math/Math.h>

namespace GF1
{
	class Sprite;
};

namespace CarDemo 
{

	const int INVALID_ID = -1;
	const int MAX_POPULATION = 15;
	static const Clarity::Vector2 gWorldUp(0.0f, 1.0f);
	const int HIDDEN_LAYER_NEURONS = 8;
	const float MAX_FRAME_DELTA = 1 / 20.0f;
	const float MUTATION_RATE = 0.15f;
	const float MAX_PERBETUATION = 0.3f;


	// Agent specific stuff.
	// These are the rotation amounts that are applied to the feelers to rebuild them
	const float EAST_THETA = 90.0f;
	const float NORTH_EAST_THETA = 45.0f;
	const float NORTH_THETA = 0.0f;
	const float NORTH_WEST_THETA = -45.0f;
	const float WEST_THETA = -90.0f;
	const float SPEED = 70.0f;
	const float FEELER_LENGTH = 120.0f;

	const float MAX_ROTATION_PER_SECOND = 80.0f; // Degrees per seconds.
	
	inline GF1::Vector3 ToGF1Vector(const Clarity::Vector2& v)
	{
		GF1::Vector3 out;
		out.x = v.x;
		out.y = v.y;
		out.z = 0;
		return out;
	}

	inline Clarity::Vector2 ToClarityVector(const GF1::Vector3& v)
	{
		Clarity::Vector2 out;
		out.x = v.x;
		out.y = v.y;
		return out;
	}


	inline Clarity::Ray2 ToRay2(const Clarity::Vector2& dir, const Clarity::Vector2& origin)
	{
		return Clarity::Ray2(origin, dir);
	}


	// ----------------------------------------------------------------------
	// Thank you to my friends Wikipedia, AI Techniques for Game Programming 
	// and AI Game Engine Programming for  explaining the constant 'e' and
	// showing an implemntation of Sigmoid Curve equation.
	// ----------------------------------------------------------------------
	static const float e = 2.7183f;

	// Creates an S curve based from the mathematical constant '.' This is a 
	// clamped value from 0 to 1.
	// 
	inline float Sigmoid(float a, float p)
	{
		float ap = (-a)/p;
		return (1 / (1 + Clarity::Exp(ap)));
	}

	// Creates an S curve based from the mathematical constant '.' This is a 
	// clamped value from -1 to 1.
	// The higher the value of p the steeper the curve is.
	inline float BiPolarSigmoid(float a, float p)
	{
		float ap = (-a)/p;
		return (2 / (1 + Clarity::Exp(ap)) - 1);
	}

	/*inline float HalfBiPolarSigmoid(float a, float p)
	{
		float ap = (-a)/p;
		return (2 / (1 + exp(ap)) - 1);
	}*/

	inline float RandomFloat()
	{
		return (float)rand()/*0 to 32767*/ / (float)RAND_MAX/*32767*/ + 1.0f;
	}

	inline float RandomClamped()
	{
		return RandomFloat() - RandomFloat();
	}

	inline float Clamp( float val, float min, float max)
	{
		if (val < min)
		{
			return min;
		}

		if (val > max)
		{
			return max;
		}

		return val;
	}



}; // End namespace RoboFighter.

#endif // #ifndef _GAME_GLOBALS_H