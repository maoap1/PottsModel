#pragma once
#include "Gibbs.h"

class Gibbs3D : public Gibbs // Gibbs systematic sampler
{
public:
	Gibbs3D(unsigned neighbors);
	string Name();
private:
	void OneIteration();
};
