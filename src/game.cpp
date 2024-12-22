#include "game.h"
#include "globals.h"

Game::Game() : Component()
{
    previousWindowWidth = 0;
    previousWindowHeight = 0;

    Globals::canvasWidth = 1920;
    Globals::canvasHeight = 1080;
    Globals::gameWidth = 1400;
    Globals::gameHeight = 1000;
    Globals::laserManager = &laserManager;
}

void Game::Load()
{
    canvas = LoadRenderTexture(Globals::canvasWidth, Globals::canvasHeight);
    gameCanvas = LoadRenderTexture(Globals::gameWidth, Globals::gameHeight);
    player.Load();
    laserManager.Load();
}

void Game::UnLoad()
{
    UnloadRenderTexture(canvas);
    UnloadRenderTexture(gameCanvas);
    player.UnLoad();
    laserManager.UnLoad();
}

void Game::Update()
{
    if (GetScreenWidth() != previousWindowWidth || GetScreenHeight() != previousWindowHeight)
    {
        ResizeCanvas(GetScreenWidth(), GetScreenHeight());
    }

    player.Update();
    laserManager.Update();
}

void Game::Draw()
{
    BeginTextureMode(gameCanvas);
    ClearBackground(BLACK);
    DrawRectangleLinesEx({0, 0, (float)Globals::gameWidth, (float)Globals::gameHeight}, 2, WHITE);
    player.Draw();
    laserManager.Draw();
    EndTextureMode();

    Rectangle gameCanvasSource = {0.0f, 0.0f, (float)gameCanvas.texture.width, -(float)gameCanvas.texture.height};
    Rectangle gameCanvasDest = {(float)canvas.texture.width / 2 - (float)gameCanvas.texture.width / 2, 40.0f, (float)gameCanvas.texture.width, (float)gameCanvas.texture.height};

    BeginTextureMode(canvas);
    ClearBackground((Color){7, 71, 153, 255});
    DrawTexturePro(gameCanvas.texture, gameCanvasSource, gameCanvasDest, (Vector2){0, 0}, 0.0f, WHITE);

    EndTextureMode();

    Rectangle canvasSource = {0.0f, 0.0f, (float)canvas.texture.width, -(float)canvas.texture.height};

    DrawTexturePro(canvas.texture, canvasSource, canvasDest, (Vector2){0, 0}, 0.0f, WHITE);
}

void Game::ResizeCanvas(int screenWidth, int screenHeight)
{
    float targetAspect = (float)Globals::canvasWidth / Globals::canvasHeight;
    float windowAspect = (float)screenWidth / screenHeight;

    if (targetAspect > windowAspect)
    {
        canvasDest.width = screenWidth;
        canvasDest.height = screenWidth / targetAspect;
        canvasDest.x = 0;
        canvasDest.y = (screenHeight - canvasDest.height) / 2;
    }
    else
    {
        canvasDest.width = screenHeight * targetAspect;
        canvasDest.height = screenHeight;
        canvasDest.x = (screenWidth - canvasDest.width) / 2;
        canvasDest.y = 0;
    }
}