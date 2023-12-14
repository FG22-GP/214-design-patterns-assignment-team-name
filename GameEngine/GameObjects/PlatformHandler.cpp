#include "PlatformHandler.h"
#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Engine.h"
#include "../HelperClasses/HelperFunctions.h"
#include "../EngineClasses/Sprite.h"

PlatformHandler::PlatformHandler()
{
    Engine* engine = Engine::GetInstance();
    for (int i = 0; i < PlatformAmount; i++)
    {
        platforms[i] = engine->GetSprite(Constants::WALLSPRITEFILEPATH, platformLocations[i], Vector2 {300, 100}, false);
    }
}

void PlatformHandler::HandleCollision(Entity& entity)
{
    currentEntity = &entity;
    
    // Collision
    bool grounded = false;
    for (Sprite* platform : platforms)
    {
        if (HelperFunctions::CheckIntersection(currentEntity->sprite->position, currentEntity->sprite->size, platform->position, platform->size))
        {
            Vector2 IntersectionLoc = HelperFunctions::GetIntersectionPointAABB(currentEntity->sprite->position, currentEntity->sprite->size, platform->position, platform->size);

            // Platform is to the left or right of the entity
            float Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - currentEntity->GetMiddle()), HelperFunctions::Normalize(currentEntity->GetMovementDirection()));
            if (Dot > 0.8f)
            {
                currentEntity->SetMovementDirection({0, 0});
            }

            // Platform is below the entity
            Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - currentEntity->GetMiddle()), Vector2{0, 1});
            if (Dot > 0.6f)
            {
                grounded = true;
                SDL_AddTimer(1, SetGroundedOnEntity, currentEntity);
            }

            // Platform is above the entity
            if (Dot < -0.6f)
            {
                currentEntity->yForce = HelperFunctions::Clamp(currentEntity->yForce, 0, INFINITY);
            }
        }
    }

    // Set the entity's grounded value even if collision wasn't detected.
    // Otherwise, the entity would float when walking off platforms
    if (!grounded)
    {
        currentEntity->SetGrounded(false);
    }
}

Uint32 PlatformHandler::SetGroundedOnEntity(Uint32 interval, void* param)
{
    Entity* entity = static_cast<Entity*>(param);
    if (entity)
    {
        entity->SetGrounded(true);
    }
    return 0;
}
