#include "raylib.h"
#include "raymath.h"
#include "manager/lasermanager.h"
#include "sprite/enemy.h"
#include "utils/globals.h"

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

    std::vector<Enemy> *enemies = Globals::enemyManager->GetEnemies();

    for (int i = enemies->size() - 1; i >= 0; i--)
    {
        if (!enemies->at(i).GetIsSpawned())
        {
            continue;
        }

        Rectangle rect1 = enemies->at(i).GetRectangle();
        rect1.x -= rect1.width / 2;
        rect1.y -= rect1.height / 2;

        for (int j = 0; j < playerLasers.size(); j++)
        {
            Rectangle rect2 = playerLasers[j].GetRectangle();
            rect2.x -= rect2.width / 2;
            rect2.y -= rect2.height / 2;

            if (CheckCollisionRecs(rect1, rect2))
            {
                playerLasers[j].SetIsDestroyed(true);
                enemies->at(i).SetIsDestroyed(true);
                Globals::enemyManager->SetSpawnLength(Globals::enemyManager->GetSpawnLength() - 1);
            }
        }
    }

    for (std::vector<Laser>::iterator it = playerLasers.begin(); it != playerLasers.end();)
    {
        if ((*it).GetIsDestroyed() || (*it).GetPosition().y <= -100.0f)
        {
            it = playerLasers.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (std::vector<Enemy>::iterator it = enemies->begin(); it != enemies->end();)
    {
        if ((*it).GetIsDestroyed())
        {
            it = enemies->erase(it);
        }
        else
        {
            it++;
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
