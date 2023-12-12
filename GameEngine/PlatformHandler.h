#pragma once
#include "Player.h"
#include "WinPoint.h"

inline Uint32 SetGroundedOnPlayer(Uint32 interval, void* name)
{
    Player::getInstance().SetGrounded(true);
    return 0;
}

class PlatformHandler
{
public:
    PlatformHandler();
    WinPoint* winPoint;
    Vector2 winPointLocation{1050, 600};
    
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

    void HandleCollision();
};
