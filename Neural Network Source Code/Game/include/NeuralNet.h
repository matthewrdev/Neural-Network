#ifndef _NEURAL_NET_H
#define _NEURAL_NET_H

//****************************************************************************
//**
//**    NeuralNet.h
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
	class NLayer;
	class Genome;
};

namespace CarDemo 
{

	// For the record, I owe a great debt to the website ai-junkie for its walkthrough of a NN.
	// Also, Brian Schwabs "AI Game Engine Programming" was another godsend that helped immensly with this 
	// implementation.
	class NeuralNet
	{
	private:
		int inputAmount;
		int outputAmount;
		std::vector<float> inputs;
		NLayer* inputLayer;
		std::vector<NLayer*> hiddenLayers;
		NLayer* outputLayer;
		std::vector<float> outputs;
	protected:
	public:
		NeuralNet();
		~NeuralNet();

		void Update();

		void SetInput(std::vector<float> in);
		float GetOutput(unsigned int ID);
		int GetTotalOutputs() const;

		void ExportNet(char* filename);
		void LoadNet(char* filename);

		void CreateNet(int numOfHiddenLayers, int numOfInputs, int neuronsPerHidden, int numOfOutputs);
		int GetNumOfHiddenLayers();

		void ReleaseNet();

		Genome* ToGenome();
		void FromGenome(const Genome& genome, int numOfInputs, int neuronsPerHidden, int numOfOutputs);
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _NEURAL_NET_H