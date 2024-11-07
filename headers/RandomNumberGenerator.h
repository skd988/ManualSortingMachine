#pragma once

#include <stdlib.h>
#include <time.h>

class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	RandomNumberGenerator(unsigned int seed);
	unsigned int getSeed() const;
	void setSeed(unsigned int seed);
	void newSeed();
	int rnd(int min, int max) const;

private:
	unsigned int m_seed;
};