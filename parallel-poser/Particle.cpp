#include <amp.h>

#include "Particle.h"

Particle::Particle(void)
{
}
Particle::~Particle(void)
{
}

Particle::Particle(int size, float smin, float smax, float pmin, float pmax)
{
	// Particle initialisation
	for (int i = 0; i < size; i++)
	{
		velocity.push_back(((float)rand() / ((float)RAND_MAX / smax)) + smin);
		position.push_back(((float)rand() / ((float)RAND_MAX / pmax)) + pmin);
	}
	this->velocityMinimum = smin;
	this->velocityMaximum = smax;
	this->velocityMinimum = pmin;
	this->velocityMaximum = pmax;

	this->size = size;

	fitness = -1;
	bestFitness = -1;

	initialised = true;
}

int Particle::Update(Particle globalBest, float phi1, float phi2)
{
	return BasicUpdateFunction(globalBest, phi1, phi2);
}

int Particle::BasicUpdateFunction(Particle globalBest, float phi1, float phi2)
{	
	if (globalBest.initialised)
	{
		concurrency::array_view<float, 1> parVelocity(size, velocity);
		concurrency::array_view<float, 1> parPosition(size, position);
		concurrency::array_view<const float,1 > parGlobalBestPosition(size, globalBest.position);
		concurrency::array_view<const float, 1> parBestPosition(size, bestPosition);

		concurrency::parallel_for_each(parVelocity.extent,
			[=](concurrency::index<1> i)
			restrict(amp)
		{
			float u1 = (float) rand() / ((float) RAND_MAX / phi1);
			float u2 = (float) rand() / ((float) RAND_MAX / phi2);

			// Update velocity
			parVelocity[i] += u1 * (parBestPosition[i] - parPosition[i]) + u2 * (parGlobalBestPosition[i] - parPosition[i]);

			// Check for minimum and maximum velocities
			if (parVelocity[i] < velocityMinimum)
				parVelocity[i] = velocityMinimum;
			if (parVelocity[i] > velocityMaximum)
				parVelocity[i] = velocityMaximum;

			// Update position
			parPosition[i] += parVelocity[i];

			// Check for minimum and maximum positions
		});
	}
	return 0;
}