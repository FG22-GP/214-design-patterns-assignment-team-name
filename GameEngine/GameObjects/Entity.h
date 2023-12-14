#pragma once
#include "../EngineClasses/Vector2.h"
#include "../EngineClasses/Sprite.h"

class Entity
{
public:
    virtual ~Entity() = default;

    Sprite* sprite;
    
    Vector2 position;
    Vector2 movementDirection;

    float yForce;
    int uniqueId;
    bool isGrounded;

    Entity* nextEntity;

    virtual Vector2 GetMiddle();
    virtual Vector2 GetPosition();
    virtual Vector2 SetPosition(Vector2 newPosition);
    
    virtual Vector2 GetMovementDirection();
    virtual void SetMovementDirection(const Vector2& direction);

    virtual void SetGrounded(bool grounding);

    virtual void Tick(float deltaTime) = 0;
    virtual void HasCollidedWith(Entity* collidedEntity) = 0;
    
};
