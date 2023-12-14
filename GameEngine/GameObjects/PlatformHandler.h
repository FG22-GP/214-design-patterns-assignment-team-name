#pragma once
#include "Entity.h"
#include "Player.h"

inline Uint32 SetGroundedOnPlayer(Uint32 interval, void* name)
{
    Player::getInstance().SetGrounded(true);
    return 0;
}

class PlatformHandler
{
public:
    PlatformHandler();
    
    static const int PlatformAmount = 20;
    Sprite* platforms[PlatformAmount];
    Vector2 platformLocations[PlatformAmount]
    {
        Vector2{0,600},
        Vector2{300,600},
        Vector2{600,600},
        Vector2{900,600},
        Vector2{1700,600},
        Vector2{2000,600},
        Vector2{2300,600},
        Vector2{2600,600},
        Vector2{2900,600},
        Vector2{3200,600},

        Vector2{3500,500},
        Vector2{3800,400},
        Vector2{4100,300},

        Vector2{4700,300},
        Vector2{5000,400},
        Vector2{5300,500},
        
        Vector2{5600,600},
        
        Vector2{2300,500},
        Vector2{2600,300},
        Vector2{2900,300},
    };

    void HandleCollision(Entity& entity);

private:
    Entity* currentEntity; // Store the current entity for the timer callback
    static Uint32 SetGroundedOnEntity(Uint32 interval, void* param);
};
