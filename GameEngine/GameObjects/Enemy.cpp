﻿#include "Enemy.h"
#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Engine.h"
#include "../EngineClasses/Vector2.h"
#include "../EngineClasses/Sprite.h"

Enemy::Enemy(Vector2 position)
{
    this->position = position;
}

void Enemy::EnemyMovement(float input)
{
    SetMovementDirection(Vector2(input * movementSpeed, 0));
    LastRecordedDirection = input;
}

void Enemy::Setup()
{
    Engine* engine = Engine::GetInstance();
    sprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0, 0}, Vector2 {200.0, 200.0}, false);

    movementDirection = Vector2(10, 0);

    SetPosition(position);
    
}

void Enemy::Tick(float deltaTime)
{
    if(!isGrounded)
    {
        yForce -= Gravity;
    }else
    {
        yForce = 0.f;
    }
    
    SetPosition(GetPosition() + movementDirection * deltaTime + Vector2(0, yForce));
    
    sprite->position = GetPosition();
}

