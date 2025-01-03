#include "raylib.h"
#include "raymath.h"
#include "manager/lasermanager.h"

void LaserManager::Load()
{
    playerLaserTex = LoadTexture("res/sprite/player_laser.png");
}

void LaserManager::UnLoad()
{
    UnloadTexture(playerLaserTex);
}

void LaserManager::Update()
{
    for (int i = 0; i < playerLasers.size(); i++)
    {
        Vector2 velocity = Vector2Scale(playerLasers[i].GetVelocity(), GetFrameTime());
        playerLasers[i].SetPosition(Vector2Add(playerLasers[i].GetPosition(), velocity));
    }

    for (int i = playerLasers.size() - 1; i >= 0; i--)
    {
        if (playerLasers[i].GetPosition().y <= -100.0f)
        {
            playerLasers.erase(playerLasers.begin() + i);
        }
    }
}

void LaserManager::Draw()
{
    for (int i = 0; i < playerLasers.size(); i++)
    {
        Rectangle rect = playerLasers[i].GetRectangle();
        DrawTexturePro(playerLaserTex, {0, 0, (float)playerLaserTex.width, (float)playerLaserTex.height}, rect, {rect.width / 2, rect.height / 2}, 0.0f, WHITE);
    }
}

void LaserManager::AddPlayerLaser(Rectangle playerRect)
{
    Laser laser;
    Vector2 size = {playerLaserTex.width, playerLaserTex.height};
    Vector2 position = {playerRect.x, playerRect.y - playerRect.height / 2 - playerLaserTex.height / 2};

    laser.SetSize(size);
    laser.SetPosition(position);
    laser.SetVelocity({0.0, -1250.0f});

    playerLasers.push_back(laser);
}
