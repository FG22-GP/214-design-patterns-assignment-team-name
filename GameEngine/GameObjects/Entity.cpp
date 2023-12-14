#include "Entity.h"


Vector2 Entity::GetMiddle()
{
    return GetPosition() + sprite->size * .5f;
}

Vector2 Entity::GetPosition()
{
    return position;
}

Vector2 Entity::SetPosition(Vector2 newPosition)
{
    return position = newPosition;
}

Vector2 Entity::GetMovementDirection()
{
    return movementDirection;
}

void Entity::SetMovementDirection(const Vector2& direction)
{
    movementDirection = direction;
}

void Entity::SetGrounded(bool grounding)
{
    isGrounded = grounding;
    if(grounding)
    {
        yForce = 0.f;
    }
}
