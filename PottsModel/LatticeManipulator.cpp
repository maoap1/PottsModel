#include "LatticeManipulator.h"
#include "Header.h"

int LatticeManipulator::IncreaseIndex(int index)
{
	return (latticeSize + index + 1) % latticeSize;
}

int LatticeManipulator::DecreaseIndex(int index)
{
	return (latticeSize + index - 1) % latticeSize;

}