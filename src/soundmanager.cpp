#include "soundmanager.h"
#include "raylib.h"
#include "globals.h"

void SoundManager::Load()
{
    playerLaser = LoadSound("res/player_laser.wav");
    menuMusic = LoadMusicStream("res/menu.xm");
    menuMusic.looping = true;
    gameMusic = LoadMusicStream("res/music.xm");
    gameMusic.looping = true;
}

void SoundManager::UnLoad()
{
    UnloadSound(playerLaser);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
}

void SoundManager::PlayPlayerLaser()
{
    PlaySound(playerLaser);
}

void SoundManager::PlayMenuMusic()
{
    PlayMusicStream(menuMusic);
}

void SoundManager::StopMenuMusic()
{
    StopMusicStream(menuMusic);
}

void SoundManager::PlayGameMusic()
{
    PlayMusicStream(gameMusic);
}

void SoundManager::StopGameMusic()
{
    StopMusicStream(gameMusic);
}

void SoundManager::UpdateCurrentMusicStream()
{
    if (Globals::state == State::MENU)
    {
        UpdateMusicStream(menuMusic);
    }
    else if (Globals::state == State::GAME)
    {
        UpdateMusicStream(gameMusic);
    }
}
