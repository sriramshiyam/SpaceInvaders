#pragma once

#include "raylib.h"
#include "utils/globals.h"
#include "utils/component.h"
#include "utils/spring.h"

class Hud : public Component
{
private:
    Font font;
    Vector2 scoreLabelV;
    Vector2 scoreV;
    Vector2 livesLabelV;
    Vector2 livesV;
    Vector2 maxComboLabelV;
    Vector2 maxComboV;
    Vector2 waveLabelV;
    Vector2 waveV;
    Vector2 killsLabelV;
    Vector2 killsV;
    Spring spring;
    int score;
    int lives;
    int maxCombo;
    int wave;
    int kills;
    void HandleSpring();

public:
    Hud();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    void SetScore(int score);
    int GetScore();
    void SetLives(int lives);
    int GetLives();
    void SetMaxCombo(int maxCombo);
    int GetMaxCombo();
    void SetWave(int wave);
    int GetWave();
    void SetKills(int kills);
    int GetKills();
};