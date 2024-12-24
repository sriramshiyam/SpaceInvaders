#pragma once

#include "raylib.h"
#include "component.h"

class SoundManager
{
private:
    Sound playerLaser;

public:
    void Load();
    void UnLoad();
    void PlayPlayerLaser();
};