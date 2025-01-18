#pragma once

#include <vector>
#include "raylib.h"
#include "utils/component.h"
#include "sprite/combo.h"

class ComboManager : public Component
{
private:
    std::vector<Combo> combos;
    int comboNumber;
    float comboTimer;

public:
    ComboManager();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void AddCombo(Vector2 enemyPosition);
    void DrawComboTextures();
};