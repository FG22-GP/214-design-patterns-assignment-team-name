#include "Animator.h"
#include "../EngineClasses/Sprite.h"

class Player;

Animator::Animator(Sprite* InSprite, std::string DefaultAnimation)
{
    TargetSprite = InSprite;
    CurrentState = DefaultAnimation;
}

void Animator::UpdateSprite()
{
    //Transition state if a transition was triggered
    for (auto Transition : AnimationStates[CurrentState].Transitions)
    {
        if(Transition.TransitionCondition())
        {
            CurrentState = Transition.StateToTransitionTo;
            break;
        }
    }

    //Update flip
    TargetSprite->flip = FlipSpriteCondition();

    //Update texture
    TargetSprite->texture = AnimationStates[CurrentState].Animation.GetTexture();
}
