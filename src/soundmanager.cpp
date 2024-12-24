#include "soundmanager.h"
#include "raylib.h"

void SoundManager::Load()
{
    playerLaser = LoadSound("res/player_laser.wav");
}

void SoundManager::UnLoad()
{
    UnloadSound(playerLaser);
}

void SoundManager::PlayPlayerLaser()
{
    PlaySound(playerLaser);
}
