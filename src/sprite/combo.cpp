#include "sprite/combo.h"
#include "raymath.h"
#include "utils/globals.h"
#include "utils/random.h"
#include <string>

Combo::Combo(int comboNumber) : comboNumber(comboNumber)
{
    rotateSpring.k = 0.4f;
    rotateSpring.damping = 0.8f;
    rotateSpring.restLength = -20.0f;
    rotateSpring.velocity = 0.0f;
    rotation = -60.0f;
    restTimer = 0.2f;
    scale = 1.0f;
    colorChange = Random().GetRandomFloat(0.0f, 5.0f);
}

void Combo::HandleRotateSpring()
{
    float x = rotation - rotateSpring.restLength;
    rotateSpring.force = -rotateSpring.k * x;

    rotateSpring.velocity += rotateSpring.force;
    rotation += rotateSpring.velocity;

    rotateSpring.velocity *= rotateSpring.damping;

    if (rotation > -20.5f && rotation < -19.5f)
    {
        restTimer -= GetFrameTime();
    }
    else
    {
        restTimer = 0.2f;
    }

    if (restTimer < 0.0f)
    {
        scale -= GetFrameTime();
    }
}

void Combo::Load()
{
    Vector2 size1 = MeasureTextEx(Globals::font, "COMBO", 20.0f, 3.0f);
    size1 = Vector2Add(size1, (Vector2){4, 0});
    comboWordTexture = LoadRenderTexture(size1.x, size1.y);

    Vector2 size2 = comboNumber < 10 ? MeasureTextEx(Globals::font, "X0!", 20.0f, 3.0f) : MeasureTextEx(Globals::font, "X00!!", 20.0f, 3.0f);
    size2 = Vector2Add(size2, (Vector2){4, 0});
    comboNumberTexture = LoadRenderTexture(size2.x, size2.y);

    Vector2 size3 = Vector2Add(Vector2Add(size1, size2), (Vector2){10, 0});
    comboTexture = LoadRenderTexture(size3.x, size3.y);
}

void Combo::UnLoad()
{
    UnloadRenderTexture(comboWordTexture);
    UnloadRenderTexture(comboNumberTexture);
    UnloadRenderTexture(comboTexture);
}

void Combo::SetComboNumber(int comboNumber)
{
    this->comboNumber = comboNumber;
}

int Combo::GetComboNumber()
{
    return comboNumber;
}

void Combo::SetRotation(float rotation)
{
    this->rotation = rotation;
}

float Combo::GetRotation()
{
    return rotation;
}

void Combo::SetPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Combo::GetPosition()
{
    return position;
}

void Combo::RenderComboTexture()
{
    colorChange += GetFrameTime() * 2;
    Color comboBgColor = {sin(colorChange) * 255, -sin(colorChange) * 255, cos(colorChange) * 255, 255};

    BeginTextureMode(comboWordTexture);
    ClearBackground(ColorAlpha(BLACK, 0.0f));
    DrawRectangleRounded((Rectangle){0, 0, comboWordTexture.texture.width, comboWordTexture.texture.height}, 0.5f, 8, comboBgColor);
    DrawTextEx(Globals::font, "COMBO", (Vector2){2, 0}, 20.0f, 3.0f, BLACK);
    EndTextureMode();

    std::string comboNumberText = comboNumber < 10 ? "X!" : "X!!";
    BeginTextureMode(comboNumberTexture);
    ClearBackground(ColorAlpha(BLACK, 0.0f));
    DrawRectangleRounded((Rectangle){0, 0, comboNumberTexture.texture.width, comboNumberTexture.texture.height}, 0.5f, 8, comboBgColor);
    comboNumberText.insert(1, std::to_string(comboNumber));
    DrawTextEx(Globals::font, comboNumberText.c_str(), (Vector2){2, 0}, 20.0f, 3.0f, BLACK);
    EndTextureMode();

    BeginTextureMode(comboTexture);
    ClearBackground(ColorAlpha(BLACK, 0.0f));
    DrawTextureEx(comboWordTexture.texture, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(comboNumberTexture.texture, (Vector2){comboWordTexture.texture.width + 10, 0}, 0.0f, 1.0f, WHITE);
    EndTextureMode();
}

RenderTexture Combo::GetComboTexture()
{
    return comboTexture;
}

float Combo::GetRestTimer()
{
    return restTimer;
}

float Combo::GetScale()
{
    return scale;
}
