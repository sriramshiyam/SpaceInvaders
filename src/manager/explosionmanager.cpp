#include "manager/explosionmanager.h"
#include "utils/random.h"
#include <math.h>

void ExplosionManager::Load()
{
    smokeTexture = LoadTexture("res/sprite/smoke.png");
}

void ExplosionManager::UnLoad()
{
    UnloadTexture(smokeTexture);
}

#include "utils/globals.h"

void ExplosionManager::Update()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        explosions[i].SetAlpha(explosions[i].GetAlpha() - GetFrameTime() * 0.6);
        explosions[i].SetGravity(explosions[i].GetGravity() + 5.0f);
        explosions[i].SetSparkSize(explosions[i].GetSparkSize() - 4.0f * GetFrameTime());

        for (int j = 0; j < 5; j++)
        {
            float *angles = explosions[i].GetSmokeAngles();
            Vector2 *position = &explosions[i].GetSmokePositions()[j];
            position->x += 25.0f * cos(angles[j] * (M_PI / 180.0f)) * GetFrameTime();
            position->y += 25.0f * sin(angles[j] * (M_PI / 180.0f)) * GetFrameTime();
        }

        for (int j = 0; j < 20; j++)
        {
            float *angles = explosions[i].GetSparkAngles();
            Vector2 *position = &explosions[i].GetSparkPositions()[j];
            position->x += 25.0f * cos(angles[j] * (M_PI / 180.0f)) * GetFrameTime();
            position->y += 25.0f * sin(angles[j] * (M_PI / 180.0f)) * GetFrameTime();
            position->y += explosions[i].GetGravity() * GetFrameTime();
        }
    }

    for (std::vector<Explosion>::iterator it = explosions.begin(); it != explosions.end();)
    {
        if ((*it).GetAlpha() < 0.0f)
        {
            it = explosions.erase(it);
        }
        else
        {
            it++;
        }
    }
}
void ExplosionManager::Draw()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Vector2 position = explosions[i].GetSmokePositions()[j];
            DrawTexturePro(smokeTexture,
                           (Rectangle){0, 0, smokeTexture.width, smokeTexture.height},
                           (Rectangle){position.x, position.y, smokeTexture.width * 0.2, smokeTexture.height * 0.2},
                           (Vector2){smokeTexture.width * 0.2 / 2, smokeTexture.height * 0.2 / 2},
                           0.0f,
                           ColorAlpha(WHITE, explosions[i].GetAlpha()));
        }

        for (int j = 0; j < 20; j++)
        {
            float size = explosions[i].GetSparkSize();
            Vector2 position = explosions[i].GetSparkPositions()[j];
            DrawRectanglePro((Rectangle){position.x, position.y, size, size},
                             (Vector2){size / 2, size / 2}, 0.0f,
                             ORANGE);
        }
    }
}

void ExplosionManager::AddExplosion(Vector2 position)
{
    explosions.push_back(Explosion(position));
}
