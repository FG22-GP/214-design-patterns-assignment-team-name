#pragma once
#include "Entity.h"


class Enemy : public Entity
{

public:
    Enemy(Vector2 position);
    
private:
    float movementSpeed = 500.f;

    //bool isGrounded = false;
    //Vector2 MovementDirection;
    //Vector2 EnemyPosition;
    
    float Gravity = -0.1f;
    
    float LastRecordedDirection = 0.f;

    
public:
    void EnemyMovement(float input);
    
    void Setup();
    void Tick(float deltaTime);
    
    // Sprite* EnemySprite;
    //
    // float YForce = 0.f;
    //void SetMovementDirection(Vector2 dir);
    //Vector2 GetPosition();
    //Vector2 EnemyMiddle();
    //void SetGrounded(bool grounding);
    //void SetEnemyPosition(Vector2 newPosition);
};
