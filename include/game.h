#pragma once
#include "raylib.h"
#include "splashscreen.h"
#include "component.h"
#include "player.h"
#include "lasermanager.h"
#include "soundmanager.h"
#include "stars.h"
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