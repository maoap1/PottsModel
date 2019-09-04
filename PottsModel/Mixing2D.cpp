using namespace std;

#include <vector>

#include "Header.h"
#include "RandomGeneration.h"
#include "Situation.h"
#include "Mixing2D.h"

void PermutationStep2D()
{
	vector<uint8_t> permutation(situation.numberOfStates, 0); // initializes the whole vector to zeros
	for (uint8_t i = 0; i < situation.numberOfStates; i++)
	{
		permutation[i] = i;
	}
	for (uint8_t i = 0; i < situation.numberOfStates - 1; i++)
	{
		uint8_t j = i + RandomState(situation.numberOfStates - i);
		uint8_t temp = permutation[i];
		permutation[i] = permutation[j];
		permutation[j] = temp;
	}
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			lattice[i][j] = permutation[lattice[i][j]];
		}
	}
}

void Mixing2D::OneStep()
{
	double random = rn;
	if (random < situation.p)
	{
		Gibbs2D::OneStep();
	}
	else
	{
		PermutationStep2D();
	}
}

string Mixing2D::Name()
{
	return "MIXING2D";
}

string Mixing2D::Type()
{
	return "MIXING";
}