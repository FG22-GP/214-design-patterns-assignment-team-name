#pragma once
#include "Entity.h"

class EntityManager
{
public:
    Entity* firstEntity = nullptr;
    Entity* lastEntity = nullptr;
    int uniqueIdCounter = 0;

    void AddEntity(Entity* entityToAdd);
    void RemoveEntityWithId(int id);
    Entity* GetEntityWithId(int id);

    void Update(float deltaTime);
    void Draw(float deltaTime);
    
};
