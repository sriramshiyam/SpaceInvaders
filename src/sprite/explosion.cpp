#include "sprite/explosion.h"
#include "utils/random.h"
#include <math.h>

Explosion::Explosion(Vector2 position)
{
    this->position = position;
    alpha = 0.6f;
    gravity = 0.0f;
    sparkSize = 3.5f;
    LoadSmokes();
    LoadSparks();
}

void Explosion::LoadSmokes()
{
    Random random;
    float angle = 0.0f;

    for (int i = 0; i < 5; i++)
    {
        Vector2 smokePosition;
        smokePosition.x = position.x + 20.0f * cos(angle * (M_PI / 180.0f));
        smokePosition.y = position.y + 20.0f * sin(angle * (M_PI / 180.0f));

        smokePositions[i] = smokePosition;
        smokesAngles[i] = angle;

        angle += random.GetRandomFloat(45.0f, 90.0f);
    }
}

void Explosion::LoadSparks()
{
    Random random;

    for (int i = 0; i < 20; i++)
    {
        Vector2 sparkPosition;

        float angle = random.GetRandomFloat(0.0f, 360.0f);

        sparkPosition.x = position.x + random.GetRandomInt(10, 70) * cos(angle * (M_PI / 180.0f));
        sparkPosition.y = position.y + random.GetRandomInt(10, 70) * sin(angle * (M_PI / 180.0f));

        sparkPositions[i] = sparkPosition;
        sparkAngles[i] = angle;
    }
}

float *Explosion::GetSmokeAngles()
{
    return smokesAngles;
}

Vector2 *Explosion::GetSmokePositions()
{
    return smokePositions;
}

float *Explosion::GetSparkAngles()
{
    return sparkAngles;
}

Vector2 *Explosion::GetSparkPositions()
{
    return sparkPositions;
}

float Explosion::GetAlpha()
{
    return alpha;
}
void Explosion::SetAlpha(float alpha)
{
    this->alpha = alpha;
}
float Explosion::GetGravity()
{
    return gravity;
}

void Explosion::SetGravity(float gravity)
{
    this->gravity = gravity;
}

float Explosion::GetSparkSize()
{
    return sparkSize;
}

void Explosion::SetSparkSize(float sparkSize)
{
    this->sparkSize = sparkSize;
}
