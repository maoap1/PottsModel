#include <fstream>

#include "Statistics3D.h"

void Statistics3D::ResetVisited()
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			for (int k = 0; k < latticeSize; k++)
			{
				visited[i][j][k] = false;
			}
		}
	}
}

void Statistics3D::ResetRemaining()
{
	while (!remaining.empty())
	{
		remaining.pop();
	}
}

int Statistics3D::BFSCheck(int otherX, int otherY, int otherZ, uint8_t value)
{
	if ((visited[otherX][otherY][otherZ] == false) && (lattice3[otherX][otherY][otherZ] == value))
		// point is always visited, so it can not end up in remaining again
	{
		remaining.push(coord3D(otherX, otherY, otherZ));
		visited[otherX][otherY][otherZ] = true;
		return 1;
	}
	return 0;
}

void  Statistics3D::BFS(int i, int j, int k)
{
	uint8_t value = lattice3[i][j][k];
	remaining.push(coord3D(i, j, k));
	visited[i][j][k] = true;
	int count = 1;
	while (!remaining.empty())
	{
		coord3D point = remaining.front();
		remaining.pop();

		count += BFSCheck(IncreaseIndex(point.x), point.y, point.z, value);
		count += BFSCheck(DecreaseIndex(point.x), point.y, point.z, value);
		count += BFSCheck(point.x, IncreaseIndex(point.y), point.z, value);
		count += BFSCheck(point.x, DecreaseIndex(point.y), point.z, value);
		count += BFSCheck(point.x, point.y, IncreaseIndex(point.z), value);
		count += BFSCheck(point.x, point.y, DecreaseIndex(point.z), value);
	}
	grainSizes.push(count);
}


void Statistics3D::CallingBFS() // Breadth-first search
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			for (int k = 0; k < latticeSize; k++)
			{
				if (visited[i][j][k] == false)
				{
					BFS(i, j, k);
				}
			}
		}
	}
}

void Statistics3D::UpdateFrequency(int state, int step)
{
	int count = 0;

	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			for (int k = 0; k < latticeSize; k++)
			{
				count += (lattice3[i][j][k] == state);
			}
		}
	}
	frequencies[step] = count;
}

void Statistics3D::SaveLattice(ofstream& saveFile)
{
	for (int i = 0; i < latticeSize; i++) // i je cislo patra
	{
		for (int j = 0; j < latticeSize; j++)
		{
			for (int k = 0; k < latticeSize; k++)
			{
				saveFile << (unsigned)lattice3[i][j][k] << " ";
			}
			saveFile << endl;
		}
		saveFile << endl;
		saveFile << endl;
		saveFile << "Dalsi patro:" << endl;
		saveFile << endl;
	}
}