#include "raylib.h"
#include "manager/soundmanager.h"
#include "utils/globals.h"

void SoundManager::Load()
{
    playerLaser = LoadSound("res/audio/player_laser.wav");
    SetSoundVolume(playerLaser, 0.5f);
    menuMusic = LoadMusicStream("res/audio/menu.mp3");
    menuMusic.looping = true;
    gameMusic = LoadMusicStream("res/audio/game.mp3");
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
