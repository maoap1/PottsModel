#include <fstream>

#include "Statistics2D.h"
#include "Header.h"

void Statistics2D::ResetVisited()
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			visited[i][j] = false;
		}
	}
}

void Statistics2D::ResetRemaining()
{
	while (!remaining.empty())
	{
		remaining.pop();
	}
}

int Statistics2D::BFSCheck(int otherX, int otherY, uint8_t value)
{
	if ((visited[otherX][otherY] == false) && (lattice[otherX][otherY] == value))
		// point is always visited, so it can not end up in remaining again
	{
		remaining.push(coord2D(otherX, otherY));
		visited[otherX][otherY] = true;
		return 1;
	}
	return 0;
}

void  Statistics2D::BFS(int i, int j)
{
	uint8_t value = lattice[i][j];
	remaining.push(coord2D(i, j));
	visited[i][j] = true;
	int count = 1;
	while (!remaining.empty())
	{
		coord2D point = remaining.front();
		remaining.pop();

		count += BFSCheck(IncreaseIndex(point.x), point.y, value);
		count += BFSCheck(DecreaseIndex(point.x), point.y, value);
		count += BFSCheck(point.x, IncreaseIndex(point.y), value);
		count += BFSCheck(point.x, DecreaseIndex(point.y), value);
	}
	grainSizes.push(count);
}

void Statistics2D::CallingBFS() // Breadth-first search
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			if (visited[i][j] == false)
			{
				BFS(i, j);
			}
		}
	}
}

void Statistics2D::UpdateFrequency(int state, int step)
{
	int count = 0;

	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			count += (lattice[i][j] == state);
		}
	}
	frequencies[step] = count;
}

void Statistics2D::SaveLattice(ofstream& saveFile)
{
	for (int i = 0; i < latticeSize; i++) // i je cislo radku
	{
		for (int j = 0; j < latticeSize; j++) // j je cislo sloupce
		{
			//TODO
			if (lattice[i][j] < 10)
			{
				saveFile << "0";
			}
			//TODO
			saveFile << (unsigned)lattice[i][j] << " ";
		}
		saveFile << endl;
	}
}
