#include "../../Player.h"
#include "PlayerAnimator.h"
#include "PlayerFallAnimation.h"
#include "PlayerIdleAnimation.h"
#include "PlayerJumpAnimation.h"
#include "PlayerRunAnimation.h"

PlayerAnimator::PlayerAnimator(Sprite* InSprite, std::string DefaultAnimation, Player* InPlayer) : Animator(InSprite, DefaultAnimation)
{
    FlipSpriteCondition = [InPlayer]{return InPlayer->LastRecordedDirectionPress < 0.f;};
    
     std::list<AnimationTransition> TransitionList =
     {
         AnimationTransition{ "Jump", [InPlayer]{return !InPlayer->GetGrounded();} },
         AnimationTransition{ "Run", [InPlayer]{return InPlayer->GetMovementDirection().magnitude() > 0.f;} },
     };
     AnimationStates["Idle"] = AnimationState{ PlayerIdleAnimation{}, TransitionList };
     
     TransitionList =
     {
         AnimationTransition{ "Fall", [InPlayer]{return !InPlayer->GetGrounded() && InPlayer->YForce > 0.f;} },
         AnimationTransition{ "Jump", [InPlayer]{return !InPlayer->GetGrounded() && InPlayer->YForce < 0.f;} },AnimationTransition{ "Idle", [InPlayer]{return InPlayer->GetMovementDirection().magnitude() == 0.f;} },
     };
     AnimationStates["Run"] = AnimationState{ PlayerRunAnimation{}, TransitionList };
     
     TransitionList =
     {
         AnimationTransition{ "Fall", [InPlayer]{return !InPlayer->GetGrounded() && InPlayer->YForce > 0.f;} },
         AnimationTransition{ "Run", [InPlayer]{return InPlayer->GetGrounded();} },
     };
     AnimationStates["Jump"] = AnimationState{ PlayerJumpAnimation{}, TransitionList };
     
     TransitionList =
      {
         AnimationTransition{ "Run", [InPlayer]{return InPlayer->GetGrounded() && InPlayer->GetMovementDirection().magnitude() > 0.f;} },
         AnimationTransition{ "Idle", [InPlayer]{return InPlayer->GetGrounded();} },
     };
     AnimationStates["Fall"] = AnimationState{ PlayerFallAnimation{}, TransitionList };
}
