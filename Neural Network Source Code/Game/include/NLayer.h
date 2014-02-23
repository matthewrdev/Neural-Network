#ifndef _NLAYER_H
#define _NLAYER_H

//****************************************************************************
//**
//**    NLayer.h
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>
#include <fstream>

#include <assert.h>

#include "GameGlobals.h"

namespace CarDemo 
{
	class Neuron
	{
	private:
	protected:
	public:
		int numInputs;
		std::vector<float> weights;

		// 
		void Populate(int numOfInputs)
		{
			this->numInputs = numOfInputs;

			// Initilise the weights
			for (unsigned int i = 0; i < numOfInputs; i++)
			{
				weights.push_back(RandomClamped());
			}

			// Add an extra weight as the bias (the value that acts as a threshold in a step activation).
			weights.push_back(RandomClamped());
		}

		void Initilise(std::vector<float> weightsIn, int numOfInputs)
		{
			// The number of inputs should not be equal or exceed the weights.
			// If so, something is not right in the exported NN file or you've 
			// just done something odd to fuck this up.
			//assert(numOfInputs < weightsIn.size());

			this->numInputs = numOfInputs;
			weights = weightsIn;
		}

		Neuron(){}
		~Neuron(){}
	};

	const float BIAS = -1.0f;

	enum EvalFunction
	{
		EVAL_SIGMOID,
		EVAL_STEP,
		EVAL_BIPOLAR,
	};

	// The NLayer is a tighly connected
	class NLayer
	{
	private:
		int totalNeurons;
		int totalInputs;
		std::vector<Neuron> neurons;

	protected:
	public:
		NLayer();
		~NLayer();

		// Evalutes the inputs to the outputs, the amount of input should be mapped directly to the amount
		// of neurons in the layer. Each neuron will be mapped to the corresponding input
		void Evaluate(std::vector<float> input, std::vector<float> &output);

		void SaveLayer(std::ofstream &fileOut, char* layerType);
		void LoadLayer(std::vector<Neuron> in);

		// Creates the layer with 'n' neurons, intilise with random weights.
		void PopulateLayer(int numOfNeurons, int numOfInputs);

		void SetWeights(std::vector<float> weights, int numOfNeurons, int numOfInputs);
		void GetWeights(std::vector<float> &out);

		void SetNeurons(std::vector<Neuron> neurons, int numOfNeurons, int numOfInputs);
	};
	
}; // End namespace CarDemo.

#endif // #ifndef _NLAYER_H