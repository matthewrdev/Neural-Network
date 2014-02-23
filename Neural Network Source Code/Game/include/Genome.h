#ifndef _GENOME_H
#define _GENOME_H

//****************************************************************************
//**
//**    Genome.h
//**
//**    Copyright (c) 2010 Matthew Robbins
//**
//**    Author:  Matthew Robbins
//**    Created: 04/2010
//**
//****************************************************************************

#include <vector>

namespace CarDemo 
{

	class Genome
	{
	private:
	protected:
	public:
		float fitness;
		int ID;
		std::vector<float> weights;

	};
	
}; // End namespace CarDemo.

#endif // #ifndef _GENOME_H