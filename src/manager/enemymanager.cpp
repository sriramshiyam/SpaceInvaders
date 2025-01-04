#include "raylib.h"
#include "raymath.h"
#include "utils/globals.h"
#include "manager/enemymanager.h"

EnemyManager::EnemyManager()
{
    initializeValues();
}

void EnemyManager::Load()
{
    texture = LoadTexture("res/sprite/enemy1.png");
    LoadEnemies();
}

void EnemyManager::UnLoad()
{
    UnloadTexture(texture);
}

void EnemyManager::Update()
{
    if (!finishedSpawing)
    {
        HandleSpawnGen();
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
        DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, rect, {rect.width / 2, rect.height / 2}, rotation, WHITE);
        if (enemies[i].GetIsLast())
        {
            Rectangle rect = enemies[i].GetRectangle();
            DrawRectangleLines(rect.x - rect.width / 2, rect.y - rect.height / 2, rect.width, rect.height, WHITE);
        }
    }
}

void EnemyManager::LoadEnemies()
{
    initializeValues();

    for (int y = 0; y < 5; y++)
    {
        for (int x = 1; x <= 11; x++)
        {
            Enemy enemy;
            if (y == 0 && x == 1)
            {
                enemy.SetIsSpawned(true);
            }
            enemy.SetSize((Vector2){texture.width, texture.height});
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
