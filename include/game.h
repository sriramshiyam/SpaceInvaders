#pragma once

#include "raylib.h"
#include "ui/splashscreen.h"
#include "utils/component.h"
#include "sprite/player.h"
#include "manager/lasermanager.h"
#include "manager/soundmanager.h"
#include "manager/enemymanager.h"
#include "manager/combomanager.h"
#include "sprite/stars.h"
#include "ui/hud.h"
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
    EnemyManager enemyManager;
    ComboManager comboManager;
    Stars stars;
    Player player;

public:
    Game();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};