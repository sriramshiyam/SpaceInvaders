#pragma once
#include "raylib.h"
#include "component.h"
#include "player.h"
#include "lasermanager.h"

class Game : public Component
{
private:
    RenderTexture2D canvas;
    RenderTexture2D gameCanvas;
    int previousWindowWidth;
    int previousWindowHeight;
    Rectangle canvasDest;
    void ResizeCanvas(int screenWidth, int screenHeight);

    LaserManager laserManager;
    Player player;

public:
    Game();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
};