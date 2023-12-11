#pragma once
#include <set>

#include "GameObject.h"
#include "Vector2.h"

class Player : public GameObject
{
#pragma region "Singleton logic"
    Player(){}
public:
    static Player& getInstance(){ static Player instance; return instance;}
    Player(Player const&) = delete;
    void operator=(Player const&) = delete;
#pragma endregion
    
private:
    float jumpSpeed = 5.f;
    float movementSpeed = 500.f;

    bool isGrounded = false;
    
    Vector2 MovementDirection;
    Vector2 PlayerPosition;

    float YForce = 0.f;
    float Gravity = -0.1f;
    
public:
    void SetMovementDirection(Vector2 dir);
    Vector2 GetMovementDirection();
    
    Vector2 GetPlayerPosition();
    void SetPlayerPosition(Vector2 movement);
    
    void Jump();
    void PlayerMovement(float input);
    void SetGrounded(bool grounding);

    void Tick(float deltaTime) override;
};
