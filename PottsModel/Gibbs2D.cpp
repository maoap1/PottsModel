using namespace std;

#include <vector>

#include "Header.h"
#include "Situation.h"
#include "Gibbs2D.h"
#include "RandomGeneration.h"

Gibbs2D::Gibbs2D(unsigned neighbors)
{
	numberOfSites = latticeSize * latticeSize;

	if ((neighbors == 4)||(neighbors == 8))
	{
		numberOfNeighbors = neighbors;
	}
	else
	{
		throw invalid_argument("In Gibbs2D only 4 or 8 neighbors are allowed");
	}
}

void Gibbs2D::OneIteration()
{
	int i = DiscreteUniformNumber(latticeSize);
	int j = DiscreteUniformNumber(latticeSize);

	vector<double> probabilities(situation.numberOfStates, 0); // initializes the whole vector to zeros
	probabilities[lattice[DecreaseIndex(i)][j]]++; // up
	probabilities[lattice[IncreaseIndex(i)][j]]++; // down
	probabilities[lattice[i][DecreaseIndex(j)]]++; // left
	probabilities[lattice[i][IncreaseIndex(j)]]++; // right
	
	if (numberOfNeighbors == 8)
	{
		probabilities[lattice[DecreaseIndex(i)][DecreaseIndex(j)]]++; // top left
		probabilities[lattice[DecreaseIndex(i)][IncreaseIndex(j)]]++; // top right
		probabilities[lattice[IncreaseIndex(i)][DecreaseIndex(j)]]++; // down left
		probabilities[lattice[IncreaseIndex(i)][IncreaseIndex(j)]]++; // down right
	}

	lattice[i][j] = NewState(probabilities);
}

string Gibbs2D::Name()
{
	if (numberOfNeighbors == 4)
	{
		return "GIBBS2D4N";
	}
	else
	{
		return "GIBBS2D8N";
	}
}