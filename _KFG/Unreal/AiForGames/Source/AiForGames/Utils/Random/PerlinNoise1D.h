
#pragma once

#include <vector>

using namespace std;

class PerlinNoise1D
{
	
public:
	
protected:
	
private:
	int octaves;
	float min;
	float max;
	float persistence;
	float slopeFactor;
	
	float* values;
	int valuesLength;
	float* results;
	float localT;
	
	
	
	
	
private:
	void nextStep() const;
	void newStep() const;
	[[nodiscard]]
	float getValue(float t) const;
	
protected:
	
public:
	PerlinNoise1D(int octaves, float min, float max, float slopeFactor = 8, float persistence = 0.5);
	
	/**
	 * get a value after the last return value with the given distance
	 * @param deltaT meaningful values 0 < val < 1/octaves
	 * @return 
	 */
	[[nodiscard]]
	float getNextValue(float deltaT);
	
};
