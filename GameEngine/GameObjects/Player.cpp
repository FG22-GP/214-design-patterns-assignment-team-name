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
    bool grounded = false;
    
    Vector2 IntersectionLoc = HelperFunctions::GetIntersectionPointAABB(sprite->position, sprite->size, collidedEntity->sprite->position, collidedEntity->sprite->size);

    //Collision on left/right side
    float dot = HelperFunctions::DotProduct(IntersectionLoc - GetMiddle(), HelperFunctions::Normalize(GetMovementDirection()));
    if (dot > 0.8f)
    {
        SetMovementDirection(Vector2{0, 0});
    }

    // Collision under player
    dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - GetMiddle()), Vector2{0, 1});
    if (dot > 0.6f)
    {
        grounded = true;
        SetGrounded(true);
        //SDL_AddTimer(1, SetGroundedOnPlayer, this);
    }

    // Platform is above the player
    if (dot < -0.6f)
    {
        yForce = HelperFunctions::Clamp(yForce, 0, INFINITY);
    }

    if (!grounded)
    {
        SetGrounded(false);
    }
    
}

// Set the player's grounded value even if collision wasn't detected.
// Otherwise, the player would float when walking off platforms
Uint32 Player::SetGroundedOnPlayer(Uint32 interval, void* param)
{
    Entity* entity = static_cast<Entity*>(param);
    if (entity) entity->SetGrounded(true);
    return 0;
}
