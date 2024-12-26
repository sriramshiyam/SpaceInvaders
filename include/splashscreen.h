#pragma once

#include "raylib.h"
#include "component.h"
#include <string>

class SplashScreen : public Component
{

private:
    Font font;
    float alpha;

public:
    SplashScreen();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};