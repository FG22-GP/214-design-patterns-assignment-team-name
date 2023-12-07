#include "Player.h"

void Player::Move(float input)
{
    MovementDirection.x = input * movementSpeed;
}

void Player::Jump()
{
    if(isGrounded)
    {
        MovementDirection.y = jumpSpeed;
        SetGrounded(false);
    }
}

void Player::SetGrounded(bool grounding)
{
    isGrounded = grounding;
}

Vector2 Player::GetPlayerPosition()
{
    return PlayerPosition;
}

void Player::UpdatePlayerPosition(Vector2 movement)
{
    PlayerPosition += movement;
}
