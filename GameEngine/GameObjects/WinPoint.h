#pragma once
#include "../EngineClasses/Sprite.h"

class WinPoint
{
    bool winBoolean = false;

public:
    Sprite* winPointSprite;

    [[nodiscard]] bool GetWinBoolean() const
    {
        return winBoolean;
    }

    void SetWinBoolean(bool win_boolean)
    {
        winBoolean = win_boolean;
    }
    void Win();
    void WinPointHandle();
};
