#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

//****************************************************************************
//**
//**    EntityManager
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>
#include <Clarity/Math/LineSegment2.h>
#include <Clarity/Math/Vector2.h>
#include <Clarity/Math/Circle.h>

namespace CarDemo
{
	class Agent;
	class GeneticAlgorithm;
	class NeuralNet;
};

namespace GF1
{
	class Sprite;
};

namespace CarDemo 
{
	enum AgentLearningMode
	{
		USER_SUPERVISED,
		GENETIC_ALGORITHM,
	};

	enum CheckpointFlag
	{
		Checkpoint_Active,
		Checkpoint_Inactive,
	};

	const float CHECK_POINT_BONUS = 15.0f;
	const float DEFAULT_ROTATION = 90.0f;
	const Clarity::Vector2 DEFAULT_POSITION(0.0f, -175.0f);
	const unsigned int MAX_GENOME_POPULATION = 15;

	//const unsigned int HIDDEN_LAYER_NEURONS = 7;

	typedef Clarity::LineSegment2 Checkpoint;

	// This is used to hold 
	class EntityManager
	{
	private: 
		Agent* testAgent;
		std::vector<Agent*> agents;
		float currentAgentFitness;
		float bestFitness;
		float currentTimer;
		int checkPointsHit;

		GF1::Sprite* font;
		GF1::Sprite* pointSprite;

		NeuralNet* neuralNet;

		// The checkpoints for the polygon track we are testing the agent against.
		std::vector<Checkpoint> checkpoints;
		std::vector<CheckpointFlag> checkpointFlags;

		GeneticAlgorithm* genAlg;
		//char* GetRandomName();

	protected:
	public:

		EntityManager();
		~EntityManager();

		void LoadCheckPoints(char* filename);
		void LoadExternalNetwork(char* filename);

		void NextTestSubject();
		void BreedNewPopulation();
		void EvolveGenomes();
		int GetCurrentMemberOfPopulation() const;

		void ExportAllNeuralNetworks();
		void ExportCurrentAgent();

		void Render();
		void RenderStatistics();

		const Clarity::Circle& GetAgentSensorBounds();
		void TestAgentToPolySections(std::vector<Clarity::LineSegment2> polySections);

		void Restart();

		void Update(float t);

		 void ForceToNextAgent();
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _ENTITY_MANAGER_H