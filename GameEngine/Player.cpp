#include "Player.h"
#include "Constants.h"
#include "Engine.h"
#include "Animation/PlayerAnimation/PlayerAnimator.h"

void Player::Setup()
{
    Engine* engine = Engine::GetInstance();
    PlayerSprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);

    //Animator setup
    animator = PlayerAnimator{PlayerSprite, "Idle", this};
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

    //Update sprite location
    PlayerSprite->position = GetPlayerPosition();

    //Animation
    animator.UpdateSprite();
}