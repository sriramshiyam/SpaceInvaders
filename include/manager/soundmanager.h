#pragma once

#include "raylib.h"
#include "utils/component.h"

class SoundManager
{
private:
    Sound playerLaser;
    Music menuMusic;
    Music gameMusic;
    Sound enemyDestroyed;
    Sound combo;

public:
    void Load();
    void UnLoad();
    void PlayPlayerLaser();
    void PlayMenuMusic();
    void StopMenuMusic();
    void PlayGameMusic();
    void StopGameMusic();
    void UpdateCurrentMusicStream();
    void PlayEnemyDestroyed();
    void PlayCombo();
};