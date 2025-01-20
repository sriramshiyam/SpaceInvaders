#include "raylib.h"
#include "sprite/player.h"
#include "utils/globals.h"
#include <math.h>

Player::Player()
{
    speed = 1000.0f;
    jumpSpring.k = 0.1f;
    jumpSpring.damping = 0.6f;
    jumpSpring.velocity = 0.0f;
    shootTimer = 0.0f;
    isAttacked = false;
    attackedColorCount = 0;
    attackedRadianValue = 0.0f;
    canIncreaseAttackedColorCount = true;
}

void Player::Load()
{
    texture = LoadTexture("res/sprite/player.png");
    sourceTex = {0, 0, (float)texture.width, (float)texture.height};
    position = {(float)Globals::gameWidth / 2, (float)Globals::gameHeight - texture.height * 4 - 20};
    jumpSpring.restLength = Globals::gameHeight - texture.height * 4 - 20;
    attackedShader = LoadShader(0, "res/shader/attackedshader.fx");
}

void Player::UnLoad()
{
    UnloadTexture(texture);
    UnloadShader(attackedShader);
}

void Player::Update()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        position.x += speed * GetFrameTime();
        direction = 1;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        position.x -= speed * GetFrameTime();
        direction = -1;
    }

    if (position.x < 100.0f)
    {
        position.x = 100.0f;
    }
    else if (position.x >= Globals::gameWidth - 100.0f)
    {
        position.x = Globals::gameWidth - 100.0f;
    }

    shootTimer -= GetFrameTime();

    if (IsKeyDown(KEY_SPACE) && shootTimer <= 0.0f)
    {
        shootTimer = 0.16f;
        Globals::laserManager->AddPlayerLaser(GetRectangle());
        position.y += speed * 1.25f * GetFrameTime();
        Globals::soundManager->PlayPlayerLaser();
    }

    HandleJumpSpring();

    if (isAttacked)
    {
        HandleAttackedState();
    }
}

void Player::HandleJumpSpring()
{
    float x = position.y - jumpSpring.restLength;
    jumpSpring.force = -jumpSpring.k * x;

    jumpSpring.velocity += jumpSpring.force;
    position.y += jumpSpring.velocity;

    jumpSpring.velocity *= jumpSpring.damping;
}

void Player::HandleAttackedState()
{
    attackedRadianValue -= GetFrameTime() * 10.0f;
    float value = abs(sin(attackedRadianValue));
    SetShaderValue(attackedShader, GetShaderLocation(attackedShader, "red"), &value, SHADER_UNIFORM_FLOAT);

    if ((value > 0.99f || value < 0.1f) && canIncreaseAttackedColorCount)
    {
        canIncreaseAttackedColorCount = false;
        attackedColorCount++;
    }
    else
    {
        canIncreaseAttackedColorCount = true;
    }

    if (attackedColorCount == 6)
    {
        isAttacked = false;
    }
}

void Player::Draw()
{
    Rectangle dest = {position.x, position.y, texture.width * 4, texture.height * 4};

    if (isAttacked)
    {
        BeginShaderMode(attackedShader);
    }

    DrawTexturePro(texture, sourceTex, dest, {(float)texture.width * 4 / 2, (float)texture.height * 4 / 2}, 0, WHITE);

    if (isAttacked)
    {
        EndShaderMode();
    }

    // DrawRectangleLines(position.x - texture.width * 4 / 2, position.y - texture.height * 4 / 2, texture.width * 4, texture.height * 4, WHITE);
}

int Player::MovingDirection()
{
    return direction;
}

Rectangle Player::GetRectangle()
{
    return (Rectangle){position.x, position.y, texture.width * 4, texture.height * 4};
}

void Player::SetIsAttacked(bool isAttacked)
{
    this->isAttacked = isAttacked;
    attackedColorCount = 0;
    attackedRadianValue = 0.0f;
    canIncreaseAttackedColorCount = true;
}
