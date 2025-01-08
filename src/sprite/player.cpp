#include "raylib.h"
#include "sprite/player.h"
#include "utils/globals.h"

Player::Player()
{
    speed = 1000.0f;
    jumpSpring.k = 0.1f;
    jumpSpring.damping = 0.6f;
    jumpSpring.velocity = 0.0f;
    shootTimer = 0.0f;
}

void Player::Load()
{
    texture = LoadTexture("res/sprite/player.png");

    sourceTex = {0, 0, (float)texture.width, (float)texture.height};
    position = {(float)Globals::gameWidth / 2, (float)Globals::gameHeight - texture.height * 4 - 20};
    jumpSpring.restLength = Globals::gameHeight - texture.height * 4 - 20;
}

void Player::UnLoad()
{
    UnloadTexture(texture);
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
}

void Player::HandleJumpSpring()
{
    float x = position.y - jumpSpring.restLength;
    jumpSpring.force = -jumpSpring.k * x;

    jumpSpring.velocity += jumpSpring.force;
    position.y += jumpSpring.velocity;

    jumpSpring.velocity *= jumpSpring.damping;
}

void Player::Draw()
{
    Rectangle dest = {position.x, position.y, texture.width * 4, texture.height * 4};
    DrawTexturePro(texture, sourceTex, dest, {(float)texture.width * 4 / 2, (float)texture.height * 4 / 2}, 0, WHITE);
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
