#pragma once

class Component
{
public:
    virtual void Load() = 0;
    virtual void UnLoad() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};