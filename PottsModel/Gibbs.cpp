using namespace std;

#include <vector>

#include "Gibbs.h"
#include "Situation.h"
#include "RandomGeneration.h"

uint8_t Gibbs::NewState(vector<double>& probabilities)
{
	for (uint8_t q = 0; q < situation.numberOfStates; q++)
	{
		probabilities[q] = exp(situation.beta * probabilities[q]);
	} // mame citatel uplne podminene pravdepodobnosti

	double sum = 0;
	for (uint8_t q = 0; q < situation.numberOfStates; q++)
	{
		sum += probabilities[q];
	} // v promenne sum mame jmenovatel uplne podminene pravdepodobnosti

	for (uint8_t q = 0; q < situation.numberOfStates; q++)
	{
		probabilities[q] /= sum;
	} // nyni mame v refProbabilities primo uplne podminene pravdepodobnosti

	double random = rn;

	uint8_t q = 0;
	double probability = probabilities[q];
	while (probability < random)
	{
		q++;
		probability += probabilities[q];
	}
	return q;
}

void Gibbs::OneStep()
{
	for (unsigned i = 0; i < numberOfSites; i++)
	{
		OneIteration();
	}
}