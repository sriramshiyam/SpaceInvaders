#include "raylib.h"
#include "utils/globals.h"
#include "game.h"

int Globals::canvasWidth = 0;
int Globals::canvasHeight = 0;
int Globals::gameWidth = 0;
int Globals::gameHeight = 0;
State Globals::state = State::SPLASH_SCREEN;
LaserManager *Globals::laserManager = nullptr;
SoundManager *Globals::soundManager = nullptr;
EnemyManager *Globals::enemyManager = nullptr;
ComboManager *Globals::comboManager = nullptr;
ExplosionManager *Globals::explosionManager = nullptr;
Player *Globals::player = nullptr;
void *Globals::hud = nullptr;
Font Globals::font = Font();

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Space Invaders");
    InitAudioDevice();
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
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
