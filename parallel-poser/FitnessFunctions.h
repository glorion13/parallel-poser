#pragma once

#include "Particle.h"

class FitnessFunctions
{
public:
	FitnessFunctions(void);
	~FitnessFunctions(void);

	float H1(Particle particle);
};

