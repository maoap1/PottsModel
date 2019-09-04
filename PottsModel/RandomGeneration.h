#pragma once
#include <random>

extern random_device generator;
extern uniform_real_distribution<double> distribution;

unsigned DiscreteUniformNumber(unsigned length);
uint8_t RandomState(uint8_t numberOfStates);

#define rn distribution(generator);