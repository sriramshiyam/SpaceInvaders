#include "raylib.h"
#include "raymath.h"
#include "utils/globals.h"
#include "utils/random.h"
#include "manager/enemymanager.h"
#include "ui/hud.h"

EnemyManager::EnemyManager()
{
    shootLaserTimer = 1.0f;
    initializeValues();
}

void EnemyManager::Load()
{
    texture1 = LoadTexture("res/sprite/enemy1.png");
    texture2 = LoadTexture("res/sprite/enemy2.png");
    texture3 = LoadTexture("res/sprite/enemy3.png");
    texture4 = LoadTexture("res/sprite/enemy4.png");
    LoadEnemies();
}

void EnemyManager::UnLoad()
{
    UnloadTexture(texture1);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
    UnloadTexture(texture4);
}

void EnemyManager::Update()
{
    if (!finishedSpawing)
    {
        HandleSpawnGen();
    }
    else
    {
        shootLaserTimer -= GetFrameTime();
        if (shootLaserTimer < 0.0f)
        {
            shootLaserTimer = 1.0f;
            ShootLasers();
        }
    }

    if (movingDownTimer > 0.0f)
    {
        movingDownTimer -= GetFrameTime();

        for (int i = 0; i < spawnLength; i++)
        {
            enemies[i].SetPosition(Vector2Add(enemies[i].GetPosition(), (Vector2){0, movingDownSpeed * GetFrameTime()}));
        }

        if (movingDownTimer < 0.1f)
        {
            rotationTimer = 0.2f;
        }
    }

    if (finishedSpawing && rotationTimer > 0.0f)
    {
        rotationTimer -= GetFrameTime();
        rotation += movingSpeed * movingDirection * GetFrameTime();
    }

    if (rotationTimer < 0.0f)
    {
        if (movingDirection == -1 && rotation < 0.0f)
        {
            rotation += movingSpeed * GetFrameTime();
        }
        else if (movingDirection == 1 && rotation > 0.0f)
        {
            rotation -= movingSpeed * GetFrameTime();
        }
        else
        {
            rotation = 0.0f;
        }
    }

    if (movingDownTimer > 0.0f)
    {
        return;
    }

    bool enemyOutOfBounds = false;

    for (int i = 0; i < spawnLength; i++)
    {
        if (enemies[i].GetSpawnMoveTimer() <= 0.15f)
        {
            enemies[i].SetPosition(Vector2Add(enemies[i].GetPosition(), (Vector2){0, 80 * GetFrameTime()}));
            enemies[i].SetSpawnMoveTimer(enemies[i].GetSpawnMoveTimer() + GetFrameTime());
        }

        if (finishedSpawing)
        {
            Vector2 velocity = Vector2Scale(enemies[i].GetVelocity(), GetFrameTime() * movingDirection * movingSpeed);
            enemies[i].SetPosition(Vector2Add(enemies[i].GetPosition(), velocity));

            if (enemies[i].GetPosition().x > 1300.0f || enemies[i].GetPosition().x < 100.0f)
            {
                enemyOutOfBounds = true;
            }
        }
    }

    if (enemyOutOfBounds)
    {
        movingSpeed += 10;
        movingDownSpeed += 5;
        movingDirection *= -1;
        movingDownTimer = 0.4f - 0.01 * movingDownCounter;
        movingDownCounter++;
        rotationTimer = 0.3f;
    }

    MarkLastEnemy();
}

void EnemyManager::Draw()
{
    for (int i = 0; i < spawnLength; i++)
    {
        Rectangle rect = enemies[i].GetRectangle();

        switch (enemies[i].GetRowNumber())
        {
        case 1:
            DrawTexturePro(texture1, {0, 0, (float)texture1.width, (float)texture1.height}, rect, {rect.width / 2, rect.height / 2}, rotation, WHITE);
            break;
        case 2:
            DrawTexturePro(texture2, {0, 0, (float)texture2.width, (float)texture2.height}, rect, {rect.width / 2, rect.height / 2}, rotation, WHITE);
            break;
        case 3:
            DrawTexturePro(texture3, {0, 0, (float)texture2.width, (float)texture2.height}, rect, {rect.width / 2, rect.height / 2}, rotation, WHITE);
            break;
        case 4:
            DrawTexturePro(texture4, {0, 0, (float)texture2.width, (float)texture2.height}, rect, {rect.width / 2, rect.height / 2}, rotation, WHITE);
            break;
        default:
            break;
        }

        if (enemies[i].GetIsLast())
        {
            Rectangle rect = enemies[i].GetRectangle();
            DrawRectangleLines(rect.x - rect.width / 2, rect.y - rect.height / 2, rect.width, rect.height, WHITE);
        }
    }
}

void EnemyManager::LoadEnemies()
{
    Hud *hud = reinterpret_cast<Hud *>(Globals::hud);

    hud->SetWave(hud->GetWave() + 1);
    initializeValues();

    int enemyNumber = 0;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 1; x <= 11; x++)
        {
            Enemy enemy;
            enemy.SetEnemyNumber(enemyNumber);
            enemyNumber++;

            if (y == 0 && x == 1)
            {
                enemy.SetIsSpawned(true);
            }

            switch (y)
            {
            case 0:
                enemy.SetRowNumber(1);
                break;
            case 1:
                enemy.SetRowNumber(2);
                break;
            case 2:
                enemy.SetRowNumber(3);
                break;
            case 3:
                enemy.SetRowNumber(4);
                break;
            case 4:
                enemy.SetRowNumber(2);
                break;
            default:
                break;
            }

            enemy.SetSize((Vector2){texture1.width, texture1.height});
            enemy.SetPosition((Vector2){100 + 100 * x, 100 + 80 * y});
            enemy.SetVelocity((Vector2){movingDirection, 0});
            enemies.push_back(enemy);
        }
    }
}

std::vector<Enemy> *EnemyManager::GetEnemies()
{
    return &enemies;
}

void EnemyManager::SetSpawnLength(int spawnLength)
{
    this->spawnLength = spawnLength;
    if (this->spawnLength == 0)
    {
        LoadEnemies();
        finishedSpawing = false;
    }
}

int EnemyManager::GetSpawnLength()
{
    return spawnLength;
}

void EnemyManager::initializeValues()
{
    spawnTimer = 0.0f;
    spawnLength = 0;
    finishedSpawing = false;
    movingDirection = 1;
    movingSpeed = 50;
    movingDownTimer = 0.0f;
    movingDownSpeed = 70;
    movingDownCounter = 0;
    rotation = 0.0f;
    rotationTimer = 0.0f;
}
void EnemyManager::HandleSpawnGen()
{
    spawnTimer += GetFrameTime();
    if (spawnTimer >= 0.06f)
    {
        enemies[spawnLength].SetIsSpawned(true);
        spawnLength++;
        spawnTimer = 0.0f;
        if (spawnLength == enemies.size())
        {
            finishedSpawing = true;
        }
    }
}

void EnemyManager::MarkLastEnemy()
{
    float temp = movingDirection == 1 ? 0 : MAXFLOAT;

    Enemy *lastEnemy;

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].SetIsLast(false);

        if (movingDirection == 1)
        {
            if (enemies[i].GetPosition().x > temp)
            {
                temp = enemies[i].GetPosition().x;
                lastEnemy = &enemies[i];
            }
        }
        else
        {
            if (enemies[i].GetPosition().x < temp)
            {
                temp = enemies[i].GetPosition().x;
                lastEnemy = &enemies[i];
            }
        }
    }

    lastEnemy->SetIsLast(true);
}

void EnemyManager::ShootLasers()
{
    Hud *hud = reinterpret_cast<Hud *>(Globals::hud);

    Random random;
    int laserCount = random.GetRandomInt(1, 2 + hud->GetWave());
    std::vector<int> enemyNumbers;

    for (int i = 0; i < laserCount; i++)
    {
        enemyNumbers.push_back(random.GetRandomInt(0, 55 - 1));
    }

    Globals::laserManager->AddEnemyLaser(enemyNumbers);
}
