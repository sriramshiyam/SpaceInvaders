#include "utils/random.h"

Random::Random()
{
    gen = std::mt19937(rd());
}

float Random::GetRandomFloat(float min, float max)
{
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}

int Random::GetRandomInt(int min, int max)
{
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
