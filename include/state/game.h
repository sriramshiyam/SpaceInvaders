#pragma once

#include "raylib.h"
#include "manager/lasermanager.h"
#include "manager/soundmanager.h"
#include "ui/splashscreen.h"
#include "ui/hud.h"
#include "sprite/stars.h"
#include "sprite/player.h"
#include "utils/component.h"
#include "menu.h"

class Game : public Component
{
private:
    RenderTexture2D canvas;
    RenderTexture2D gameCanvas;
    int previousWindowWidth;
    int previousWindowHeight;
    Rectangle canvasDest;
    void ResizeCanvas(int screenWidth, int screenHeight);

    SplashScreen splashScreen;
    Menu menu;

    Hud hud;
    LaserManager laserManager;
    SoundManager soundManager;
    Stars stars;
    Player player;

public:
    Game();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};