#pragma once
#include <string>

#include "Vector2.h"

class WinPoint
{
    Vector2 WinPointSize{100, 600};
    std::string WinPointSprite;
public:
    std::string GetVictoryPointSprite() { return WinPointSprite; }
    Vector2 GetWinPoint() { return WinPointSize; }
    
    void Win();;
};
