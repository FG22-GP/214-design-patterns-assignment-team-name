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

void Player::SetPlayerPosition(Vector2 movement)
{
    PlayerPosition += movement;
}

void Player::SetGrounded(bool grounding)
{
    isGrounded = grounding;
}

void Player::Jump()
{
    if(isGrounded)
    {
        MovementDirection.y = jumpSpeed;
        SetGrounded(false);
    }
}

void Player::PlayerMovement(float input)
{
    SetMovementDirection(Vector2(input*movementSpeed, 0));
}
