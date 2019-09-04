using namespace std;

#include <vector>

#include "Header.h"
#include "Situation.h"
#include "Gibbs3D.h"
#include "RandomGeneration.h"

Gibbs3D::Gibbs3D(unsigned neighbors)
{
	numberOfSites = latticeSize * latticeSize * latticeSize;

	if ((neighbors == 6) || (neighbors == 18) || (neighbors == 26))
	{
		numberOfNeighbors = neighbors;
	}
	else
	{
		throw invalid_argument("In Gibbs3D only 6, 18 or 26 neighbors are allowed");
	}
}

void Gibbs3D::OneIteration()
{
	int i = DiscreteUniformNumber(latticeSize);
	int j = DiscreteUniformNumber(latticeSize);
	int k = DiscreteUniformNumber(latticeSize);

	vector<double> probabilities(situation.numberOfStates, 0); // initializes the whole vector to zeros

	probabilities[lattice3[DecreaseIndex(i)][j][k]]++; // top
	probabilities[lattice3[IncreaseIndex(i)][j][k]]++; // bottom
	probabilities[lattice3[i][DecreaseIndex(j)][k]]++; // left
	probabilities[lattice3[i][IncreaseIndex(j)][k]]++; // right
	probabilities[lattice3[i][j][DecreaseIndex(k)]]++; // back
	probabilities[lattice3[i][j][IncreaseIndex(k)]]++; // front


	if ((numberOfNeighbors == 18)||(numberOfNeighbors == 26))
	{
		probabilities[lattice3[DecreaseIndex(i)][DecreaseIndex(j)][k]]++; // top-left
		probabilities[lattice3[DecreaseIndex(i)][IncreaseIndex(j)][k]]++; // top-right
		probabilities[lattice3[DecreaseIndex(i)][j][DecreaseIndex(k)]]++; // top-back
		probabilities[lattice3[DecreaseIndex(i)][j][IncreaseIndex(k)]]++; // top-front

		probabilities[lattice3[IncreaseIndex(i)][DecreaseIndex(j)][k]]++; // down-left
		probabilities[lattice3[IncreaseIndex(i)][IncreaseIndex(j)][k]]++; // down-right
		probabilities[lattice3[IncreaseIndex(i)][j][DecreaseIndex(k)]]++; // down-back
		probabilities[lattice3[IncreaseIndex(i)][j][IncreaseIndex(k)]]++; // down-front

		probabilities[lattice3[i][DecreaseIndex(j)][DecreaseIndex(k)]]++; // left - back
		probabilities[lattice3[i][DecreaseIndex(j)][IncreaseIndex(k)]]++; // left - front
		probabilities[lattice3[i][IncreaseIndex(j)][DecreaseIndex(k)]]++; // right - back
		probabilities[lattice3[i][IncreaseIndex(j)][IncreaseIndex(k)]]++; // right - front
	}

	if (numberOfNeighbors == 26)
	{
		probabilities[lattice3[DecreaseIndex(i)][DecreaseIndex(j)][DecreaseIndex(k)]]++; // top - left - back
		probabilities[lattice3[DecreaseIndex(i)][DecreaseIndex(j)][IncreaseIndex(k)]]++; // top - left - front
		probabilities[lattice3[DecreaseIndex(i)][IncreaseIndex(j)][DecreaseIndex(k)]]++; // top - right - back
		probabilities[lattice3[DecreaseIndex(i)][IncreaseIndex(j)][IncreaseIndex(k)]]++; // top - right - front

		probabilities[lattice3[IncreaseIndex(i)][DecreaseIndex(j)][DecreaseIndex(k)]]++; // down - left - back
		probabilities[lattice3[IncreaseIndex(i)][DecreaseIndex(j)][IncreaseIndex(k)]]++; // down - left - front
		probabilities[lattice3[IncreaseIndex(i)][IncreaseIndex(j)][DecreaseIndex(k)]]++; // down - right - back
		probabilities[lattice3[IncreaseIndex(i)][IncreaseIndex(j)][IncreaseIndex(k)]]++; // down - right - front
	}

	lattice3[i][j][k] = NewState(probabilities);
}

string Gibbs3D::Name()
{
	if (numberOfNeighbors == 6)
	{
		return "GIBBS3D6N";
	}
	else if (numberOfNeighbors == 18)
	{
		return "GIBBS3D18N";
	}
	else
	{
		return "GIBBS3D26N";
	}
}