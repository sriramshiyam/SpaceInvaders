#pragma once

#include "raylib.h"
#include "utils/component.h"

class Menu : public Component
{
private:
    Font font;

public:
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};