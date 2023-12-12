#include "Player.h"
#include "Constants.h"
#include "Engine.h"
#include "Animation/PlayerIdleAnimation.h"
#include "Animation/PlayerRunLeftAnimation.h"
#include "Animation/PlayerRunRightAnimation.h"

void Player::Setup()
{
    Engine* engine = Engine::GetInstance();
    PlayerSprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);
    
    animator = Animator{PlayerSprite};
    
    animator.Animations["Idle"] = PlayerIdleAnimation{};
    animator.Animations["RunRight"] = PlayerRunRightAnimation{};
    animator.Animations["RunLeft"] = PlayerRunLeftAnimation{};
    
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
    if(GetMovementDirection().x > 0.f)
    {
        animator.CurrentAnimation = "RunRight";
    }else if(GetMovementDirection().x < 0.f)
    {
        animator.CurrentAnimation = "RunLeft";
    }else
    {
        animator.CurrentAnimation = "Idle";
    }
    animator.UpdateSprite();
}