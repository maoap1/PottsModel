#pragma once
#include "Metropolis2D.h"

class Metropolis2DAGG : public Metropolis2D
{
	using Metropolis2D::Metropolis2D;
public:
	string Name();
	string Type();
private:
	bool SiteIsTypeI(uint8_t site);
	void DetermineAccepting(uint8_t newState, uint8_t oldState, vector<uint8_t>& neighbors, int i, int j);
};