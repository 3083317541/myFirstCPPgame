#pragma once
#include <random>

// Float in [min, max)
float getRandomFloat(std::ranlux24_base& rng, float min, float max);

// Int in [min, max]
int getRandomInt(std::ranlux24_base& rng, int min, int max);

bool getRandomChance(std::ranlux24_base& rng, float chance);