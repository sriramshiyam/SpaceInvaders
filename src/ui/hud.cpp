#include "ui/hud.h"

Hud::Hud()
{
    spring.k = 0.3f;
    spring.damping = 0.6f;
    spring.restLength = 20.0f;
    spring.velocity = 0.0f;
    score = 0;
    lives = 3;
    maxCombo = 0;
    wave = 0;
    kills = 0;
}

void Hud::Load()
{
    float y = 0.0f;
    y += 40.0f;
    scoreLabelV = {-300.0f, y};
    Vector2 boundRect = MeasureTextEx(Globals::font, "SCORE", 30.0f, 3.0f);
    y += boundRect.y;
    scoreV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "0", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    livesLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "LIVES", 30.0f, 3.0f);
    y += boundRect.y;
    livesV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "3", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    maxComboLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "MAX COMBO", 30.0f, 3.0f);
    y += boundRect.y;
    maxComboV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "0", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    waveLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "WAVE", 30.0f, 3.0f);
    y += boundRect.y;
    waveV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "1", 60.0f, 3.0f);
    y += boundRect.y + 20.0f;
    killsLabelV = {-300.0f, y};
    boundRect = MeasureTextEx(Globals::font, "KILLS", 30.0f, 3.0f);
    y += boundRect.y;
    killsV = {-300.0f, y};
}

void Hud::UnLoad()
{
}

void Hud::Update()
{
    HandleSpring();
}

void Hud::Draw()
{
    DrawTextEx(Globals::font, "SCORE", scoreLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, std::to_string(score).c_str(), scoreV, 60.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, "LIVES", livesLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, std::to_string(lives).c_str(), livesV, 60.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, "MAX COMBO", maxComboLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, std::to_string(maxCombo).c_str(), maxComboV, 60.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, "WAVE", waveLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, std::to_string(wave).c_str(), waveV, 60.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, "KILLS", killsLabelV, 30.0f, 3.0f, WHITE);
    DrawTextEx(Globals::font, std::to_string(kills).c_str(), killsV, 60.0f, 3.0f, WHITE);
}

void Hud::HandleSpring()
{
    float x = scoreLabelV.x - spring.restLength;
    spring.force = -spring.k * x;
    spring.velocity += spring.force;
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
    spring.velocity *= spring.damping;
}

void Hud::SetScore(int score)
{
    this->score = score;
}

int Hud::GetScore()
{
    return score;
}

void Hud::SetLives(int lives)
{
    this->lives = lives;
}

int Hud::GetLives()
{
    return lives;
}

void Hud::SetMaxCombo(int maxCombo)
{
    this->maxCombo = maxCombo;
}

int Hud::GetMaxCombo()
{
    return maxCombo;
}

void Hud::SetWave(int wave)
{
    this->wave = wave;
}

int Hud::GetWave()
{
    return wave;
}

void Hud::SetKills(int kills)
{
    this->kills = kills;
}

int Hud::GetKills()
{
    return kills;
}
