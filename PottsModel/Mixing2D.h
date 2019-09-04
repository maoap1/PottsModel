#pragma once
#include "Gibbs2D.h"

class Mixing2D : public Gibbs2D
{
	using Gibbs2D::Gibbs2D;
public:
	string Name();
	string Type();
	void OneStep();
};