#pragma once
#include "Player.h"

inline Uint32 SetGroundedOnPlayer(Uint32 interval, void* name)
{
    Player::getInstance().SetGrounded(true);
    return 0;
}

class PlatformHandler
{
public:
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
    
    void Setup();
    void HandleCollision();
};
