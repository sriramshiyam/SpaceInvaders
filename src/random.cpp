#include "random.h"
#include <random>

float Random::GetRandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distrib(min, max);

    return distrib(gen);
}

int Random::GetRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}
