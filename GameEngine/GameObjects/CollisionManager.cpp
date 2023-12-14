#include "CollisionManager.h"

#include "Entity.h"
#include "EntityManager.h"
#include "../HelperClasses/HelperFunctions.h"

void CollisionManager::CollisionUpdate()
{
    Entity* stepEntity = EntityManager::GetInstance().firstEntity;
    Entity* secondStepEntity = nullptr;

    while (stepEntity != nullptr)
    {
        secondStepEntity = stepEntity->nextEntity;
        
        while (secondStepEntity != nullptr)
        {
            if(HelperFunctions::CheckIntersection(stepEntity->sprite->position, stepEntity->sprite->size,
                secondStepEntity->sprite->position, secondStepEntity->sprite->size))
            {
                stepEntity->HasCollidedWith(secondStepEntity);
                secondStepEntity->HasCollidedWith(stepEntity);
            }

            secondStepEntity = secondStepEntity->nextEntity;
        }

        stepEntity = stepEntity->nextEntity;
    }
}
