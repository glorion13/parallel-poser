#pragma once

#include <vector>

class Particle
{
public:
	Particle(void);
	~Particle(void);

	Particle(int size, float smin, float smax, float pmin, float pmax);

	int size;
	bool initialised;

	float fitness;
	std::vector<float> velocity;
	std::vector<float> position;

	float bestFitness;
	std::vector<float> bestPosition;

	float velocityMinimum;
	float velocityMaximum;
	float positionMinimum;
	float positionMaximum;

	int Update(Particle globalBest, float phi1, float phi2);

	int BasicUpdateFunction(Particle globalBest, float phi1, float phi2);
};