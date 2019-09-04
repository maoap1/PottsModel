#pragma once
#include "Simulator.h"

class Metropolis3D : public Simulator
{
public:
	string Name();
	void OneStep();
};