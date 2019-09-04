#include "Simulator.h"
#include "Initialization.h"

void Simulator::Initialize()
{
	FillWithRandomNumbers();
}

string Simulator::Type()
{
	return "unspecified";
}