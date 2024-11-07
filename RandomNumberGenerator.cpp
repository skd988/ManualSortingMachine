#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{
	newSeed();
}

RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
{
	setSeed(seed);
}

unsigned int RandomNumberGenerator::getSeed() const
{
	return m_seed;
}

void RandomNumberGenerator::setSeed(unsigned int seed)
{
	srand(m_seed = seed);
}

void RandomNumberGenerator::newSeed()
{
	setSeed(time(NULL));
}

int RandomNumberGenerator::rnd(int min, int max) const
{
	if (max >= min)
		return rand() % (max - min + 1) + min;
	else
		return 0;
}
