#pragma once

#include "raylib.h"
#include "utils/globals.h"
#include "utils/component.h"
#include "utils/spring.h"

class Hud : public Component
{
private:
    Font font;
    Vector2 scoreLabelV;
    Vector2 scoreV;
    Vector2 livesLabelV;
    Vector2 livesV;
    Vector2 maxComboLabelV;
    Vector2 maxComboV;
    Vector2 waveLabelV;
    Vector2 waveV;
    Vector2 killsLabelV;
    Vector2 killsV;
    Spring spring;
    void HandleSpring();

public:
    Hud();
    void Load();
    void UnLoad();
    void Update();
    void Draw();
};