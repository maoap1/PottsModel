#pragma once
using namespace std;

#include <string>

#include "LatticeManipulator.h"

class Simulator : public LatticeManipulator
{
public:
	virtual string Name() = 0;
	virtual void OneStep() = 0;
	virtual string Type();
	virtual void Initialize();
};
