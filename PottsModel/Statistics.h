#pragma once
using namespace std;

#include <vector>
#include <queue>
#include <fstream>

#include "LatticeManipulator.h"

class Statistics : public LatticeManipulator
{
public:
	void GrainCounting(int number, int steps);
	void SaveFrequencyToFile();
	void PrintToFile(int number, int steps);
	void InitializeStatistics();
	virtual void UpdateFrequency(int state, int step) = 0;
protected:
	virtual void Reset();
	virtual void ResetVisited() = 0;
	virtual void ResetRemaining() = 0;
	virtual void CallingBFS() = 0;
	virtual void SaveLattice(ofstream& saveFile) = 0;

	vector<int> frequencies;
	string startTime;
	priority_queue<int> grainSizes;

private:
	void StartTimeStamp();
	void SaveToFile(int number, int steps, int type);
	void SaveGrainsToFile(ofstream& saveFile);
};

