#pragma once
#include <functional>
#include <map>
#include "Animation.h"

struct AnimationTransition
{
    AnimationTransition(std::string InStateToTransitionTo, std::function<bool()> InTransitionCondition)
    {
        StateToTransitionTo = InStateToTransitionTo;
        TransitionCondition = InTransitionCondition;
    }
    std::string StateToTransitionTo;
    std::function<bool()> TransitionCondition;
};

struct AnimationState
{
    Animation Animation;
    std::list<AnimationTransition> Transitions;
};

class Animator
{
public:
    Animator(Sprite* InSprite, std::string DefaultAnimation);

    Sprite* TargetSprite;

    std::string CurrentState;
    std::map<std::string, AnimationState> AnimationStates;
    std::function<bool()> FlipSpriteCondition;

    void UpdateSprite();
};
