#include <iostream>
#include <amp.h>
#include <stdlib.h>

#include "Swarm.h"
#include "FitnessFunctions.h"
#include "GlMain.h"
#include "GenericDescriptors.h"
#include "GenericMetrics.h"

#include <fstream>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

int psoInitialisation(GlMain glMain)
{
	static FitnessFunctions fitnessFunctionLibrary = FitnessFunctions();
	Swarm swarm = Swarm(20, 2, -3, 3, -6, 6);

	for (int g = 0; g < 1000; g++)
	{
		//printf("G %i \n", g);
		if (g == 0)
			for (int i = 0; i < swarm.size; i++)
			{
				// Set personal best
				if ((swarm.particles[i].bestFitness == -1) || (swarm.particles[i].fitness > swarm.particles[i].bestFitness))
				{
					swarm.particles[i].bestPosition = swarm.particles[i].position;
					swarm.particles[i].bestFitness = swarm.particles[i].fitness;
				}
				// Set global best
				if (!(swarm.globalBest.initialised) || (swarm.particles[i].fitness > swarm.globalBest.fitness))
				{
					swarm.globalBest = Particle(swarm.particles[i]);
				}
			}
		else
		{
			concurrency::array_view<Particle, 1> parParticles(swarm.size, swarm.particles);
			concurrency::parallel_for_each(parParticles.extent, [&](int i) restrict(amp)
			{
				// Set personal best
				if ((swarm.particles[i].bestFitness == -1) || (swarm.particles[i].fitness > swarm.particles[i].bestFitness))
				{
					swarm.particles[i].bestPosition = swarm.particles[i].position;
					swarm.particles[i].bestFitness = swarm.particles[i].fitness;
				}
				// Set global best
				if (!(swarm.globalBest.initialised) || (swarm.particles[i].fitness > swarm.globalBest.fitness))
				{
					swarm.globalBest = Particle(swarm.particles[i]);
				}
				// Update particle
				glMain.UpdateDisplay();
				swarm.particles[i].Update(swarm.globalBest, 2.0, 2.0);
				// Evaluate particle
				swarm.particles[i].fitness = fitnessFunctionLibrary.H1(swarm.particles[i]);
			});
		}
	}
	std::cout << "Solution " << swarm.globalBest.position[0] << " " << swarm.globalBest.position[1] << ", Fitness: " << swarm.globalBest.fitness << "\n";
	return 0;
}

int main(int argc, char **argv)
{
	GenericDescriptors descriptorFunctions = GenericDescriptors();
	GenericMetrics metricFunctions = GenericMetrics();
	Assimp::Importer importer;

	//cvDescriptorFunctions.GetSilhouetteImage(cvDescriptorFunctions.ReadImageFromDisk("C:\\Users\\Public\\Pictures\\Sample Pictures\\Desert.jpg"));
	//std::printf("Value: %f \n", cvMetricFunctions.EuclideanDistance(cv::Point(2, 2), cv::Point(1, 1)));

	std::string alpha = "alpha.fbx";
	std::string teapot = "teapot.obj";
	std::string simon = "SIR_SIMON.3ds";

	std::string filename = alpha;

	std::ifstream fin(filename.c_str());
	if (!fin.fail())
		fin.close();
	else
	{
		printf("Couldn't open file: %s\n", filename.c_str());
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	const aiScene* scenePointer = importer.ReadFile(filename, aiProcess_CalcTangentSpace | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | 0);

	if (!scenePointer)
	{
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	printf("Import of scene %s succeeded.\n", filename.c_str());

	GlMain glMain = GlMain(argc, argv, filename, scenePointer);
	int psoSuccess = psoInitialisation(glMain);

	return psoSuccess;
}