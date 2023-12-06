#pragma once
#include "Vector2.h"

class Player
{
public:
    Vector2 MovementDirection;
    
private:
    float jumpSpeed;
    float movementSpeed;

    bool isGrounded;
    
public:
    void Move(float input);
    void Jump();
    void SetGrounded(bool grounding);
};
