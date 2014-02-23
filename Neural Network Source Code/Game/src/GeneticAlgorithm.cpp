//****************************************************************************
//**
//**    GeneticAlgorithm.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include "GeneticAlgorithm.h"

#include "Genome.h"
#include "NeuralNet.h"

#include "GameGlobals.h"
#include "MemoryLeak.h"

namespace CarDemo 
{

	GeneticAlgorithm::GeneticAlgorithm()
	{
		this->currentGenome = -1;
		this->totalPopulation = 0;
		genomeID = 0;
		generation = 1;
	}

	GeneticAlgorithm::~GeneticAlgorithm()
	{
		ClearPopulation();
	}

	Genome* GeneticAlgorithm::GetNextGenome()
	{
		currentGenome++;
		if (currentGenome >= population.size())
			return NULL;

		return population[this->currentGenome];
	}

	Genome* GeneticAlgorithm::GetBestGenome()
	{
		int bestGenome = -1;
		float fitness = 0;
		for (unsigned int i = 0; i < population.size(); i++)
		{
			if (population[i]->fitness > fitness)
			{
				fitness = population[i]->fitness;
				bestGenome = i;
			}
		}

		return population[bestGenome];
	}

	Genome* GeneticAlgorithm::GetWorstGenome()
	{
		int worstGenome = -1;
		float fitness = 1000000;
		for (unsigned int i = 0; i < population.size(); i++)
		{
			if (population[i]->fitness < fitness)
			{
				fitness = population[i]->fitness;
				worstGenome = i;
			}
		}

		return population[worstGenome];
	}
	
	Genome* GeneticAlgorithm::GetGenome(int index)
	{
		if (index >= totalPopulation)
			return NULL;

		return population[index];
	}

	int GeneticAlgorithm::GetCurrentGenomeIndex() const
	{
		return currentGenome;
	}

	int GeneticAlgorithm::GetCurrentGenomeID() const
	{
		return population[currentGenome]->ID;
	}

	int GeneticAlgorithm::GetCurrentGeneration() const
	{
		return generation;
	}

	int GeneticAlgorithm::GetTotalPopulation() const
	{
		return totalPopulation;
	}

	void GeneticAlgorithm::GenerateCrossoverSplits(int neuronsPerHidden, int inputs, int outputs)
	{
		// Unimplemented
	}
	
	void GeneticAlgorithm::GetBestCases(int totalGenomes, std::vector<Genome*> &out)
	{
		int genomeCount = 0;
		int runCount = 0;

		while (genomeCount < totalGenomes)
		{
			if (runCount > 10)
				return;

			runCount++;

			// Find the best cases for cross breeding based on fitness score.
			float bestFitness = 0;
			int bestIndex = -1;
			for (unsigned int i = 0; i < this->totalPopulation; i++)
			{
				if (population[i]->fitness > bestFitness)
				{
					bool isUsed = false;

					for (unsigned int j = 0; j < out.size(); j++)
					{
						if (out[j]->ID == population[i]->ID)
						{
							isUsed = true;
						}
					}

					if (isUsed == false)
					{
						bestIndex = i;
						bestFitness = population[bestIndex]->fitness;
					}
				}
			}

			if (bestIndex != -1)
			{
				genomeCount++;
				out.push_back(population[bestIndex]);
			}

		}
	}

	
	void GeneticAlgorithm::CrossBreed(Genome* g1, Genome* g2, Genome* &baby1, Genome* &baby2)
	{
		// Select a random cross over point.
		unsigned int totalWeights = g1->weights.size();
		unsigned int crossover = rand() % totalWeights;

		baby1 = new Genome();
		baby1->ID = genomeID;
		baby1->weights.resize(totalWeights);
		genomeID++;

		baby2 = new Genome();
		baby2->ID = genomeID;
		baby2->weights.resize(totalWeights);
		genomeID++;

		// Go from start to crossover point, copying the weights from g1.
		for (unsigned int i = 0; i < crossover; i++)
		{
			baby1->weights[i] = g1->weights[i];
			baby2->weights[i] = g2->weights[i];
		}
		// Go from start to crossover point, copying the weights from g2 to child.
		for (unsigned int i = crossover; i < totalWeights; i++)
		{
			baby1->weights[i] = g2->weights[i];
			baby2->weights[i] = g1->weights[i];
		}
	}

	Genome* GeneticAlgorithm::CreateNewGenome(unsigned int totalWeights)
	{
		Genome* genome = new Genome();
		genome->ID = genomeID;
		genome->fitness = 0.0f;
		genome->weights.resize(totalWeights);
		for (unsigned int j = 0; j < totalWeights; j++)
		{
			genome->weights[j] = RandomClamped();
		}
		genomeID++;
		return genome;
	}

	void GeneticAlgorithm::GenerateNewPopulation(unsigned int totalPop, unsigned int totalWeights)
	{
		generation = 1;
		ClearPopulation();
		currentGenome = -1;
		totalPopulation = totalPop;
		population.resize(totalPop);
		for (unsigned int i = 0; i < population.size(); i++)
		{
			Genome* genome = new Genome();
			genome->ID = genomeID;
			genome->fitness = 0.0f;
			genome->weights.resize(totalWeights);
			for (unsigned int j = 0; j < totalWeights; j++)
			{
				genome->weights[j] = RandomClamped();
			}
			genomeID++;
			population[i] = genome;
		}
	}

	void GeneticAlgorithm::BreedPopulation()
	{
		std::vector<Genome*> bestGenomes;

		// Find the 4 best genomes.
		this->GetBestCases(4, bestGenomes);

		// Breed them with each other twice to form 3*2 + 2*2 + 1*2 = 12 children
		std::vector<Genome*> children;

		// Carry on the best dude.
		Genome* bestDude = new Genome();
		bestDude->fitness = 0.0f;
		bestDude->ID = bestGenomes[0]->ID;
		bestDude->weights = bestGenomes[0]->weights;
		Mutate(bestDude);
		children.push_back(bestDude);

		// Child genomes.
		Genome* baby1 = NULL;
		Genome* baby2 = NULL;

		// Breed with genome 0.
		CrossBreed(bestGenomes[0], bestGenomes[1], baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		children.push_back(baby1);
		children.push_back(baby2);
		CrossBreed(bestGenomes[0], bestGenomes[2], baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		children.push_back(baby1);
		children.push_back(baby2);
		CrossBreed(bestGenomes[0], bestGenomes[3], baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		children.push_back(baby1);
		children.push_back(baby2);

		// Breed with genome 1.
		CrossBreed(bestGenomes[1], bestGenomes[2], baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		children.push_back(baby1);
		children.push_back(baby2);
		CrossBreed(bestGenomes[1], bestGenomes[3], baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		children.push_back(baby1);
		children.push_back(baby2);

		// For the remainding n population, add some random kiddies.
		unsigned int remainingChildren = (totalPopulation - children.size());
		for (unsigned int i = 0; i < remainingChildren; i++)
		{

			children.push_back(this->CreateNewGenome(bestGenomes[0]->weights.size()));
		}

		ClearPopulation();
		population = children;

		currentGenome = -1;
		generation++;
	}

	void GeneticAlgorithm::ClearPopulation()
	{
		for (unsigned int i = 0; i < population.size(); i++)
		{
			if (population[i] != NULL)
			{
				delete population[i];
				population[i] = NULL;
			}
		}

		population.clear();
	}


	void GeneticAlgorithm::Mutate(Genome* genome)
	{
		for (unsigned int i = 0; i < genome->weights.size(); ++i)
		{
			// Generate a random chance of mutating the weight in the genome.
			if (RandomClamped() < CarDemo::MUTATION_RATE)
			{
				genome->weights[i] += (RandomClamped() * MAX_PERBETUATION);
			}
		}
	}
	
	void GeneticAlgorithm::SetGenomeFitness(float fitness, int index)
	{
		if (index >= population.size())
			return;

		population[index]->fitness = fitness;
	}
	
}; // End namespace CarDemo.
