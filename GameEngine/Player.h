#pragma once
#include <set>

#include "Vector2.h"

class Player
{
#pragma region "Singleton logic"
    Player(){}
public:
    static Player& getInstance(){ static Player instance; return instance;}
    Player(Player const&) = delete;
    void operator=(Player const&) = delete;
#pragma endregion
    
private:
    float jumpSpeed = 5.0f;
    float movementSpeed = 5.0f;

    bool isGrounded = false;
    
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
