#include "Header.h"
#include "Input.h"
#include "Simulation.h"

uint8_t lattice[latticeSize][latticeSize]; // prvni je cislo radku, druhe je cislo sloupce
uint8_t lattice3[latticeSize][latticeSize][latticeSize];

int main()
{
	InitializeByConsoleFast();
	DoSimulation();
}

// Zkontrolovat pres vyhledevani vsech odkazu, ze lattice se pouziva u vsech 2D, zatimco lattice3 se pouziva u vsech 3D!!!
// Statistics.cpp jeste bude treba rozhazet do vice souboru (casem)
// Statistics sice funguje skoro dobre i pro 8N, ale teoreticky by tam mohly byt defekty. Na druhou stranu, skoro se to nestane
