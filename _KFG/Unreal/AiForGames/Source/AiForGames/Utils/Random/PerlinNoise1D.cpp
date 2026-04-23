#include "PerlinNoise1D.h"

#include <stdexcept>


PerlinNoise1D::PerlinNoise1D(int octaves, float min, float max, float slopeFactor, float persistence)
{
	this->octaves = octaves;
	this->min = min;
	this->max = max;
	this->slopeFactor = slopeFactor;
	this->persistence = persistence;
	valuesLength = octaves*(octaves+1) / 2;
	values = new float[valuesLength];
	results = new float[octaves];
	newStep();
	localT = 0;
}


float PerlinNoise1D::getNextValue(float deltaT)
{
	if (deltaT < 0)
		throw std::invalid_argument("deltaT must be greater than 0");
	localT += deltaT;
	if (localT >= 1)
	{
		if (localT < 2)
		{
			nextStep();
			localT--;
		}
		else
		{
			newStep();
			localT = localT - static_cast<int>(localT);
		}
	}
	return getValue(localT);
}


void PerlinNoise1D::newStep() const
{
	for (int i = 0; i < valuesLength; i++)
		values[i] = (FMath::FRandRange(min, max) + FMath::FRandRange(min, max)) / 2;
		
}


void PerlinNoise1D::nextStep() const
{
	int indexOffset = 0;
	for (int o = 0; o < octaves; o++)
	{
		values[indexOffset] = values[indexOffset+o+1];
		int v = 1;
		for (; v < o+1; v++)
			values[indexOffset+v] = (FMath::FRandRange(min, max) + FMath::FRandRange(min, max)) / 2;
		indexOffset += v;
	}
}


float PerlinNoise1D::getValue(float t) const
{
	if (t < 0 || t > 1)
		throw std::invalid_argument("t must be a value from 0 to 1");
	float result = 0;
	int indexOffset = 0;
	for (int o = 0; o < octaves; o++)
	{
		float pos = t * (o+1);
		int spectrum = static_cast<int>(pos);
		float rel = pos - spectrum;
		float res = FMath::InterpEaseInOut(values[indexOffset+spectrum], values[indexOffset+spectrum+1], 
			rel, slopeFactor);
		result += res * FMath::Pow(persistence, o+1);
		
		indexOffset += o+1;
	}
	return result;
}



