#include "ui/hud.h"

Hud::Hud()
{
    spring.k = 0.3f;
    spring.damping = 0.6f;
    spring.restLength = 20.0f;
}

void Hud::Load()
{
    font = LoadFont("res/font/Vipnagorgialla_Bd.otf");

    float y = 0.0f;
    y += 40.0f;
    scoreLabelV = {-300.0f, y};
    Vector2 boundRect = MeasureTextEx(font, "SCORE", 30.0f, 3.0f);
    y += boundRect.y;
    scoreV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "0", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    livesLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "LIVES", 30.0f, 3.0f);
    y += boundRect.y;
    livesV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "3", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    maxComboLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "MAX COMBO", 30.0f, 3.0f);
    y += boundRect.y;
    maxComboV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "0", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    waveLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "WAVE", 30.0f, 3.0f);
    y += boundRect.y;
    waveV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "1", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    killsLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(font, "KILLS", 30.0f, 3.0f);
    y += boundRect.y;
    killsV = {-300.0f, y};
}

void Hud::UnLoad()
{
    UnloadFont(font);
}

void Hud::Update()
{
    scoreLabelV.x += spring.velocity;
    scoreV.x += spring.velocity;
    livesLabelV.x += spring.velocity;
    livesV.x += spring.velocity;
    maxComboLabelV.x += spring.velocity;
    maxComboV.x += spring.velocity;
    waveLabelV.x += spring.velocity;
    waveV.x += spring.velocity;
    killsLabelV.x += spring.velocity;
    killsV.x += spring.velocity;
    HandleSpring();
}

void Hud::Draw()
{
    DrawTextEx(font, "SCORE", scoreLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(font, "0", scoreV, 60.0f, 3.0f, WHITE);
    DrawTextEx(font, "LIVES", livesLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(font, "3", livesV, 60.0f, 3.0f, WHITE);
    DrawTextEx(font, "MAX COMBO", maxComboLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(font, "0", maxComboV, 60.0f, 3.0f, WHITE);
    DrawTextEx(font, "WAVE", waveLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(font, "1", waveV, 60.0f, 3.0f, WHITE);
    DrawTextEx(font, "KILLS", killsLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(font, "0", killsV, 60.0f, 3.0f, WHITE);
}

void Hud::HandleSpring()
{
    float x = scoreLabelV.x - spring.restLength;
    spring.force = -spring.k * x;
    spring.velocity += spring.force;
    spring.velocity *= spring.damping;
}
