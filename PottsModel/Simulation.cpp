using namespace std;

#include <iostream>
#include <iomanip>
#include <sstream>

#include "Header.h"
#include "Situation.h"
#include "Statistics.h"

#include "Swendsen.h"
#include "Mixing2D.h"

#include "Rendering.h"

void BurnIn()
{
	cout << "Burn In." << endl;
	for (int i = 0; i < situation.burnIn; i++)
	{
		if ((situation.percentageDisplayInterval != 0) && (i % situation.percentageDisplayInterval == 0))
		{
			cout << "BurnIn " << setprecision(6) << 100 * (double)(i) / situation.burnIn << " %." << endl;
		}
		burnInAlgorithm->OneStep();
	}
}

void Simulate()
{
	cout << "Simulation started." << endl;

	int number = 1;
	int saveNumber = 1;
	int frequencyNumber = 1;
	for (unsigned int i = 0; i < situation.howManySteps; i++)
	{
		if ((situation.percentageDisplayInterval != 0) && (i % situation.percentageDisplayInterval == 0))
		{
			cout << "Hotovo " << setprecision(6) << 100 * (double)(i) / situation.howManySteps << " %." << endl;
		}
		algorithm->OneStep();
		if ((situation.grainCountingSavingInterval != 0) && (i % situation.grainCountingSavingInterval == 0))
		{
			statistics->GrainCounting(number++, i);
		}
		if ((situation.colorFrequenciesSavingInterval != 0) && (i % situation.colorFrequenciesSavingInterval == 0))
		{
			statistics->UpdateFrequency(1, i); // We would like to count states with number 1
		}
		if ((situation.latticeSavingInterval != 0) && (i % situation.latticeSavingInterval == 0))
		{
			statistics->PrintToFile(saveNumber++, i);
		}
	}
	cout << "Hotovo 100 %." << endl;
	cout << " - Konec simulace ... ";

	if (situation.grainCountingSavingInterval != 0)
	{
		statistics->GrainCounting(number, situation.howManySteps);
	}
	if (situation.latticeSavingInterval != 0)
	{
		statistics->PrintToFile(saveNumber, situation.howManySteps);
	}
	if (situation.colorFrequenciesSavingInterval != 0)
	{
		statistics->SaveFrequencyToFile();
	}

#ifdef _2D
	stringstream ss;
	ss << "WithoutBlack" << (unsigned)situation.numberOfStates << ".png";
	SaveLatticeWithoutWhite(ss.str(), situation.numberOfStates);
#endif // _2D
}

void DoSimulation()
{
	statistics->InitializeStatistics();

	if (algorithm->Type() == "SWENDSEN")
	{
		situation.p = 1 - exp(-situation.beta);
	}

	if (situation.burnIn > 0)
	{
		double temp_p = situation.p;
		if (algorithm->Type() == "MIXING")
		{
			situation.p = situation.burnInP;
		}

		if (algorithm->Type() == "SWENDSEN")
		{
			situation.p = 1 - exp(-situation.beta);
		}
		burnInAlgorithm->Initialize();
		BurnIn();
		situation.p = temp_p;
	}

	Simulate();
	cout << "Konec zapisu " << endl;
}