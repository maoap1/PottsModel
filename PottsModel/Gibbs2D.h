#pragma once
#include "Gibbs.h"

class Gibbs2D : public Gibbs // Gibbs systematic sampler
{
public:
	Gibbs2D(unsigned neighbors);
	string Name();
private:
	void OneIteration();
};
