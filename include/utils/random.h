#pragma once

#include <random>

class Random
{
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    Random();
    float GetRandomFloat(float min, float max);
    int GetRandomInt(int min, int max);
};