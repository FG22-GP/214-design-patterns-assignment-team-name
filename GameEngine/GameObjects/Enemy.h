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
    void Tick(float gameTime) override;
    void Draw() override;
    
    void HasCollidedWith(Entity* collidedEntity) override;
};
