#ifndef _GENETIC_ALGORITHM_H
#define _GENETIC_ALGORITHM_H

//****************************************************************************
//**
//**    GeneticAlgorithm.h
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>

// Forward Declarations
namespace CarDemo
{
	class Genome;
	class NeuralNet;
};

namespace CarDemo 
{

	class GeneticAlgorithm
	{
	private:
		int currentGenome;
		unsigned int totalPopulation;
		int genomeID;
		int generation;
		int totalGenomeWeights;
		std::vector<Genome*> population;
		std::vector<int> crossoverSplits;

		void GetBestCases(int totalGenomes, std::vector<Genome*> &out);
		void CrossBreed(Genome* g1, Genome* g2, Genome* &baby1, Genome* &baby2);
		void Mutate(Genome* genome);
		Genome* CreateNewGenome(unsigned int totalWeights);
	protected:
	public:
		GeneticAlgorithm();
		~GeneticAlgorithm();

		Genome* GetNextGenome();
		Genome* GetBestGenome();
		Genome* GetWorstGenome();
		Genome* GetGenome(int index);

		int GetCurrentGenomeIndex() const;
		int GetCurrentGenomeID() const;
		int GetCurrentGeneration() const;
		int GetTotalPopulation() const;

		// Creates a new population 
		void GenerateNewPopulation(unsigned int totalPop, unsigned int totalWeights);
		void BreedPopulation();
		void ClearPopulation();

		void GenerateCrossoverSplits(int neuronsPerHidden, int inputs, int outputs);

		void SetGenomeFitness(float fitness, int index);
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _GENETIC_ALGORITHM_H