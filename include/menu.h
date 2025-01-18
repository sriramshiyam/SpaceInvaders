#pragma once

#include "raylib.h"
#include "utils/component.h"

class Menu : public Component
{
public:
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};