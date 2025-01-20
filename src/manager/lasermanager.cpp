#include "raylib.h"
#include "raymath.h"
#include "manager/lasermanager.h"
#include "sprite/enemy.h"
#include "utils/globals.h"
#include "ui/hud.h"

void LaserManager::Load()
{
    playerLaserTex = LoadTexture("res/sprite/player_laser.png");
    enemyLaserTex = LoadTexture("res/sprite/enemy_laser.png");
}

void LaserManager::UnLoad()
{
    UnloadTexture(playerLaserTex);
    UnloadTexture(enemyLaserTex);
}

void LaserManager::Update()
{
    for (int i = 0; i < playerLasers.size(); i++)
    {
        Vector2 velocity = Vector2Scale(playerLasers[i].GetVelocity(), GetFrameTime());
        playerLasers[i].SetPosition(Vector2Add(playerLasers[i].GetPosition(), velocity));
    }

    for (int i = 0; i < enemyLasers.size(); i++)
    {
        Vector2 velocity = Vector2Scale(enemyLasers[i].GetVelocity(), GetFrameTime());
        enemyLasers[i].SetPosition(Vector2Add(enemyLasers[i].GetPosition(), velocity));
    }

    std::vector<Enemy> *enemies = Globals::enemyManager->GetEnemies();

    for (int i = enemies->size() - 1; i >= 0; i--)
    {
        if (!enemies->at(i).GetIsSpawned())
        {
            continue;
        }

        Rectangle enemyRect = enemies->at(i).GetRectangle();
        enemyRect.x -= enemyRect.width / 2;
        enemyRect.y -= enemyRect.height / 2;

        for (int j = 0; j < playerLasers.size(); j++)
        {
            Rectangle laserRect = playerLasers[j].GetRectangle();
            laserRect.x -= laserRect.width / 2;
            laserRect.y -= laserRect.height / 2;

            if (CheckCollisionRecs(enemyRect, laserRect))
            {
                playerLasers[j].SetIsDestroyed(true);
                enemies->at(i).SetIsDestroyed(true);
                Globals::enemyManager->SetSpawnLength(Globals::enemyManager->GetSpawnLength() - 1);
            }
        }
    }

    Rectangle playerRect = Globals::player->GetRectangle();
    playerRect.x -= playerRect.width / 2;
    playerRect.y -= playerRect.height / 2;

    for (int i = 0; i < enemyLasers.size(); i++)
    {
        Rectangle laserRect = enemyLasers[i].GetRectangle();
        laserRect.x -= laserRect.width / 2;
        laserRect.y -= laserRect.height / 2;

        if (CheckCollisionRecs(playerRect, laserRect))
        {
            enemyLasers[i].SetIsDestroyed(true);
            Hud *hud = reinterpret_cast<Hud *>(Globals::hud);
            hud->SetLives(hud->GetLives() - 1);
            Globals::player->SetIsAttacked(true);
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

    for (std::vector<EnemyLaser>::iterator it = enemyLasers.begin(); it != enemyLasers.end();)
    {
        if ((*it).GetIsDestroyed() || (*it).GetPosition().y > Globals::gameHeight)
        {
            it = enemyLasers.erase(it);
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
            Hud *hud = reinterpret_cast<Hud *>(Globals::hud);
            hud->SetKills(hud->GetKills() + 1);
            Globals::comboManager->AddCombo((*it).GetPosition());
            Globals::explosionManager->AddExplosion((*it).GetPosition());
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

    for (int i = 0; i < enemyLasers.size(); i++)
    {
        Rectangle rect = enemyLasers[i].GetRectangle();
        DrawTexturePro(enemyLaserTex, {0, 0, (float)enemyLaserTex.width, (float)enemyLaserTex.height}, rect, {rect.width / 2, rect.height / 2}, 0.0f, WHITE);
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

void LaserManager::AddEnemyLaser(std::vector<int> &enemyNumbers)
{
    std::vector<Enemy> *enemies = Globals::enemyManager->GetEnemies();

    for (int i = 0; i < enemies->size(); i++)
    {
        for (int j = 0; j < enemyNumbers.size(); j++)
        {
            if (enemies->at(i).GetEnemyNumber() == enemyNumbers[j])
            {
                EnemyLaser laser;
                Vector2 size = {enemyLaserTex.width, enemyLaserTex.height};
                Rectangle rect = enemies->at(i).GetRectangle();
                Vector2 position = {rect.x, rect.y};

                laser.SetSize(size);
                laser.SetPosition(position);
                laser.SetVelocity({0.0, 400.0f});

                enemyLasers.push_back(laser);
            }
        }
    }
}
