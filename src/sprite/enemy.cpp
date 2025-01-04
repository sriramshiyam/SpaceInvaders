#include "sprite/enemy.h"

Enemy::Enemy()
{
    spawnMoveTimer = 0.0f;
    isDestroyed = false;
    isSpawned = false;
    isLast = false;
}

void Enemy::SetSize(Vector2 size)
{
    this->size = size;
}

void Enemy::SetPosition(Vector2 position)
{
    this->position = position;
}

void Enemy::SetVelocity(Vector2 velocity)
{
    this->velocity = velocity;
}

Vector2 Enemy::GetSize()
{
    return size;
}

Vector2 Enemy::GetPosition()
{
    return position;
}

Vector2 Enemy::GetVelocity()
{
    return velocity;
}

Rectangle Enemy::GetRectangle()
{
    return (Rectangle){position.x, position.y, size.x * 6, size.y * 6};
}
float Enemy::GetSpawnMoveTimer()
{
    return spawnMoveTimer;
}

void Enemy::SetSpawnMoveTimer(float newTimer)
{
    spawnMoveTimer = newTimer;
}

bool Enemy::GetIsDestroyed()
{
    return isDestroyed;
}

void Enemy::SetIsDestroyed(bool isDestroyed)
{
    this->isDestroyed = isDestroyed;
}

bool Enemy::GetIsSpawned()
{
    return isSpawned;
}

void Enemy::SetIsSpawned(bool isSpawned)
{
    this->isSpawned = isSpawned;
}

bool Enemy::GetIsLast()
{
    return isLast;
}

void Enemy::SetIsLast(bool isLast)
{
    this->isLast = isLast;
}
