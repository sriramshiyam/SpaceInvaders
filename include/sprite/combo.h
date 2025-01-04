#pragma once

#include "raylib.h"
#include "utils/spring.h"

class Combo
{
private:
    int comboNumber;
    float rotation;
    Spring rotateSpring;
    Vector2 position;

public:
    Combo();
    void HandleRotateSpring();
    void SetComboNumber(int comboNumber);
    int GetComboNumber();
    void SetRotation(float rotation);
    float GetRotation();
    void SetPosition(Vector2 position);
    Vector2 GetPosition();
};