#include "sprite/combo.h"
#include "combo.h"

Combo::Combo()
{
    rotateSpring.k = 0.1f;
    rotateSpring.damping = 0.6f;
    rotateSpring.restLength = -22.0f;
    rotation = -22.0f;
}

void Combo::HandleRotateSpring()
{
    float x = rotation - rotateSpring.restLength;
    rotateSpring.force = -rotateSpring.k * x;

    rotateSpring.velocity += rotateSpring.force;
    rotation += rotateSpring.velocity;

    rotateSpring.velocity *= rotateSpring.damping;
}

void Combo::SetComboNumber(int comboNumber)
{
    this->comboNumber = comboNumber;
}

int Combo::GetComboNumber()
{
    return comboNumber;
}

void Combo::SetRotation(float rotation)
{
    this->rotation = rotation;
}

float Combo::GetRotation()
{
    return rotation;
}

void Combo::SetPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Combo::GetPosition()
{
    return position;
}
