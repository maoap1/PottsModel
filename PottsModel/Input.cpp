using namespace std;

#include <iostream>
#include <sstream>

#include "Header.h"
#include "Situation.h"
#include "Statistics2D.h"  // TODO ... podle me by melo byt spis v Simulation
#include "Statistics3D.h"  // TODO ... podle me by melo byt spis v Simulation
#include "Rendering.h"

#include "Gibbs2D.h"
#include "Gibbs3D.h"
#include "Metropolis.h"
#include "Metropolis2D.h"
#include "Metropolis2DAGG.h"
#include "Metropolis3D.h"
#include "Mixing2D.h"
#include "Swendsen.h"

Situation situation;

Statistics* statistics;
Simulator* algorithm;
Simulator* burnInAlgorithm;

#ifdef _2D
Statistics2D statisticsSpecified;
#endif // _2D

#ifdef _3D
Statistics3D statisticsSpecified;
#endif // _3D

// 2D

Swendsen swendsen;

Gibbs2D gibbs4N(4);
Gibbs2D gibbs8N(8);
Metropolis2D metropolis4N(4);
Metropolis2D metropolis8N(8);
Metropolis2DAGG metropolisAGG4N(4);
Metropolis2DAGG metropolisAGG8N(8);
Mixing2D mixing4N(4);
Mixing2D mixing8N(8);

// 3D
Gibbs3D gibbs6N(6);
Gibbs3D gibbs18N(18);
Gibbs3D gibbs26N(26);


void InitializeSwendsen()
{
	algorithm = &swendsen;
}

void InitializeGibbs4N()
{
	algorithm = &gibbs4N;
}

void InitializeGibbs8N()
{
	algorithm = &gibbs8N;
}

void InitializeGibbs6N()
{
	algorithm = &gibbs6N;
}

void InitializeGibbs18N()
{
	algorithm = &gibbs18N;
}

void InitializeGibbs26N()
{
	algorithm = &gibbs26N;
}

void InitializeMetropolis4N()
{
	algorithm = &metropolis4N;
}

void InitializeMetropolis8N()
{
	algorithm = &metropolis8N;
}

void InitializeMetropolisAGG4N()
{
	algorithm = &metropolisAGG4N;
}

void InitializeMetropolisAGG8N()
{
	algorithm = &metropolisAGG8N;
}

void InitializeMetropolisBurnIn4N()
{
	burnInAlgorithm = &metropolis4N;
}

void InitializeMetropolisBurnIn8N()
{
	burnInAlgorithm = &metropolis8N;
}

void InitializeMixing4N()
{
	algorithm = &mixing4N;
}

void InitializeMixing8N()
{
	algorithm = &mixing8N;
}

void InitializeStatistics()
{
	statistics = &statisticsSpecified;
}

#ifdef _2D

void SelectingGibbs()
{
	cout << "Specifikujte jaky Gibbs (1 4Neighbors , 2 8Neighbors):" << endl;
	int type;
	cin >> type;
	switch (type)
	{
	case 1:
		InitializeGibbs4N();
		break;
	case 2:
		InitializeGibbs8N();
		break;
	default:
		cout << "Zadali jste spatne. Zkuste znovu" << endl;
		SelectingGibbs();
		break;
	}
}
#endif // _2D

#ifdef _3D
void SelectingGibbs()
{
	cout << "Specifikujte jaky Gibbs (1 6Neighbors , 2 18Neighbors, 3 26Neighbors):" << endl;
	int type;
	cin >> type;
	switch (type)
	{
	case 1:
		InitializeGibbs6N();
		break;
	case 2:
		InitializeGibbs18N();
		break;
	case 3:
		InitializeGibbs26N();
		break;
	default:
		cout << "Zadali jste spatne. Zkuste znovu" << endl;
		SelectingGibbs();
		break;
	}
}
#endif // _3D

void SelectingMetropolis()
{
	cout << "Specifikujte jaky Metropolis (1 4Neighbors , 2 8Neighbors, 3 AGG4Neighbors, 4 AGG8Neighbors):" << endl;
	int type;
	cin >> type;
	switch (type)
	{
	case 1:
		InitializeMetropolis4N();
		break;
	case 2:
		InitializeMetropolis8N();
		break;
	case 3:
		InitializeMetropolisBurnIn4N();
		InitializeMetropolisAGG4N();
		break;
	case 4:
		InitializeMetropolisBurnIn8N();
		InitializeMetropolisAGG8N();
		break;
	default:
		cout << "Zadali jste spatne. Zkuste znovu" << endl;
		SelectingMetropolis();
		break;
	}
}

void SelectingMixing()
{
	cout << "Specifikujte jaky Mixing (1 4Neighbors , 2 8Neighbors):" << endl;
	int type;
	cin >> type;
	switch (type)
	{
	case 1:
		InitializeMixing4N();
		break;
	case 2:
		InitializeMixing8N();
		break;
	default:
		cout << "Zadali jste spatne. Zkuste znovu" << endl;
		SelectingMixing();
		break;
	}
}

void SelectingSwendsen()
{
	InitializeSwendsen();
}

void SelectAlgorithm()
{
#ifdef _3D
	cout << "Funkcni ve 3D je pouze Gibbs!!!" << endl;
#endif // _3D

	cout << "Vyberte algoritmus (1 Gibbs, 2 Metropolis, 3 Mixing, 4 Swendsen-Wang):" << endl;

	int type;
	cin >> type;

	switch (type)
	{
	case 1:
		SelectingGibbs();
		break;
	case 2:
		SelectingMetropolis();
		break;
	case 3:
		SelectingMixing();
		break;
	case 4:
		SelectingSwendsen();
		break;
	default:
		cout << "Zadali jste spatne. Zkuste znovu" << endl;
		SelectAlgorithm();
		break;
	}
}

void AGGSetup()
{
	cout << "Parametr C (Predel typu zrn): ";
	unsigned parC;
	cin >> parC;
	situation.C = (uint8_t)parC;

	cout << "Energy multiplier: ";
	cin >> situation.energyMultiplier;
}

void InitializeByConsoleFast() // Almost no asking
{

	SelectAlgorithm();

	cout << "Rezim: ";

#ifdef _2D
	cout << "2D";
#endif // _2D

#ifdef _3D
	cout << "3D";
#endif // _3D

	cout << ", ";
	
	InitializeStatistics();
	
	cout << algorithm->Name();
	cout << endl << "Velikost mrizky: " << latticeSize << endl << "Dalsi parametry zadejte. " << endl;

	cout << "Pocet iteraci BurnIn: ";
	if (algorithm->Type() == "AGG")
	{
		cin >> situation.burnIn;
	}
	else
	{
		situation.burnIn = 0;
	}
	cout << situation.burnIn << endl;

	cout << "Pocet iteraci: ";
	cin >> situation.howManySteps;
	//situation.howManySteps = 1000; // 50000
	cout << situation.howManySteps << endl;

	cout << "Po kolika iteracich pocitat zrna: ";
	//situation.grainCountingSavingInterval = 0;//0
	cin >> situation.grainCountingSavingInterval;
	cout << situation.grainCountingSavingInterval << endl;

	cout << "Po kolika iteracich spocitat frekvenci barev: ";
	situation.colorFrequenciesSavingInterval = 1;
	cout << situation.colorFrequenciesSavingInterval << endl;




	cout << "Po kolika iteracich ukladat mrizku: ";
	//situation.latticeSavingInterval = 1;//1
#ifdef _2D
	cin >> situation.latticeSavingInterval;
#endif // _2D

#ifdef _3D
	situation.latticeSavingInterval = 0;
#endif // _3D

	cout << situation.latticeSavingInterval << endl;

	cout << "Po kolika iteracich vypisovat procenta: ";
	//situation.percentageDisplayInterval = 1; // 500
	situation.percentageDisplayInterval = situation.howManySteps/1000;
	cout << situation.percentageDisplayInterval << endl;

	cout << "Pocet stavu (= Q) [1 - 255]: ";
	unsigned states;
	cin >> states;
	situation.numberOfStates = (uint8_t)states;
	//situation.numberOfStates = 48; // 8
	cout << (unsigned)situation.numberOfStates << endl;

	cout << "Parametr beta: ";
	cin >> situation.beta;

	if (algorithm->Type() == "MIXING")
	{
		cout << "Parametr p: ";
		cin >> situation.p;
	}

	if (situation.burnIn > 0)
	{
		if (burnInAlgorithm->Type() == "MIXING")
		{
			cout << "Parametr p pro burnIn: ";
			cin >> situation.burnInP;
		}
	}

	if (algorithm->Type() == "AGG")
	{
		AGGSetup();
	}

	int load;
#ifdef _2D
	stringstream ss;
	ss << "Load" << (unsigned)situation.numberOfStates << ".png";
	cout << "Pro nacteni z " << ss.str() << " zadejte 1: ";
	cin >> load;
#endif // _2D
#ifdef _3D
	load = 0;
#endif // _3D

	if (load == 1)
	{
		LoadLatticeFromFile(ss.str(), situation.numberOfStates);
	}
	else
	{
		algorithm->Initialize();
	}

	cout << "Pracuji ..." << endl;

}

/* DEPRECATED
void InitializeByConsoleSlow() // Asking everything
{
	cout << "Rezim: 2D, "; //TODO 2D vs 3D
	cout << "Vyberte algoritmus:"; // TODO jak?
	InitializeMetropolis(); // TODO prozatim
	cout << algorithm->Name();
	cout << endl << "Velikost mrizky: " << latticeSize << endl << "Dalsi parametry zadejte. " << endl;

	cout << "Pocet iteraci BurnIn: ";
	cin >> situation.burnIn;
	cout << situation.burnIn << endl;

	cout << "Pocet iteraci: ";
	cin >> situation.howManySteps;
	cout << situation.howManySteps << endl;

	cout << "Po kolika iteracich pocitat zrna: ";
	cin >> situation.grainCountingSavingInterval;
	cout << situation.grainCountingSavingInterval << endl;

	cout << "Po kolika iteracich spocitat frekvenci barev: ";
	cin >> situation.colorFrequenciesSavingInterval;
	cout << situation.colorFrequenciesSavingInterval << endl;

	cout << "Po kolika iteracich ukladat mrizku: ";
	cin >> situation.latticeSavingInterval;
	cout << situation.latticeSavingInterval << endl;

	cout << "Po kolika iteracich vypisovat procenta: ";
	cin >> situation.percentageDisplayInterval;
	cout << situation.percentageDisplayInterval << endl;

	cout << "Pocet stavu (= Q) [1 - 255]: ";
	cin >> situation.numberOfStates;
	cout << situation.numberOfStates << endl;

	cout << "Parametr beta: ";
	cin >> situation.beta;

	if (algorithm->Name() == "MIXING")
	{
		cout << "Parametr p: ";
		cin >> situation.p;
	}

	if (burnInAlgorithm->Name() == "MIXING")
	{
		cout << "Parametr p pro burnIn: ";
		cin >> situation.burnInP;
	}
	cout << "Pracuji ..." << endl;



}
*/


/* ZATIM NIC NEDELA
#include <fstream>
void Load2DFromFile(string fileName)
{
	ifstream file;
	file.open(fileName, ifstream::in);
	//file.getline();
	//file.get();
	file.close();
}
*/