#pragma once
#include <set>

#include "Vector2.h"

class Player
{
    float jumpSpeed;
    float movementSpeed;

    bool isGrounded;
    
    Vector2 MovementDirection;
    Vector2 PlayerPosition;
    
public:
    void SetMovementDirection(Vector2 dir);
    Vector2 GetMovementDirection();
    
    Vector2 GetPlayerPosition();
    void SetPlayerPosition(Vector2 movement);
    
    void Jump();
    void PlayerMovement(float input);
    void SetGrounded(bool grounding);
};
