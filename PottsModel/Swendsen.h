#pragma once
#include "Simulator.h"

class Swendsen : public Simulator 
{
public:
	string Name();
	void OneStep();
	void Initialize();
	string Type();
};