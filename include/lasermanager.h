#pragma once

#include <vector>
#include "raylib.h"
#include "component.h"
#include "player.h"
#include "laser.h"

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