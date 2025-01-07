#include "raylib.h"
#include "game.h"
#include "utils/globals.h"

Game::Game() : Component()
{
    previousWindowWidth = 0;
    previousWindowHeight = 0;

    Globals::canvasWidth = 1920;
    Globals::canvasHeight = 1080;
    Globals::gameWidth = 1400;
    Globals::gameHeight = 1000;
    Globals::laserManager = &laserManager;
    Globals::soundManager = &soundManager;
    Globals::enemyManager = &enemyManager;
    Globals::comboManager = &comboManager;
    Globals::player = &player;
    Globals::state = State::MENU;
}

void Game::Load()
{
    canvas = LoadRenderTexture(Globals::canvasWidth, Globals::canvasHeight);
    gameCanvas = LoadRenderTexture(Globals::gameWidth, Globals::gameHeight);

    splashScreen.Load();
    menu.Load();
    hud.Load();
    player.Load();
    laserManager.Load();
    soundManager.Load();
    enemyManager.Load();
    comboManager.Load();
    stars.Load();
}

void Game::UnLoad()
{
    UnloadRenderTexture(canvas);
    UnloadRenderTexture(gameCanvas);

    splashScreen.UnLoad();
    menu.UnLoad();
    hud.UnLoad();
    player.UnLoad();
    laserManager.UnLoad();
    soundManager.UnLoad();
    enemyManager.UnLoad();
    comboManager.UnLoad();
}

void Game::Update()
{
    soundManager.UpdateCurrentMusicStream();
    if (GetScreenWidth() != previousWindowWidth || GetScreenHeight() != previousWindowHeight)
    {
        ResizeCanvas(GetScreenWidth(), GetScreenHeight());
    }

    if (Globals::state == State::SPLASH_SCREEN)
    {
        splashScreen.Update();
    }
    else
    {
        player.Update();
        laserManager.Update();
        stars.Update();

        if (Globals::state == State::MENU)
        {
            menu.Update();
        }
        else if (Globals::state == State::GAME)
        {
            hud.Update();
            enemyManager.Update();
            comboManager.Update();
        }
    }
}

void Game::Draw()
{
    if (Globals::state != State::SPLASH_SCREEN)
    {
        if (Globals::state == State::GAME)
        {
            comboManager.DrawComboTextures();
        }

        BeginTextureMode(gameCanvas);
        ClearBackground(BLACK);
        DrawFPS(5, 5);

        DrawRectangleLinesEx({0, 0, (float)Globals::gameWidth, (float)Globals::gameHeight}, 2, WHITE);
        stars.Draw();
        player.Draw();
        laserManager.Draw();

        if (Globals::state == State::MENU)
        {
            menu.Draw();
        }
        else if (Globals::state == State::GAME)
        {
            enemyManager.Draw();
            comboManager.Draw();
        }

        EndTextureMode();
    }

    BeginTextureMode(canvas);
    if (Globals::state == State::SPLASH_SCREEN)
    {
        ClearBackground((Color){39, 36, 37, 255});
        splashScreen.Draw();
    }
    else
    {
        Rectangle gameCanvasSource = {0.0f, 0.0f, (float)gameCanvas.texture.width, -(float)gameCanvas.texture.height};
        Rectangle gameCanvasDest = {(float)canvas.texture.width / 2 - (float)gameCanvas.texture.width / 2, 40.0f, (float)gameCanvas.texture.width, (float)gameCanvas.texture.height};
        ClearBackground((Color){7, 71, 153, 255});
        DrawTexturePro(gameCanvas.texture, gameCanvasSource, gameCanvasDest, (Vector2){0, 0}, 0.0f, WHITE);
    }

    if (Globals::state == State::GAME)
    {
        hud.Draw();
    }

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