#include "iostream"
#include "ui/splashscreen.h"
#include "utils/globals.h"

SplashScreen::SplashScreen()
{
    alpha = 2.0f;
}

void SplashScreen::Load()
{
}

void SplashScreen::UnLoad()
{
}

void SplashScreen::Update()
{
    alpha -= 0.5f * GetFrameTime();
    if (alpha < -0.2f)
    {
        Globals::state = State::MENU;
        Globals::soundManager->PlayMenuMusic();
    }
}

void SplashScreen::Draw()
{
    Vector2 boundRect = MeasureTextEx(Globals::font, "MADE\nWITH", 40.0f, 3.0f);
    DrawTextPro(Globals::font, "MADE\nWITH", {(float)Globals::canvasWidth / 2, (float)Globals::canvasHeight / 2}, {boundRect.x, boundRect.y / 2}, 0.0f, 40.0f, 3.0f, ColorAlpha(WHITE, alpha));

    DrawRectangleV({(float)Globals::canvasWidth / 2 + 30, (float)Globals::canvasHeight / 2 - 75}, (Vector2){140, 10}, ColorAlpha(WHITE, alpha));
    DrawRectangleV({(float)Globals::canvasWidth / 2 + 20, (float)Globals::canvasHeight / 2 - 75}, (Vector2){10, 150}, ColorAlpha(WHITE, alpha));
    DrawRectangleV({(float)Globals::canvasWidth / 2 + 30, (float)Globals::canvasHeight / 2 + 65}, (Vector2){130, 10}, ColorAlpha(WHITE, alpha));
    DrawRectangleV({(float)Globals::canvasWidth / 2 + 160, (float)Globals::canvasHeight / 2 - 65}, (Vector2){10, 140}, ColorAlpha(WHITE, alpha));

    int textWidth = MeasureText("raylib", 30.0f);
    DrawText("raylib", Globals::canvasWidth / 2 + 150 - textWidth, Globals::canvasHeight / 2 + 65 - 40.0f, 30.0f, ColorAlpha(WHITE, alpha));
}
