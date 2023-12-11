#pragma once

class GameObject
{
public:
    GameObject();
    virtual ~GameObject() = default;
    
    virtual void Tick(float deltaTime);
};
