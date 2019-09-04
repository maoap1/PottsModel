#pragma once
#include "Metropolis.h"

class Metropolis2D : public Metropolis
{
public:
	virtual string Name();
	Metropolis2D(unsigned neighbors);
protected:
	void OneIteration();
	virtual void DetermineAccepting(uint8_t newState, uint8_t oldState, vector<uint8_t> & neighbors, int i, int j);
};