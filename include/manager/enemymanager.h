#pragma once

#include <vector>
#include "raylib.h"
#include "utils/component.h"
#include "utils/spring.h"
#include "sprite/enemy.h"

class EnemyManager : public Component
{

private:
    Texture texture1;
    Texture texture2;
    Texture texture3;
    Texture texture4;
    std::vector<Enemy> enemies;
    float spawnTimer;
    int spawnLength;
    bool finishedSpawing;
    int movingDirection;
    int movingSpeed;
    int movingDownSpeed;
    float movingDownTimer;
    int movingDownCounter;
    float rotation;
    float rotationTimer;
    float shootLaserTimer;

    void initializeValues();
    void HandleSpawnGen();
    void MarkLastEnemy();
    void ShootLasers();

public:
    EnemyManager();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void LoadEnemies();
    std::vector<Enemy> *GetEnemies();
    void SetSpawnLength(int spawnLength);
    int GetSpawnLength();
};