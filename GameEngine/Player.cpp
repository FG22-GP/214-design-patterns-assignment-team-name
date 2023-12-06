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
