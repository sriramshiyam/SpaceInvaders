#pragma once

#include "utils/component.h"
#include <raylib.h>
#include <vector>
#include "sprite/explosion.h"

class ExplosionManager : public Component
{
private:
    Texture smokeTexture;
    std::vector<Explosion> explosions;

public:
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void AddExplosion(Vector2 position);
};