#include "menu.h"
#include "utils/globals.h"

void Menu::Load()
{
}

void Menu::UnLoad()
{
}

void Menu::Update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        Globals::state = State::GAME;
        Globals::soundManager->StopMenuMusic();
        Globals::soundManager->PlayGameMusic();
    }
}

void Menu::Draw()
{
    Vector2 boundRect = MeasureTextEx(Globals::font, "INVASION FROM SPACE", 100.0f, 3.0f);
    Vector2 position = {Globals::gameWidth / 2, 100.0f};
    Vector2 origin = {boundRect.x / 2, 0};

    DrawTextPro(Globals::font, "INVASION FROM SPACE", position, origin, 0.0f, 100.0f, 3.0f, WHITE);

    boundRect = MeasureTextEx(Globals::font, "PRESS <ENTER> TO START", 40.0f, 3.0f);
    position = {(float)Globals::gameWidth / 2, (float)Globals::gameHeight / 2};
    origin = {boundRect.x / 2, boundRect.y / 2};

    DrawTextPro(Globals::font, "PRESS <ENTER> TO START", position, origin, 0.0f, 40.0f, 3.0f, WHITE);
}
