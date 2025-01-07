#pragma once

#include "raylib.h"

class Enemy
{
private:
    Vector2 velocity;
    Vector2 position;
    Vector2 size;
    float spawnMoveTimer;
    bool isDestroyed;
    bool isSpawned;
    bool isLast;
    int enemyNumber;

public:
    Enemy();
    void SetSize(Vector2 size);
    void SetPosition(Vector2 position);
    void SetVelocity(Vector2 velocity);
    Vector2 GetSize();
    Vector2 GetPosition();
    Vector2 GetVelocity();
    Rectangle GetRectangle();
    float GetSpawnMoveTimer();
    void SetSpawnMoveTimer(float newTimer);
    bool GetIsDestroyed();
    void SetIsDestroyed(bool isDestroyed);
    bool GetIsSpawned();
    void SetIsSpawned(bool isSpawned);
    bool GetIsLast();
    void SetIsLast(bool isLast);
    int GetEnemyNumber();
    void SetEnemyNumber(int enemyNumber);
};