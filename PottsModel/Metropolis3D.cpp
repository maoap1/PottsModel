using namespace std;

#include <vector>

#include "Header.h"
#include "RandomGeneration.h"
#include "Situation.h"
#include "Metropolis3D.h"


void OneMetropolisIteration3D()
{
	long x = DiscreteUniformNumber((long)latticeSize * (long)latticeSize * (long)latticeSize);
	unsigned i = x / (latticeSize*latticeSize);
	x = x % (latticeSize * latticeSize);
	unsigned j = x / latticeSize;
	unsigned k = x % latticeSize;

	uint8_t newState = RandomState(situation.numberOfStates);
	uint8_t oldState = lattice3[i][j][k];

	vector<uint8_t> neighbors(6, 0); // initializes the whole vector to zeros

	// This is deprecated version. Normally it is with DecreaseIndex(int index) and IncreaseIndex(int index)
	neighbors[0] = lattice3[(latticeSize + i - 1) % latticeSize][j][k]; // up
	neighbors[1] = lattice3[(latticeSize + i + 1) % latticeSize][j][k]; // down
	neighbors[2] = lattice3[i][(latticeSize + j - 1) % latticeSize][k]; // left
	neighbors[3] = lattice3[i][(latticeSize + j + 1) % latticeSize][k]; // right
	neighbors[4] = lattice3[i][j][(latticeSize + k + 1) % latticeSize]; // top
	neighbors[5] = lattice3[i][j][(latticeSize + k - 1) % latticeSize]; // bottom

	int sum = 0;
	for (int index = 0; index < 6; index++)
	{
		sum = sum + (newState == neighbors[index]) - (oldState == neighbors[index]);
	}
	double probability = exp(situation.beta * sum);
	double random = rn;
	if (random <= probability)
	{
		lattice3[i][j][k] = newState;
	}
}

void MetropolisStep3D()
{
	for (long i = 0; i < latticeSize * latticeSize * latticeSize; i++)
	{
		OneMetropolisIteration3D();
	}
}

void Metropolis3D::OneStep()
{
	MetropolisStep3D();
}

string Metropolis3D::Name()
{
	return "METROPOLIS";
}