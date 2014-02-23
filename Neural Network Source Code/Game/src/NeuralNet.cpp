//****************************************************************************
//**
//**    NeuralNet.cpp
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <iostream>
#include <fstream>

#include "NeuralNet.h"

#include "NLayer.h"
#include "Genome.h"

#include "MemoryLeak.h"

using std::endl;

namespace CarDemo 
{

	NeuralNet::NeuralNet()
		: inputLayer(NULL)
		, outputLayer(NULL)
	{
	}

	NeuralNet::~NeuralNet()
	{
		if (inputLayer != NULL)
		{
			delete inputLayer;
			inputLayer = NULL;
		}
		if (outputLayer != NULL)
		{
			delete outputLayer;
			outputLayer = NULL;
		}
		for (unsigned int i = 0; i < hiddenLayers.size(); i++)
		{
			if (hiddenLayers[i] != NULL)
			{
				delete hiddenLayers[i];
				hiddenLayers[i] = NULL;
			}
		}
		hiddenLayers.clear();
	}

	void NeuralNet::Update()
	{
		outputs.clear();

		for (unsigned int i = 0; i < hiddenLayers.size(); i++)
		{
			if (i > 0)
			{
				inputs = outputs;
			}

			hiddenLayers[i]->Evaluate(inputs, outputs);
		}

		inputs = outputs;
		// Process the layeroutputs through the output llayer to 
		outputLayer->Evaluate(inputs, outputs);
	}

	void NeuralNet::SetInput(std::vector<float> in)
	{
		inputs = in;
	}

	float NeuralNet::GetOutput(unsigned int ID)
	{
		if (ID >= outputAmount)
			return 0.0f;
		return outputs[ID];
	}

	int NeuralNet::GetTotalOutputs() const
	{
		return outputAmount;
	}

	void NeuralNet::ExportNet(char* filename)
	{
		char buff[128] = {0};
		sprintf(buff, "ExportedNNs/%s", filename);
		std::ofstream file;
		file.open(buff);

		file << "<NeuralNetwork>" << endl;
		file <<"TotalOuputs=" << this->outputAmount << endl;
		file <<"TotalInputs=" << this->inputAmount << endl;
		// Export hidden layerss.
		for (unsigned int i = 0; i < hiddenLayers.size(); i++)
		{
			hiddenLayers[i]->SaveLayer(file, "Hidden");
		}
		// Export output layer.
		outputLayer->SaveLayer(file, "Output");
		file << "</NeuralNetwork>" << endl;

		file.close();
	}

	void NeuralNet::LoadNet(char* filename)
	{
		FILE* file = fopen(filename,"rt");

		if(file!=NULL)
		{
			enum LayerType
			{
				HIDDEN,
				OUTPUT,
			};

			float weight = 0.0f;
			int totalNeurons = 0;
			int totalWeights = 0;
			int totalInputs = 0;
			int currentNeuron = 0;
			std::vector<Neuron> neurons;
			std::vector<float> weights;
			LayerType type = HIDDEN;


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

				if(0 == strcmp(buff, "<NeuralNetwork>"))
				{
				}
				else if (0 == strcmp(buff,"</NeuralNetwork>"))
				{
					break;
				}
				else if (0 == strcmp(buff,"<NLayer>"))
				{
					weight = 0.0f;
					totalNeurons = 0;
					totalWeights = 0;
					totalInputs = 0;
					currentNeuron = 0;
					neurons.clear();
					type = HIDDEN;
				}
				else if (0 == strcmp(buff,"</NLayer>"))
				{
					NLayer* layer = new NLayer();
					layer->SetNeurons(neurons, neurons.size(), totalInputs);
					switch (type)
					{
					case HIDDEN:
						this->hiddenLayers.push_back(layer);
						layer = NULL;
						break;
					case OUTPUT:
						this->outputLayer = layer;
						layer = NULL;
						break;
					};
				}
				else if (0 == strcmp(buff,"<Neuron>"))
				{
					weights.clear();
				}
				else if (0 == strcmp(buff,"</Neuron>"))
				{
					neurons[currentNeuron].Initilise(weights, totalInputs);
					currentNeuron++;
				}
			
				else
				{
					char* token = strtok(buff, "=");
					if(token != NULL)
					{
						char* value = strtok(NULL,"=");


						if (0 == strcmp(token,"Type"))
						{
							if (0 == strcmp("Hidden", value))
							{
								type = HIDDEN;
							}
							else if (0 == strcmp("Output", value))
							{
								type = OUTPUT;
							}
						}
						else if (0 == strcmp(token,"Inputs"))
						{
							totalInputs = atoi(value);
						} 
						else if (0 == strcmp(token,"Neurons"))
						{
							totalNeurons = atoi(value);
						} 
						else if (0 == strcmp(token,"Weights"))
						{
							totalWeights = atoi(value);
						} 
						else if (0 == strcmp(token,"W"))
						{
							weight = (float)atof(value);
						} 
						else if (0 == strcmp(token,"TotalOuputs"))
						{
							outputAmount = atoi(value);
						} 
						else if (0 == strcmp(token,"TotalInputs"))
						{
							inputAmount = atoi(value);
						} 
					}
				}
			}
			fclose(file);
		}
	}

	void NeuralNet::CreateNet(int numOfHiddenLayers, int numOfInputs, int neuronsPerHidden, int numOfOutputs)
	{
		inputAmount = numOfInputs;
		outputAmount = numOfOutputs;

		for (unsigned int i = 0; i < numOfHiddenLayers; i++)
		{
			NLayer* layer = new NLayer();
			layer->PopulateLayer(neuronsPerHidden, numOfInputs);
			hiddenLayers.push_back(layer);
		}

		outputLayer = new NLayer();
		outputLayer->PopulateLayer(numOfOutputs, neuronsPerHidden);		
	}

	
	void NeuralNet::ReleaseNet()
	{
		if (inputLayer != NULL)
		{
			delete inputLayer;
			inputLayer = NULL;
		}
		if (outputLayer != NULL)
		{
			delete outputLayer;
			outputLayer = NULL;
		}
		for (unsigned int i = 0; i < hiddenLayers.size(); i++)
		{
			if (hiddenLayers[i] != NULL)
			{
				delete hiddenLayers[i];
				hiddenLayers[i] = NULL;
			}
		}
		hiddenLayers.clear();
	}

	int NeuralNet::GetNumOfHiddenLayers()
	{
		return hiddenLayers.size();
	}
	
	Genome* NeuralNet::ToGenome()
	{
		Genome* genome = new Genome();
		for (unsigned int i = 0; i < this->hiddenLayers.size(); i++)
		{
			std::vector<float> weights;
			hiddenLayers[i]->GetWeights(weights);
			for (unsigned int j = 0; j < weights.size(); j++)
			{
				genome->weights.push_back(weights[j]);
			}
		}
			
		std::vector<float> weights;
		outputLayer->GetWeights(weights);
		for (unsigned int i = 0; i < weights.size(); i++)
		{
			genome->weights.push_back(weights[i]);
		}
		
		return genome;
	}
	
	void NeuralNet::FromGenome(const Genome& genome, int numOfInputs, int neuronsPerHidden, int numOfOutputs)
	{		
		ReleaseNet();

		outputAmount = numOfOutputs;
		inputAmount = numOfInputs;
		int weightsForHidden = numOfInputs * neuronsPerHidden;
		NLayer* hidden = new NLayer();
		std::vector<Neuron> neurons;
		neurons.resize(neuronsPerHidden);
		for (unsigned int i = 0; i < neuronsPerHidden; i++)
		{
			std::vector<float> weights;
			weights.resize(numOfInputs + 1);
			for (unsigned int j = 0; j < numOfInputs + 1; j++)
			{
				weights[j] = genome.weights[i * neuronsPerHidden + j];
			}
			neurons[i].Initilise(weights, numOfInputs);
		}
		hidden->LoadLayer(neurons);
		this->hiddenLayers.push_back(hidden);

		// Clear weights and reasign the weights to the output.
		int weightsForOutput = neuronsPerHidden * numOfOutputs;
		neurons.clear();
		neurons.resize(numOfOutputs);
		for (unsigned int i = 0; i < numOfOutputs; i++)
		{
			std::vector<float> weights;
			weights.resize(neuronsPerHidden + 1);
			for (unsigned int j = 0; j < neuronsPerHidden + 1; j++)
			{
				weights[j] = genome.weights[i * neuronsPerHidden + j];
			}
			neurons[i].Initilise(weights, neuronsPerHidden);
		}
		outputLayer = new NLayer();
		this->outputLayer->LoadLayer(neurons);
	}

}; // End namespace CarDemo.