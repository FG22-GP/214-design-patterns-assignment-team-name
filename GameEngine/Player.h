#pragma once
#include <set>

#include "Engine.h"
#include "GameObject.h"
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
    float jumpSpeed = 7.f;
    float movementSpeed = 500.f;

    bool isGrounded = false;
    
    Vector2 MovementDirection;
    Vector2 PlayerPosition;
    
    float Gravity = -0.1f;
    
public:
    Sprite* PlayerSprite;
    
    float YForce = 0.f;
    
    void SetMovementDirection(Vector2 dir);
    Vector2 GetMovementDirection();
    
    Vector2 GetPlayerPosition();
    void SetPlayerPosition(Vector2 movement);
    
    Vector2 PlayerMiddle(){ return GetPlayerPosition() + PlayerSprite->size / 2.f;}
    
    void Jump();
    void PlayerMovement(float input);
    void SetGrounded(bool grounding);

    void Tick(float deltaTime);
};
