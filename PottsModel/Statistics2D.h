#pragma once
#include <fstream>

#include "Statistics.h"
#include "Coord2D.h"
#include "Header.h"

class Statistics2D : public Statistics
{
public:
	void UpdateFrequency(int state, int step);
private:
	void ResetVisited();
	void ResetRemaining();
	void CallingBFS();

	void BFS(int i, int j);
	int BFSCheck(int otherX, int otherY, uint8_t value);

	void SaveLattice(ofstream& saveFile);

	bool visited[latticeSize][latticeSize];
	queue<coord2D> remaining;
};

