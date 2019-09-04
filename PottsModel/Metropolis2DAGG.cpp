using namespace std;

#include <vector>

#include "Header.h"
#include "RandomGeneration.h"
#include "Situation.h"
#include "Metropolis2DAGG.h"



bool Metropolis2DAGG::SiteIsTypeI(uint8_t site)
{
	return (site <= situation.C);
}

void Metropolis2DAGG::DetermineAccepting(uint8_t newState, uint8_t oldState, vector<uint8_t>& neighbors, int i, int j)
{
	bool oldStateIsTypeI = SiteIsTypeI(oldState);
	bool siteIsClass1 = false;
	double sum = 0;
	for (int index = 0; index < numberOfNeighbors; index++)
	{
		// this determines whether oldState is class1 or not
		siteIsClass1 = siteIsClass1 || (oldStateIsTypeI != SiteIsTypeI(neighbors[index]));
		sum = sum + (newState == neighbors[index]) - (oldState == neighbors[index]);
	}

	double probability;
	if (siteIsClass1)
	{
		probability = exp(situation.beta * sum);
	}
	else
	{
		double mu = 1 / situation.energyMultiplier;
		if (sum < 0)
		{
			probability = mu * exp(situation.beta * sum);
		}
		else
		{
			probability = mu;
		}
	}
	double random = rn;
	if (random <= probability)
	{
		lattice[i][j] = newState;
	}
}

string Metropolis2DAGG::Name()
{
	if (numberOfNeighbors == 4)
	{
		return "METROPOLIS2D4N_AGG";
	}
	else
	{
		return "METROPOLIS2D8N_AGG";
	}
}

string Metropolis2DAGG::Type()
{
	return "AGG";
}