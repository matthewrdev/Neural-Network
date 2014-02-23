//****************************************************************************
//**
//**    NLayer.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <iostream>

#include "NLayer.h"

#include "MemoryLeak.h"

namespace CarDemo 
{
	NLayer::NLayer()
	{
	}

	NLayer::~NLayer()
	{
	}

	void NLayer::Evaluate(std::vector<float> input, std::vector<float> &output)
	{
		int inputIndex = 0;
		// Cycle over all the neurons and sum their weights against the inputs.
		for (unsigned int i = 0; i < totalNeurons; i++)
		{
			float activation = 0.0f;

			// Sum the weights to the activation value.
			// We do the sizeof the weights - 1 so that we can add in the bias to the 
			// activation afterwards.
			for (unsigned int j = 0; j < neurons[i].numInputs - 1; j++)
			{
				activation += input[inputIndex] * neurons[i].weights[j];
				inputIndex++;
			}

			// Add the bias.
			// The bias will act as a threshold value to 
			activation += neurons[i].weights[neurons[i].numInputs] * BIAS;

			output.push_back(Sigmoid(activation, 1.0f));
			inputIndex = 0;
		}
	}

	void NLayer::SaveLayer(std::ofstream &fileOut, char* layerType)
	{
		fileOut << "<NLayer>" << std::endl;
		fileOut << "Type=" << layerType << std::endl;
		fileOut << "Inputs=" << this->totalInputs << std::endl;
		fileOut << "Neurons=" << this->neurons.size() << std::endl;
		fileOut << "-Build-" << std::endl;
		for (unsigned int i = 0; i < this->neurons.size(); i++)
		{
			fileOut << "<Neuron>" << std::endl;
			fileOut << "Weights=" << this->neurons[i].weights.size() << std::endl;
			for (unsigned int j = 0; j < neurons[i].weights.size(); j++)
			{
				fileOut << "W=" << neurons[i].weights[j] << std::endl; 
			}
			fileOut << "</Neuron>" << std::endl;
		}
			
		fileOut << "</NLayer>" << std::endl;
	}

	void NLayer::LoadLayer(std::vector<Neuron> in)
	{
		totalNeurons = in.size();
		neurons = in;
	}

	void NLayer::PopulateLayer(int numOfNeurons, int numOfInputs)
	{
		totalInputs = numOfInputs;
		totalNeurons = numOfNeurons;
		this->neurons.resize(numOfNeurons);
		for (unsigned int i = 0; i < neurons.size(); i++)
		{
			neurons[i].Populate(numOfInputs);
		}
	}

	void NLayer::SetWeights(std::vector<float> weights, int numOfNeurons, int numOfInputs)
	{
		int index = 0;
		totalInputs = numOfInputs;
		totalNeurons = numOfNeurons;
		this->neurons.resize(numOfNeurons);
		// Copy the weights into the neurons.
		for (unsigned int i = 0; i < numOfNeurons; i++)
		{
			neurons[i].weights.resize(numOfInputs);
			for (unsigned int j = 0; j < numOfInputs; j++)
			{
				neurons[i].weights[j] = weights[index];
				index++;
			}
		}
	}

	void NLayer::GetWeights(std::vector<float> &out)
	{
		// Calculate the size of the output vector by calculating the amount of weights in each neurons.
		// Avoids having to use a nasty push-back...
		size_t size = 0;
		for (unsigned int i = 0; i < this->totalNeurons; i++)
		{
			size += neurons[i].weights.size();
		}
		out.resize(size);

		// Iterate over each neuron and each connection weight and retrieve the weights
		for (unsigned int i = 0; i < this->totalNeurons; i++)
		{
			for (unsigned int j = 0; j < neurons[i].weights.size(); j++)
			{
				out[totalNeurons * i + j] = neurons[i].weights[j];
			}
		}
	}
	
	void NLayer::SetNeurons(std::vector<Neuron> neurons, int numOfNeurons, int numOfInputs)
	{
		totalInputs = numOfInputs;
		totalNeurons = numOfNeurons;
		this->neurons = neurons;
	}

	
}; // End namespace CarDemo.