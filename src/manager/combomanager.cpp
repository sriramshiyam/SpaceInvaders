#include "manager/combomanager.h"
#include "raymath.h"
#include "utils/globals.h"
#include <string>

ComboManager::ComboManager()
{
    comboNumber = 0;
    comboTimer = 0.0f;
}

void ComboManager::Load()
{
    font = LoadFont("res/font/Vipnagorgialla_Bd.otf");
}

void ComboManager::UnLoad()
{
    for (int i = 0; i < combos.size(); i++)
    {
        combos[i].UnLoad();
    }

    UnloadFont(font);
}

void ComboManager::Update()
{
    for (int i = 0; i < combos.size(); i++)
    {
        combos[i].HandleRotateSpring();
    }

    comboTimer += GetFrameTime();

    if (comboTimer > 0.5f)
    {
        comboNumber = 0;
    }
}

void ComboManager::Draw()
{
    for (int i = 0; i < combos.size(); i++)
    {
        Vector2 position = combos[i].GetPosition();
        Texture texture = combos[i].GetComboTexture().texture;
        float rotation = combos[i].GetRotation();
        DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){position.x, position.y, texture.width, texture.height}, (Vector2){texture.width / 2, texture.height / 2}, rotation, WHITE);
    }
}

void ComboManager::AddCombo(Vector2 enemyPosition)
{
    comboNumber++;

    if (comboTimer < 0.5f)
    {
        Combo combo(comboNumber);
        combo.SetFont(font);
        combo.Load();
        combo.SetPosition(enemyPosition);
        combos.push_back(combo);
    }

    comboTimer = 0.0f;
}

void ComboManager::DrawComboTextures()
{
    for (int i = 0; i < combos.size(); i++)
    {
        combos[i].RenderComboTexture();
    }
}
