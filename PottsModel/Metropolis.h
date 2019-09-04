#pragma once
#include "Simulator.h"

class Metropolis : public Simulator
{
public:
	virtual string Name() = 0;
	void OneStep();
protected:
	unsigned numberOfSites; // Toto cislo se bude prepisovat ve 2D jako latticeSize*latticeSize, ve 3D jako latticeSize*latticeSize*latticeSize
	uint8_t numberOfNeighbors;
	virtual void OneIteration() = 0;
};