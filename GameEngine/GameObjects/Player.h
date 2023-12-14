#pragma once
#include "../EngineClasses/Vector2.h"
#include "../EngineClasses/Sprite.h"
#include "../Animation/PlayerAnimation/PlayerAnimator.h"
#include "Entity.h"

class Player : public Entity
{
#pragma region "Singleton logic"
    Player() {}
public:
    static Player& getInstance() { static Player instance; return instance; }
    Player(Player const&) = delete;
    void operator=(Player const&) = delete;
#pragma endregion
    
private:
    float jumpSpeed = 7.f;
    float movementSpeed = 500.f;
    
    float Gravity = -0.1f;

    PlayerAnimator animator;

public:
    float LastRecordedDirectionPress = 0.f;
    
    void Jump();
    void PlayerMovement(float input);
    void Setup();
    void Tick(float deltaTime) override;
    //void Tick(float deltaTime);

    bool GetGrounded() { return isGrounded; }
};