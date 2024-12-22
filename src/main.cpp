#include "raylib.h"
#include "globals.h"
#include "game.h"

int Globals::canvasWidth = 0;
int Globals::canvasHeight = 0;
int Globals::gameWidth = 0;
int Globals::gameHeight = 0;
LaserManager *Globals::laserManager = nullptr;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Space Invaders");
    MaximizeWindow();
    HideCursor();
    SetTargetFPS(60);

    Game game;
    game.Load();

    while (!WindowShouldClose())
    {
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        game.Draw();

        EndDrawing();
    }

    game.UnLoad();
    CloseWindow();

    return 0;
}
