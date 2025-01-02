#pragma once

#include <vector>
#include "raylib.h"
#include "utils/component.h"
#include "sprite/player.h"
#include "sprite/laser.h"

class LaserManager : public Component
{
private:
    Texture playerLaserTex;
    std::vector<Laser> playerLasers;
    // std::vector<> enemyLasers;
public:
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void AddPlayerLaser(Rectangle playerRect);
};