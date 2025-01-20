#pragma once

#include "raylib.h"
#include "utils/spring.h"
#include "utils/component.h"

class Player : public Component
{
private:
    Shader attackedShader;
    Texture texture;
    Rectangle sourceTex;
    Vector2 position;
    Spring jumpSpring;
    float speed;
    int direction;
    float shootTimer;
    bool isAttacked;
    void HandleJumpSpring();
    void HandleAttackedState();

    float attackedColorCount;
    float attackedRadianValue;
    bool canIncreaseAttackedColorCount;

public:
    Player();
    void Load() override;
    void UnLoad() override;
    void Update() override;
    void Draw() override;
    int MovingDirection();
    Rectangle GetRectangle();
    void SetIsAttacked(bool isAttacked);
};