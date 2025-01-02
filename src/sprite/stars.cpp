#include "raylib.h"
#include "sprite/stars.h"
#include "utils/globals.h"
#include "utils/random.h"

Stars::Stars()
{
    moveSpeed = 100.0f;
}

void Stars::Load()
{
    std::vector<std::vector<Vector2>> ranges = {{{-500.0f, 0}, {(float)Globals::gameWidth / 2, (float)Globals::gameHeight / 2}},
                                                {{(float)Globals::gameWidth / 2, 0}, {(float)Globals::gameWidth + 500.0f, (float)Globals::gameHeight / 2}},
                                                {{-500.0f, (float)Globals::gameHeight / 2}, {(float)Globals::gameWidth / 2, (float)Globals::gameHeight}},
                                                {{(float)Globals::gameWidth / 2, (float)Globals::gameHeight / 2}, {(float)Globals::gameWidth + 500.0f, (float)Globals::gameHeight}}};

    Random random;

    for (int i = 0; i < ranges.size(); i++)
    {
        for (int j = 0; j < 20; j++)
        {
            float x = random.GetRandomFloat(ranges[i][0].x, ranges[i][1].x);
            float y = random.GetRandomFloat(ranges[i][0].y, ranges[i][1].y);

            float width = random.GetRandomFloat(4.0f, 6.0f);
            float height = random.GetRandomFloat(3.0f, 6.0f);

            Star star;
            star.rect = {x, y, width, height};
            star.color = ColorAlpha(WHITE, random.GetRandomFloat(0.7f, 1.0f));
            stars.push_back(star);
        }
    }
}

void Stars::Update()
{
    float currentPlayerPos = Globals::player->GetRectangle().x;

    if (currentPlayerPos != prevPlayerPos)
    {
        moveSpeed -= 50.0f * GetFrameTime();
        prevPlayerPos = currentPlayerPos;

        for (int i = 0; i < stars.size(); i++)
        {
            stars[i].rect.x += -1 * Globals::player->MovingDirection() * moveSpeed * GetFrameTime();
        }
    }
    else
    {
        moveSpeed = 100.0f;
    }
}

void Stars::Draw()
{
    for (int i = 0; i < stars.size(); i++)
    {
        DrawRectanglePro(stars[i].rect, {stars[i].rect.width / 2, stars[i].rect.height / 2}, 0.0f, stars[i].color);
    }
}
