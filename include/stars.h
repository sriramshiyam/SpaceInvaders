#pragma once

#include "raylib.h"
#include <vector>

typedef struct Star
{
    Rectangle rect;
    Color color;
} Star;

class Stars
{
private:
    std::vector<Star> stars;
    float prevPlayerPos;
    float moveSpeed;

public:
    Stars();
    void Load();
    void Update();
    void Draw();
};