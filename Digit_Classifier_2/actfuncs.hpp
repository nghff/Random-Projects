// Activation Functions
// below contains activation functions used by neural networks
#include <cmath>
#pragma once

// TODO: try leaky?
double fReLU(double in)
{
	return (in > 0.0) ? in : (in * 0.075);
}

double bReLU(double in)
{
	return ((in > 0.0) ? 1.0 : 0.075);
}

double fsigmoid(double in)
{
	return (in / (1.0 + abs(in)) + 1.0) / 2.0;
}

double bsigmoid(double in)
{
	return 1.0 / (2 * (abs(in) + 1) * (abs(in) + 1));
}