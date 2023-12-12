#pragma once
#include <map>

#include "Animation.h"

class Animator
{
public:
    Animator(Sprite* InSprite = nullptr);

    Sprite* MySprite;

    std::string CurrentAnimation;
    std::map<std::string, Animation> Animations;

    void UpdateSprite();
};
