#include "Swarm.h"

Swarm::Swarm(void)
{
}
Swarm::~Swarm(void)
{
}

Swarm::Swarm(int swarmSize, int particleSize, float smin, float smax, float pmin, float pmax)
{
	this->size = swarmSize;
	for (int i = 0; i < swarmSize; i++)
	{
		particles.push_back(Particle(particleSize, smin, smax, pmin, pmax));
	}
	globalBest.initialised = false;
}