using namespace std;

#include <vector>

#include "Header.h"
#include "RandomGeneration.h"
#include "Situation.h"
#include "Metropolis2D.h"

Metropolis2D::Metropolis2D(unsigned neighbors)
{
	numberOfNeighbors = neighbors;
	numberOfSites = latticeSize * latticeSize;
}

void Metropolis2D::DetermineAccepting(uint8_t newState, uint8_t oldState, vector<uint8_t>& neighbors, int i, int j)
{
	int sum = 0;
	for (int index = 0; index < numberOfNeighbors; index++)
	{
		sum = sum + (newState == neighbors[index]) - (oldState == neighbors[index]);
	}

	double probability = exp(situation.beta * sum);
	double random = rn;
	if (random <= probability)
	{
		lattice[i][j] = newState;
	}
}

void Metropolis2D::OneIteration()
{
	int i = DiscreteUniformNumber(latticeSize);
	int j = DiscreteUniformNumber(latticeSize);

	uint8_t newState = RandomState(situation.numberOfStates);
	uint8_t oldState = lattice[i][j];

	vector<uint8_t> neighbors(numberOfNeighbors, 0); // initializes the whole vector to zeros
	neighbors[0] = lattice[DecreaseIndex(i)][j]; // up
	neighbors[1] = lattice[IncreaseIndex(i)][j]; // down
	neighbors[2] = lattice[i][DecreaseIndex(j)]; // left
	neighbors[3] = lattice[i][IncreaseIndex(j)]; // right
	if (numberOfNeighbors == 8)
	{
		neighbors[4] = lattice[DecreaseIndex(i)][DecreaseIndex(j)]; // top left
		neighbors[5] = lattice[DecreaseIndex(i)][IncreaseIndex(j)]; // top right
		neighbors[6] = lattice[IncreaseIndex(i)][DecreaseIndex(j)]; // down left
		neighbors[7] = lattice[IncreaseIndex(i)][IncreaseIndex(j)]; // down right
	}

	DetermineAccepting(newState, oldState, neighbors, i, j);
}


string Metropolis2D::Name()
{
	if (numberOfNeighbors == 4)
	{
		return "METROPOLIS2D4N";
	}
	else
	{
		return "METROPOLIS2D8N";
	}
}