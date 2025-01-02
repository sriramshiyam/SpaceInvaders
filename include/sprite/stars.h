#pragma once

#include <vector>
#include "raylib.h"

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