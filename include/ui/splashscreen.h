#pragma once

#include <string>
#include "raylib.h"
#include "utils/component.h"

class SplashScreen : public Component
{

private:
    float alpha;

public:
    SplashScreen();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};