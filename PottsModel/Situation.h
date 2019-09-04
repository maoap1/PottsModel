#pragma once

struct Situation
{
	unsigned howManySteps;
	uint8_t numberOfStates, C;
	double beta, p, burnInP, energyMultiplier;
	int burnIn;
	int grainCountingSavingInterval, latticeSavingInterval, percentageDisplayInterval, colorFrequenciesSavingInterval;
};

extern Situation situation;