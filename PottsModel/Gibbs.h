#pragma once
#include <vector>

#include "Simulator.h"


class Gibbs : public Simulator
{
public:
	void OneStep();
protected:
	uint8_t numberOfNeighbors;
	uint8_t NewState(vector<double>& probabilities);
	unsigned numberOfSites; // Toto cislo se bude prepisovat ve 2D jako latticeSize*latticeSize, ve 3D jako latticeSize*latticeSize*latticeSize
	virtual void OneIteration() = 0;
};

