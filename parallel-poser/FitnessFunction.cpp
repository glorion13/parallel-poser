#include "FitnessFunctions.h"

FitnessFunctions::FitnessFunctions(void)
{
}
FitnessFunctions::~FitnessFunctions(void)
{
}

float FitnessFunctions::H1(Particle particle)
{
	/* Simple two-dimensional function containing several local maxima.
	From: The Merits of a Parallel Genetic Algorithm in Solving Hard
	Optimization Problems, A. J. Knoek van Soest and L. J. R. Richard
	Casius, J. Biomech. Eng. 125, 141 (2003)

	.. list-table::
	:widths: 10 50
	:stub-columns: 1

	* - Type
	- maximization
	* - Range
	- :math:`x_i \in [-100, 100]`
	* - Global optima
	- :math:`\mathbf{x} = (8.6998, 6.7665)`, :math:`f(\mathbf{x}) = 2`\n
	* - Function
	- :math:`f(\mathbf{x}) = \\frac{\sin(x_1 - \\frac{x_2}{8})^2 + \
	\\sin(x_2 + \\frac{x_1}{8})^2}{\\sqrt{(x_1 - 8.6998)^2 + \
	(x_2 - 6.7665)^2} + 1}`

	.. plot:: code/benchmarks/h1.py
	:width: 67 %
	*/

	//float num = pow(sin(particle.position[0] - particle.position[1] / 8), 2) + pow(sin(particle.position[1] + particle.position[0] / 8), 2);
	//float denum = pow((pow((particle.position[0] - 8.6998), 2) + pow((particle.position[1] - 6.7665), 2)), 0.5) + 1;

	return (float)((pow(sin(particle.position[0] - particle.position[1] / 8), 2) + pow(sin(particle.position[1] + particle.position[0] / 8), 2)) / (pow((pow((particle.position[0] - 8.6998), 2) + pow((particle.position[1] - 6.7665), 2)), 0.5) + 1));
}