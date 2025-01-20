#pragma once

#include <vector>
#include "raylib.h"
#include "utils/component.h"
#include "sprite/player.h"
#include "sprite/laser.h"
#include "sprite/enemylaser.h"

class LaserManager : public Component
{
private:
    Texture playerLaserTex;
    Texture enemyLaserTex;
    std::vector<Laser> playerLasers;
    std::vector<EnemyLaser> enemyLasers;

public:
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void AddPlayerLaser(Rectangle playerRect);
    void AddEnemyLaser(std::vector<int> &enemyNumbers);
};