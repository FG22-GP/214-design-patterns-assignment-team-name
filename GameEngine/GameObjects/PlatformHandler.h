﻿#pragma once
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
    
    static const int PlatformAmount = 7;
    Sprite* platforms[PlatformAmount];
    Vector2 platformLocations[PlatformAmount]
    {
        Vector2{0,600},
        Vector2{300,600},
        Vector2{600,600},
        Vector2{900,600},

        Vector2{0,200},
        Vector2{300,500},
        Vector2{600,400},
    };

    void HandleCollision(Entity& entity);

private:
    Entity* currentEntity; // Store the current entity for the timer callback
    static Uint32 SetGroundedOnEntity(Uint32 interval, void* param);
};