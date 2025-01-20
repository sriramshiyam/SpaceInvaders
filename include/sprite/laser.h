#pragma once

#include "raylib.h"

class Laser
{
private:
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool isDestroyed;

public:
    Laser();
    Rectangle GetRectangle();
    void SetPosition(Vector2 position);
    void SetSize(Vector2 size);
    void SetVelocity(Vector2 velocity);
    Vector2 GetPosition();
    Vector2 GetSize();
    Vector2 GetVelocity();
    bool GetIsDestroyed();
    void SetIsDestroyed(bool isDestroyed);
};