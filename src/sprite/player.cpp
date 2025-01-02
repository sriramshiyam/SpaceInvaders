#include "raylib.h"
#include "sprite/player.h"
#include "utils/globals.h"

Player::Player()
{
    speed = 1000.0f;
    spring.k = 0.1f;
    spring.damping = 0.6f;
}

void Player::Load()
{
    texture = LoadTexture("res/sprite/player.png");

    sourceTex = {0, 0, (float)texture.width, (float)texture.height};
    position = {(float)Globals::gameWidth / 2, (float)Globals::gameHeight - texture.height * 4 - 20};
    spring.restLength = Globals::gameHeight - texture.height * 4 - 20;
}

void Player::UnLoad()
{
    UnloadTexture(texture);
}

void Player::Update()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        stopped = false;
        position.x += speed * GetFrameTime();
        direction = 1;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        stopped = false;
        position.x -= speed * GetFrameTime();
        direction = -1;
    }

    if (IsKeyReleased(KEY_D) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
    {
        stopped = true;
        inertia = speed;
        inertiaDec = 1;
    }

    if (stopped)
    {
        position.x += direction * inertia * GetFrameTime();
        inertiaDec = inertiaDec * 2 + 1;
        inertia -= inertiaDec;

        if (inertia <= 0.0f)
        {
            stopped = false;
        }
    }

    if (position.x < 100.0f)
    {
        position.x = 100.0f;
    }
    else if (position.x >= Globals::gameWidth - 100.0f)
    {
        position.x = Globals::gameWidth - 100.0f;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        Globals::laserManager->AddPlayerLaser(GetRectangle());
        position.y += speed * 1.25f * GetFrameTime();
        Globals::soundManager->PlayPlayerLaser();
    }

    HandleSpring();
}

void Player::HandleSpring()
{
    float x = position.y - spring.restLength;
    spring.force = -spring.k * x;

    spring.velocity += spring.force;
    position.y += spring.velocity;

    spring.velocity *= spring.damping;
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
