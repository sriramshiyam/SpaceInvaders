#include "manager/combomanager.h"

ComboManager::ComboManager()
{
    comboNumber = 0;
    comboTimer = 0.0f;
}

void ComboManager::Load()
{
}

void ComboManager::UnLoad()
{
}

void ComboManager::Update()
{
    comboTimer += GetFrameTime();

    if (comboTimer > 0.5f)
    {
        comboNumber = 0;
    }
}

void ComboManager::Draw()
{
}

void ComboManager::AddCombo(Vector2 enemyPosition)
{
    comboNumber++;

    if (comboTimer < 0.5f)
    {
        Combo combo;
        combo.SetComboNumber(comboNumber);

        combos.push_back(combo);
    }

    comboTimer = 0.0f;
}
