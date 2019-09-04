using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Header.h"
#include "Situation.h"



void Print2DToConsole()
{
	for (int i = 0; i < latticeSize; i++) // i je cislo radku
	{
		for (int j = 0; j < latticeSize; j++) // j je cislo sloupce
		{
			cout << lattice[i][j] << " ";
		}
		cout << endl;
	}
}

/*
void SaveNumberOfStates(int number, int steps) // Nepouzivane, ale mohlo by se pouzit
{
	vector<int> frequency(situation.numberOfStates, 0);
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			frequency[lattice[i][j]]++;
		}
	}

	ofstream saveFile;
	stringstream ss;
	ss << "frequency" << number << ".txt";
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

	saveFile << "% mode: 2D, ";

	saveFile << algorithm->Name();
	saveFile << endl;
	saveFile << "% size: " << latticeSize << endl;
	saveFile << "% steps: " << steps << endl;
	saveFile << "% states: " << situation.numberOfStates << endl;
	saveFile << "% beta: " << situation.beta << endl;
	for (unsigned i = 0; i < situation.numberOfStates; i++)
	{
		saveFile << i << " " << frequency[i] << endl;
	}
	saveFile << endl;
	saveFile.close();
}
*/