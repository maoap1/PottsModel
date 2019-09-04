#include "Metropolis.h"

void Metropolis::OneStep()
{
	for (unsigned i = 0; i < numberOfSites; i++)
	{
		OneIteration();
	}
}

