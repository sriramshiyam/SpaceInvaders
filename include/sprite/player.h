#pragma once

#include "raylib.h"
#include "utils/spring.h"
#include "utils/component.h"

class Player : public Component
{
private:
    Texture texture;
    Rectangle sourceTex;
    Vector2 position;

    Spring spring;

    float speed;

    float inertia;
    int inertiaDec;
    int direction;
    bool stopped;

    void HandleSpring();

public:
    Player();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    int MovingDirection();
    Rectangle GetRectangle();
};