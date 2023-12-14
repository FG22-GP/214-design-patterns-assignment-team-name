#pragma once
#include "Entity.h"

class EntityManager
{
#pragma region "Singleton logic"
    EntityManager() {}
public:
    static EntityManager& GetInstance() { static EntityManager instance; return instance; }
    EntityManager(EntityManager const&) = delete;
    void operator=(EntityManager const&) = delete;
#pragma endregion
    
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
