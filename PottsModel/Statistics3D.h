#pragma once
#include <fstream>

#include "Statistics.h"
#include "Coord3D.h"
#include "Header.h"

class Statistics3D : public Statistics
{
public:
	void UpdateFrequency(int state, int step);
private:
	void ResetVisited();
	void ResetRemaining();
	void CallingBFS();

	void BFS(int i, int j, int k);
	int BFSCheck(int otherX, int otherY, int otherZ, uint8_t value);

	void SaveLattice(ofstream& saveFile);

	bool visited[latticeSize][latticeSize][latticeSize];
	queue<coord3D> remaining;

};

