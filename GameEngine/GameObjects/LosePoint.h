#pragma once
#include "../EngineClasses/Sprite.h"

class LosePoint
{
    bool loseBoolean = false;

public:
    Sprite* losePointSprite;

    [[nodiscard]] bool GetLoseBoolean() const
    {
        return loseBoolean;
    }

    void SetLoseBoolean(bool lose_boolean)
    {
        loseBoolean = lose_boolean;
    }
    void Lose();
    void LosePointHandle();
};
