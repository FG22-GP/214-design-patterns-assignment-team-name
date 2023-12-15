#include "Player.h"

#include "PlatformHandler.h"
#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Engine.h"
#include "../Animation/PlayerAnimation/PlayerAnimator.h"
#include "../HelperClasses/HelperFunctions.h"

void Player::Setup()
{
    Engine* engine = Engine::GetInstance();
    sprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);

    // Animator setup
    animator = PlayerAnimator{sprite, "Idle", this};
}


void Player::Jump()
{
    if (isGrounded)
    {
        yForce = -jumpSpeed;
        SetGrounded(false);
    }
}

void Player::PlayerMovement(float input)
{
    SetMovementDirection(Vector2(input * movementSpeed, 0));
    
    if (input != 0.f)
    {
        LastRecordedDirectionPress = input;
    }
}

void Player::Tick(float deltaTime)
{
    // Resolve forces
    if (!isGrounded)
    {
        yForce -= Gravity;
    }
    else
    {
        yForce = 0.f;
    }

    // Move player
    SetPosition(GetPosition() + GetMovementDirection() * deltaTime + Vector2(0, yForce));

    // Update sprite location
    sprite->position = GetPosition();

    // Animation
    animator.UpdateSprite();
}


void Player::HasCollidedWith(Entity* collidedEntity)
{
    Vector2 IntersectionLoc = HelperFunctions::GetIntersectionPointAABB(sprite->position, sprite->size, collidedEntity->sprite->position, collidedEntity->sprite->size);
    
}
