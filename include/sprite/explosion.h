#pragma once

#include <raylib.h>

class Explosion
{
private:
    float smokesAngles[5];
    Vector2 smokePositions[5];
    float sparkAngles[20];
    Vector2 sparkPositions[20];
    float alpha;
    Vector2 position;
    float gravity;
    float sparkSize;

public:
    Explosion(Vector2 position);
    void LoadSmokes();
    void LoadSparks();
    float *GetSmokeAngles();
    Vector2 *GetSmokePositions();
    float *GetSparkAngles();
    Vector2 *GetSparkPositions();
    float GetAlpha();
    void SetAlpha(float alpha);
    float GetGravity();
    void SetGravity(float gravity);
    float GetSparkSize();
    void SetSparkSize(float sparkSize);
};