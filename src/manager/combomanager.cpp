#include "manager/combomanager.h"
#include "raymath.h"
#include "utils/globals.h"
#include "ui/hud.h"
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

    for (std::vector<Combo>::iterator it = combos.begin(); it != combos.end();)
    {
        if ((*it).GetScale() < 0.0f)
        {
            (*it).UnLoad();
            it = combos.erase(it);
        }
        else
        {
            it++;
        }
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
        float scale = combos[i].GetScale();
        DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){position.x, position.y, texture.width * scale, texture.height * scale}, (Vector2){texture.width * scale / 2, texture.height * scale / 2}, rotation, WHITE);
    }
}

void ComboManager::AddCombo(Vector2 enemyPosition)
{
    comboNumber++;

    Hud *hud = reinterpret_cast<Hud *>(Globals::hud);
    hud->SetScore(hud->GetScore() + comboNumber);

    if (hud->GetMaxCombo() < comboNumber)
    {
        hud->SetMaxCombo(comboNumber);
    }

    if (comboTimer < 0.5f)
    {
        Globals::soundManager->PlayCombo();
        Combo combo(comboNumber);
        combo.SetFont(font);
        combo.Load();
        combo.SetPosition(enemyPosition);
        combos.push_back(combo);
    }
    Globals::soundManager->PlayEnemyDestroyed();

    comboTimer = 0.0f;
}

void ComboManager::DrawComboTextures()
{
    for (int i = 0; i < combos.size(); i++)
    {
        combos[i].RenderComboTexture();
    }
}
