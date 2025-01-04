#include "raylib.h"
#include "sprite/laser.h"

Rectangle Laser::GetRectangle()
{
    return (Rectangle){position.x, position.y, size.x, size.y};
}

Laser::Laser()
{
    isDestroyed = false;
}

void Laser::SetPosition(Vector2 position)
{
    this->position = position;
}

void Laser::SetSize(Vector2 size)
{
    this->size = size;
}

void Laser::SetVelocity(Vector2 velocity)
{
    this->velocity = velocity;
}

Vector2 Laser::GetPosition()
{
    return position;
}

Vector2 Laser::GetSize()
{
    return size;
}

Vector2 Laser::GetVelocity()
{
    return velocity;
}

bool Laser::GetIsDestroyed()
{
    return isDestroyed;
}

void Laser::SetIsDestroyed(bool isDestroyed)
{
    this->isDestroyed = isDestroyed;
}