#pragma once

#define _2D
//#define _3D

#pragma region DimensionCheck

#ifdef _2D
#undef _3D
#endif // _2D

#ifdef _3D
#undef _2D
#endif // _3D
#pragma endregion


#include "Simulator.h"
#include "Statistics.h"

constexpr unsigned latticeSize = 420; //420
extern Simulator* algorithm;
extern Simulator* burnInAlgorithm;
extern Statistics* statistics;

extern uint8_t lattice[latticeSize][latticeSize];
extern uint8_t lattice3[latticeSize][latticeSize][latticeSize];
