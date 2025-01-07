#pragma once

#include "raylib.h"
#include "utils/spring.h"

class Combo
{
private:
    int comboNumber;
    double rotation;
    Spring rotateSpring;
    Vector2 position;
    RenderTexture comboWordTexture;
    RenderTexture comboNumberTexture;
    RenderTexture comboTexture;
    Font font;

public:
    Combo(int comboNumber);
    void Load();
    void UnLoad();
    void HandleRotateSpring();
    void SetComboNumber(int comboNumber);
    int GetComboNumber();
    void SetRotation(float rotation);
    float GetRotation();
    void SetPosition(Vector2 position);
    Vector2 GetPosition();
    void SetFont(Font font);
    void RenderComboTexture();
    RenderTexture GetComboTexture();
};