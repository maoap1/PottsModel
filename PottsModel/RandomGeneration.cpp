#include <random>

using namespace std;

random_device generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

#define rn distribution(generator);

/// returns random uniformly distributed number from {0,1,...,length-1}
unsigned DiscreteUniformNumber(unsigned length)
{
	double random = rn;
	return (unsigned)floor(random * length);
}

uint8_t RandomState(uint8_t numberOfStates)
{
	double random = rn;
	return (uint8_t)floor(random * numberOfStates); // zaokrouhli dolu, dle definice uniform_real_distribution
													// nikdy nenabyde hodnoty 1.0, takze vse v poradku
}
