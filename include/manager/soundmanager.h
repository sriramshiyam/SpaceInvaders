#pragma once

#include "raylib.h"
#include "utils/component.h"

class SoundManager
{
private:
    Sound playerLaser;
    Music menuMusic;
    Music gameMusic;

public:
    void Load();
    void UnLoad();
    void PlayPlayerLaser();
    void PlayMenuMusic();
    void StopMenuMusic();
    void PlayGameMusic();
    void StopGameMusic();
    void UpdateCurrentMusicStream();
};