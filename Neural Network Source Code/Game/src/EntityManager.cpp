//****************************************************************************
//**
//**    EntityManager.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GF1.h>

#include "EntityManager.h"

#include <GF1_Sprite.h>
#include <GF1_Colour.h>
#include <GF1_Graphics.h>

#include "Agent.h"
#include "GeneticAlgorithm.h"
#include "NeuralNet.h"

#include "GameSettings.h"
#include "GameGlobals.h"
#include "MemoryLeak.h"

namespace CarDemo 
{

	EntityManager::EntityManager()
	{
		font = new GF1::Sprite("Resources/TimesNewRomanWhite.png", 16, 16, 16*16, 1, false);
		pointSprite = new GF1::Sprite("Resources/PolyPointHighlighted.png", 8, 8, 1, 1, false);

		genAlg = new GeneticAlgorithm();
		int totalWeights = FEELER_COUNT * HIDDEN_LAYER_NEURONS + HIDDEN_LAYER_NEURONS * NN_OUTPUT_COUNT + HIDDEN_LAYER_NEURONS + NN_OUTPUT_COUNT;
		genAlg->GenerateNewPopulation(MAX_GENOME_POPULATION, totalWeights);
		currentAgentFitness = 0.0f;
		bestFitness = 0.0f;

		neuralNet = new NeuralNet();
		neuralNet->FromGenome(*genAlg->GetNextGenome(), FEELER_COUNT, HIDDEN_LAYER_NEURONS, NN_OUTPUT_COUNT);
		testAgent = new Agent();

		testAgent->SetRotation(DEFAULT_ROTATION);
		testAgent->SetPosition(DEFAULT_POSITION);
		testAgent->Attach(neuralNet);
	}

	EntityManager::~EntityManager()
	{
		if (font != NULL)
		{
			delete font;
			font = NULL;
		}

		if (pointSprite != NULL)
		{
			delete pointSprite;
			pointSprite = NULL;
		}

		if (genAlg != NULL)
		{
			delete genAlg;
			genAlg = NULL;
		}

		if (testAgent != NULL)
		{
			delete testAgent;
			testAgent = NULL;
		}

		if (neuralNet != NULL)
		{
			delete neuralNet;
			neuralNet = NULL;
		}
	}

	void EntityManager::LoadCheckPoints(char* filename)
	{
		FILE* file = fopen(filename,"rt");
		int tempID = 0;

		if (file!=NULL)
		{

			Clarity::Vector2 start;
			Clarity::Vector2 end;
			int totalCheckpoints = 0;
			int currentCheckpoint = 0;

			char buffComp[1024] ={0};

			while(fgets(buffComp,1024,file))
			{
				char buff[1024] = {0};

				if(buffComp[strlen(buffComp)-1]=='\n')
				{
					for(unsigned int i = 0; i<strlen(buffComp)-1;i++)
					{
						buff[i] = buffComp[i];
					}
				}

				if(0 == strcmp(buff, "<Declaration>"))
				{
				}
				else if (0==strcmp(buff,"</Declaration>"))
				{
					break;
				}
				else if (0==strcmp(buff,"-Build-"))
				{
					checkpoints.resize(totalCheckpoints);
				}
				else if(0 == strcmp(buff, "<Checkpoint>"))
				{
					start.Set(0.0f, 0.0f);
					end.Set(0.0f, 0.0f);
				}
				else if (0==strcmp(buff,"</Checkpoint>"))
				{
					checkpoints[currentCheckpoint].Set(end, start);
					currentCheckpoint++;
				}
			
				else
				{
					char* token = strtok(buff, "=");
					if(token != NULL)
					{
						char* value = strtok(NULL,"=");


						if(0 == strcmp(token,"sX"))
						{
							start.x = (float)atof(value);
						}
						else if(0 == strcmp(token,"sY"))
						{
							start.y = (float)atof(value);
						}
						else if(0 == strcmp(token,"eX"))
						{
							end.x = (float)atof(value);
						}
						else if(0 == strcmp(token,"eY"))
						{
							end.y = (float)atof(value);
						}
						else if(0 == strcmp("TotalCheckpoints", token))
						{
							totalCheckpoints = atoi(value);
						}
					}
				}
			}
			fclose(file);
		}
		
		checkpointFlags.resize(checkpoints.size());
		for (unsigned int i = 0; i < checkpointFlags.size(); i++)
		{
			checkpointFlags[i] = Checkpoint_Active;
		}
	}

	void EntityManager::LoadExternalNetwork(char* filename)
	{
		NeuralNet* network = new NeuralNet();
		network->LoadNet(filename);
	}

	void EntityManager::ExportCurrentAgent()
	{
		testAgent->GetNeuralNet()->ExportNet("NeuralNet.txt");
	}

	void EntityManager::NextTestSubject()
	{
		genAlg->SetGenomeFitness(currentAgentFitness,  genAlg->GetCurrentGenomeIndex());
		currentAgentFitness = 0.0f;
		Genome* genome = genAlg->GetNextGenome();

		neuralNet->FromGenome(*genome, FEELER_COUNT, HIDDEN_LAYER_NEURONS, NN_OUTPUT_COUNT);

		testAgent->SetRotation(DEFAULT_ROTATION);
		testAgent->SetPosition(DEFAULT_POSITION);
		testAgent->Attach(neuralNet);
		testAgent->ClearFailure();

		// Reset the checkpoint flags
		for (unsigned int i = 0; i < checkpointFlags.size(); i++)
		{
			checkpointFlags[i] = Checkpoint_Active;
		}
	}

	void EntityManager::BreedNewPopulation()
	{
		genAlg->ClearPopulation();
		int totalWeights = FEELER_COUNT * HIDDEN_LAYER_NEURONS + HIDDEN_LAYER_NEURONS * NN_OUTPUT_COUNT + HIDDEN_LAYER_NEURONS + NN_OUTPUT_COUNT;
		genAlg->GenerateNewPopulation(CarDemo::MAX_GENOME_POPULATION, totalWeights);
	}

	void EntityManager::EvolveGenomes()
	{
		genAlg->BreedPopulation();
		NextTestSubject();
	}

	int EntityManager::GetCurrentMemberOfPopulation() const
	{
		return genAlg->GetCurrentGenomeIndex();
	}

	void EntityManager::ExportAllNeuralNetworks()
	{
	}

	void EntityManager::Render()
	{
		testAgent->Render();

		// Render the checkpoints.
		for (unsigned int i = 0; i < checkpoints.size(); i++)
		{
			if (checkpointFlags[i] == Checkpoint_Inactive)
				continue;

			GF1::Vector3 start = ToGF1Vector(checkpoints[i].GetHead());
			GF1::Vector3 end = ToGF1Vector(checkpoints[i].GetTail());
			GF1::DrawLine(start, end, GF1::Colour::WHITE, false, 2.0f);
			pointSprite->SetPosition(start);
			pointSprite->Render();
			pointSprite->SetPosition(end);
			pointSprite->Render();
		}
	}

	void EntityManager::RenderStatistics()
	{
		GF1::Vector3 printPos;
		char buff[128] = {0};
		int genomeNumber = genAlg->GetCurrentGenomeIndex();

		sprintf(buff, "Genome: %i of %i", genomeNumber + 1, MAX_GENOME_POPULATION);
		printPos.Set(-(gSettings.WORLD_WIDTH/2),
						 -(gSettings.WORLD_HEIGHT/2)+90.0f,
						 0.0f);
		GF1::print(font, printPos, buff);

		ZeroMemory(&buff, sizeof(char) * 128);
		printPos.y -= 18.0f;
		sprintf(buff, "Fitness: %.2f", this->currentAgentFitness);
		GF1::print(font, printPos, buff);

		ZeroMemory(&buff, sizeof(char) * 128);
		printPos.y -= 18.0f;
		sprintf(buff, "Generation: %i", genAlg->GetCurrentGeneration());
		GF1::print(font, printPos, buff);

		ZeroMemory(&buff, sizeof(char) * 128);
		printPos.y -= 18.0f;
		sprintf(buff, "Best Fitness To Date: %.2f", bestFitness);
		GF1::print(font, printPos, buff);
	}

	const Clarity::Circle& EntityManager::GetAgentSensorBounds()
	{
		return testAgent->GetSensorBounds();
	}

	void EntityManager::TestAgentToPolySections(std::vector<Clarity::LineSegment2> polySections)
	{
		testAgent->UpdateSensors(polySections);
		testAgent->CheckForCollision(polySections);
	}

	void EntityManager::Update(float t)
	{
		if (testAgent->HasFailed())
		{
			if (genAlg->GetCurrentGenomeIndex() == MAX_GENOME_POPULATION - 1)
			{
				EvolveGenomes();
				return;
			}
			NextTestSubject();
		}
		// Update the agent.
		testAgent->Update(t);
		currentAgentFitness += testAgent->GetDistanceDelta() / 2.0f;
		if (currentAgentFitness > bestFitness)
		{
			bestFitness = currentAgentFitness;
		}

		std::vector<Clarity::LineSegment2> agentBounds;
		testAgent->GetLocalBounds(agentBounds);
		Clarity::Ray2 ray(Clarity::Vector2::ZERO, Clarity::Vector2::ZERO);
		float distance = 0.0f;

		// Test the agent against the active checkpoints.
		for (unsigned int i = 0; i < checkpoints.size(); i++)
		{
			// See if the checkpoint has already been hit.
			if (checkpointFlags[i] == Checkpoint_Inactive)
				continue;

			for (unsigned int j = 0; j < agentBounds.size(); j++)
			{
				ray.Set(agentBounds[j].GetTail(), agentBounds[j].GetDirection());
				if (Clarity::Intersects(checkpoints[i], false, ray, &distance))
				{
					if (distance < agentBounds[j].GetLength())
					{
						currentAgentFitness += CHECK_POINT_BONUS;
						checkpointFlags[i] = Checkpoint_Inactive;
						if (currentAgentFitness > bestFitness)
						{
							bestFitness = currentAgentFitness;
						}
						return;
					}
				}
			}
		}
	}

	void EntityManager::ForceToNextAgent()
	{
		if (genAlg->GetCurrentGenomeIndex() == MAX_GENOME_POPULATION - 1)
		{
			EvolveGenomes();
			return;
		}
		NextTestSubject();
	}

	void EntityManager::Restart()
	{
	}
	
}; // End namespace CarDemo.