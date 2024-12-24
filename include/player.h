#pragma once
#include "component.h"
#include "raylib.h"

typedef struct Spring
{
    int restLength;
    float damping;
    float velocity;
    float force;
    float k;
} Spring;

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