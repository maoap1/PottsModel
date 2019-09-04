using namespace std;

#include <queue>

#include "Header.h"
#include "RandomGeneration.h"
#include "Swendsen.h"
#include "Situation.h"
#include "Coord2D.h"


bool horizontal[latticeSize][latticeSize];
bool vertical[latticeSize][latticeSize];

void SwendsenBondStep2D()
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			if (lattice[i][j] == lattice[i][(latticeSize + j + 1) % latticeSize])
			{
				double random = rn;
				if (random < situation.p)
				{
					horizontal[i][j] = 1;
				}
				else
				{
					horizontal[i][j] = 0;
				}
			}
			else
			{
				horizontal[i][j] = 0;
			}
			if (lattice[i][j] == lattice[(latticeSize + i + 1) % latticeSize][j])
			{
				double random = rn;
				if (random < situation.p)
				{
					vertical[i][j] = 1;
				}
				else
				{
					vertical[i][j] = 0;
				}
			}
			else
			{
				vertical[i][j] = 0;
			}
		}
	}
}

bool visited[latticeSize][latticeSize];
queue<coord2D> remaining;

// i,j souradnice hran; i,y souradnice sousedniho vrcholu
// nespecifikovane y => y polozi rovno j
void BFSHorizontalCheck(int i, int j, int y = -1)
{
	if (y == -1)
	{
		y = j;
	}
	if ((visited[i][y] == false) && (horizontal[i][j]))
	{
		visited[i][y] = true;
		remaining.push(coord2D(i, y));
	}
}

// i,j souradnice hran; x,j souradnice sousedniho vrcholu
// nespecifikovane x => x polozi rovno i
void BFSVerticalCheck(int i, int j, int x = -1)
{
	if (x == -1)
	{
		x = i;
	}
	if ((visited[x][j] == false) && (vertical[i][j]))
	{
		visited[x][j] = true;
		remaining.push(coord2D(x, j));
	}
}

void BFS(int i, int j)
{
	remaining.push(coord2D(i, j));
	visited[i][j] = true;
	uint8_t color = RandomState(situation.numberOfStates);

	while (!remaining.empty())
	{
		coord2D point = remaining.front();
		lattice[point.x][point.y] = color; // X...radek, Y...sloupec
		remaining.pop();
		BFSHorizontalCheck(point.x, point.y, (latticeSize + point.y + 1) % latticeSize); // doprava (opravdu, viz kodovani matice hran)
		BFSHorizontalCheck(point.x, (latticeSize + point.y - 1) % latticeSize); // doleva
		BFSVerticalCheck(point.x, point.y, (latticeSize + point.x + 1) % latticeSize); // dolu
		BFSVerticalCheck((latticeSize + point.x - 1) % latticeSize, point.y); // nahoru
	}
}

void CallBFS()
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

void ResetVariables()
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			visited[i][j] = false;
		}
	}
	while (!remaining.empty())
	{
		remaining.pop();
	}
}

void SwendsenColorStep2D()
{
	ResetVariables();
	CallBFS();
}

void SwendsenStep2D()
{
	SwendsenBondStep2D();
	SwendsenColorStep2D();
}

void SwendsenInitialization()
{
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			horizontal[i][j] = 0;
			vertical[i][j] = 0;
		}
	}
}

void Swendsen::Initialize()
{
	Simulator::Initialize();
	SwendsenInitialization();
}

void Swendsen::OneStep()
{
	SwendsenStep2D();
}

string Swendsen::Name()
{
	return "SWENDSEN-WANG";
}

string Swendsen::Type()
{
	return "SWENDSEN";
}