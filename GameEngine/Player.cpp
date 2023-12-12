#include "Player.h"

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

    //TODO replace this with actual collision with ground
    if(GetPlayerPosition().y > 500.f)
    {
        SetGrounded(true);
    }
}