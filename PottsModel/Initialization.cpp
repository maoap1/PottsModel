using namespace std;

#include "Header.h"
#include "RandomGeneration.h"
#include "Situation.h"


void Fill2D(int i, int j)
{
	lattice[i][j] = RandomState(situation.numberOfStates);
}

void Fill3D(int i, int j)
{
	for (int k = 0; k < latticeSize; k++)
	{
		lattice3[i][j][k] = RandomState(situation.numberOfStates);
	}
}

void FillWithRandomNumbers()
{
	for (int i = 0; i < latticeSize; i++) // i je cislo radku
	{
		for (int j = 0; j < latticeSize; j++) // j je cislo sloupce
		{
#ifdef _2D
			Fill2D(i, j);
#endif // _2D
#ifdef _3D
			Fill3D(i, j);
#endif // _3D
		}
	}
}
