#pragma once

#include "Particle.h"

class Swarm
{
public:
	Swarm(void);
	~Swarm(void);

	Swarm(int swarmSize, int particleSize, float smin, float smax, float pmin, float pmax);

	int size;
	Particle globalBest;
	std::vector<Particle> particles;
	std::vector<Particle> globalBestParticles;
};

