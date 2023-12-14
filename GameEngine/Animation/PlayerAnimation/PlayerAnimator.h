#pragma once
#include "../Animator.h"

class Player;

class PlayerAnimator : public Animator
{
public:
    PlayerAnimator(Sprite* InSprite = nullptr, std::string DefaultAnimation = "", Player* InPlayer = nullptr);
};
