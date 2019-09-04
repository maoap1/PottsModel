using namespace std;

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <queue>

#include "Header.h"
#include "Situation.h"
#include "RandomGeneration.h"
#include "Coord2D.h"

#include "Statistics.h"
#include "Rendering.h"

#include "Metropolis2DAGG.h"


void Statistics::StartTimeStamp()
{
	stringstream ss;
	auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
#pragma warning(suppress : 4996)
	ss << ctime(&timenow);
	startTime = ss.str();
}

void Statistics::Reset()
{
	ResetVisited();
	while (!grainSizes.empty())
	{
		grainSizes.pop();
	}
	ResetRemaining();
}

void Statistics::SaveGrainsToFile(ofstream& saveFile)
{
	while (!grainSizes.empty())
	{
		saveFile << grainSizes.top() << endl;
		grainSizes.pop();
	}
}

void Statistics::SaveToFile(int number, int steps, int type)
/// nyni pro jednoduchost rozdeleno podle typu, pozdeji by bylo rozumejsi udelat na kazdy ruzny typ ukladani vlastni tridu
/// type 1 ... GrainSize
/// type 2 ... Frequency
/// type 3 ... Lattice
{
	ofstream saveFile;
	stringstream ss;
	switch (type)
	{
	case 1:
		ss << "grains";
		break;
	case 2:
		ss << "frequency";
		break;	
	case 3:
		ss << "lattice";
		break;
	default:
		ss << "undefined";
		break;
	}
	ss << number << ".txt";
	string str = ss.str();
	saveFile.open(str, ios::out | ios::trunc);
	saveFile << "% Start: " << startTime;
#pragma region TimeStamp
	{
		auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
#pragma warning(suppress : 4996)
		saveFile << "% End: " << ctime(&timenow);
	}
#pragma endregion

	saveFile << "% mode: ";
#ifdef _2D
	saveFile << "2D, ";
#endif // _2D
#ifdef _3D
	saveFile << "3D, ";
#endif // _3D
	saveFile << algorithm->Name();
	saveFile << endl;
	saveFile << "% size: " << latticeSize << endl;
	saveFile << "% steps: " << steps << endl;
	saveFile << "% states: " << (unsigned)situation.numberOfStates << endl;
	saveFile << "% beta: " << situation.beta << endl;
	if (algorithm->Type() == "AGG")
	{
		saveFile << "% C: " << (unsigned)situation.C << endl;
		saveFile << "% Energy Multiplier: " << situation.energyMultiplier << endl;
	}


	switch (type)
	{
	case 1:
		SaveGrainsToFile(saveFile);
		break;
	case 2:
		for (unsigned int i = 0; i < situation.howManySteps; i++) // TODO neni zde chyba? tj. opravdu chceme az do howManySteps?
		{
			saveFile << frequencies[i] << endl;
		}
		break;
	case 3:
		SaveLattice(saveFile);
		break;
	default:
		break;
	}

	saveFile << endl;
	saveFile.close();
}

void Statistics::GrainCounting(int number, int steps)
{
	Reset();
	CallingBFS();
	SaveToFile(number, steps, 1); // 1 znamena grainCounting
								  // je to pouze docasne reseni, casem to rozdelim na tridy podle toho, co to dela
}

void Statistics::PrintToFile(int number, int steps)
{
	//SaveToFile(number, steps, 3); // 3 means saving lattice 
	// TODO


	stringstream ss;
	ss << "A/lattice" << setfill('0') << setw(6) << number << ".png";
	SaveLatticePicture(ss.str(), situation.numberOfStates);
}

void Statistics::SaveFrequencyToFile()
{
	SaveToFile(1, situation.howManySteps, 2); // 2 means saving frequencies 
}

void Statistics::InitializeStatistics()
{
	StartTimeStamp();
	frequencies = vector<int>(situation.howManySteps, 0); // TODO opravdu tak velke?
}


