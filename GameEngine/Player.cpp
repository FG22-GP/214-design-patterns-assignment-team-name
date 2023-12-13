#include "Player.h"
#include "Constants.h"
#include "Engine.h"
#include "Animation/PlayerFallLeftAnimation.h"
#include "Animation/PlayerFallRightAnimation.h"
#include "Animation/PlayerIdleAnimation.h"
#include "Animation/PlayerJumpLeftAnimation.h"
#include "Animation/PlayerJumpRightAnimation.h"
#include "Animation/PlayerRunLeftAnimation.h"
#include "Animation/PlayerRunRightAnimation.h"

void Player::Setup()
{
    Engine* engine = Engine::GetInstance();
    PlayerSprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);

    //Animator setup
    animator = Animator{PlayerSprite};
    animator.Animations["Idle"] = PlayerIdleAnimation{};
    animator.Animations["RunLeft"] = PlayerRunLeftAnimation{};
    animator.Animations["RunRight"] = PlayerRunRightAnimation{};
    animator.Animations["JumpLeft"] = PlayerJumpLeftAnimation{};
    animator.Animations["JumpRight"] = PlayerJumpRightAnimation{};
    animator.Animations["FallLeft"] = PlayerFallLeftAnimation{};
    animator.Animations["FallRight"] = PlayerFallRightAnimation{};
    animator.CurrentAnimation = "Idle";
}

void Player::SetMovementDirection(Vector2 dir)
{
    MovementDirection = dir;
}

Vector2 Player::GetMovementDirection()
{
    return MovementDirection;
}

Vector2 Player::GetPlayerPosition()
{
    return PlayerPosition;
}

void Player::SetPlayerPosition(Vector2 newPosition)
{
    PlayerPosition = newPosition;
}

void Player::SetGrounded(bool grounding)
{
    isGrounded = grounding;
    if(grounding)
    {
        YForce = 0.f;
    }
}

void Player::Jump()
{
    if(isGrounded)
    {
        YForce = -jumpSpeed;
        SetGrounded(false);
    }
}

void Player::PlayerMovement(float input)
{
    SetMovementDirection(Vector2(input*movementSpeed, 0));
    
    if(input != 0.f)
    {
        LastRecordedDirectionPress = input;
    }
}

void Player::Tick(float deltaTime)
{
    //Resolve forces
    if(!isGrounded)
    {
        YForce -= Gravity;
    }else
    {
        YForce = 0.f;
    }

    //Move player
    SetPlayerPosition(GetPlayerPosition() + GetMovementDirection()  * deltaTime + Vector2(0,YForce));

    animator.UpdateSprite();
    
    //Update sprite location
    PlayerSprite->position = GetPlayerPosition();

    //Animation
    UpdateAnimation();
}

void Player::UpdateAnimation()
{
    if(GetMovementDirection().magnitude() > 0.f && isGrounded) //Moving on ground
    {
        animator.CurrentAnimation = GetMovementDirection().x > 0.f ? "RunRight" : "RunLeft";
    }
    else if(GetMovementDirection().magnitude() > 0.f && !isGrounded && YForce < 0) //Moving while rising midair
    {
        animator.CurrentAnimation = GetMovementDirection().x > 0.f ? "JumpRight" : "JumpLeft";
    }
    else if(GetMovementDirection().magnitude() > 0.f && !isGrounded && YForce > 0) //Moving while falling midair
    {
        animator.CurrentAnimation = GetMovementDirection().x > 0.f ? "FallRight" : "FallLeft";
    }
    else if(!isGrounded && YForce < 0) //Rising midair
    {
        animator.CurrentAnimation = LastRecordedDirectionPress > 0 ? "JumpRight" : "JumpLeft";
    }
    else if(!isGrounded && YForce > 0) //Falling midair
    {
        animator.CurrentAnimation = LastRecordedDirectionPress > 0 ? "FallRight" : "FallLeft";
    }
    else //Idle
    {
        animator.CurrentAnimation = "Idle";
    }
    animator.UpdateSprite();
}
