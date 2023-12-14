#include "EntityManager.h"

void EntityManager::AddEntity(Entity* entityToAdd)
{
    uniqueIdCounter++;
    entityToAdd->uniqueId = uniqueIdCounter;

    if (firstEntity != nullptr)
    {
        lastEntity->nextEntity = entityToAdd;
    }
    else
    {
        firstEntity = entityToAdd;
    }

    lastEntity = entityToAdd;
}

void EntityManager::RemoveEntityWithId(int id)
{
    Entity* stepEntity = firstEntity;
    if (firstEntity->uniqueId == id)
    {
        firstEntity = firstEntity->nextEntity;
        
    }
    else
    {
        while (stepEntity->nextEntity != nullptr && stepEntity->nextEntity->uniqueId != id)
        {
            stepEntity = stepEntity->nextEntity;
        }

        if (stepEntity->nextEntity != nullptr && stepEntity->nextEntity->uniqueId == id)
        {
            stepEntity->nextEntity = stepEntity->nextEntity->nextEntity;
            
            if (stepEntity->nextEntity == nullptr)
            {
                lastEntity = stepEntity;
            }
            
        }
    }
}


Entity* EntityManager::GetEntityWithId(int id)
{
    Entity* stepEntity = firstEntity;
    while (stepEntity != nullptr)
    {
        if (stepEntity->uniqueId == id) return stepEntity;

        stepEntity = stepEntity->nextEntity;
    }
    return nullptr;
    
}


void EntityManager::Update(float deltaTime)
{
    Entity* stepEntity = firstEntity;
    while (stepEntity != nullptr)
    {
        stepEntity->Tick(deltaTime);
        stepEntity = stepEntity->nextEntity;
    }
}

void EntityManager::Draw(float deltaTime)
{
    
}


