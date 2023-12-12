#include "PlatformHandler.h"
#include "HelperFunctions.h"
#include "Sprite.h"

void PlatformHandler::Setup()
{
    Engine* engine = Engine::GetInstance();
    for (int i = 0; i < PlatformAmount; i++)
    {
        platforms[i] = engine->GetSprite("img/Wall.png", platformLocations[i], Vector2 {300, 100}, false);
    }
}

void PlatformHandler::HandleCollision()
{
    //Collision
    bool grounded = false;
    for (Sprite* platform : platforms)
    {
        if(HelperFunctions::CheckIntersection(Player::getInstance().PlayerSprite->position, Player::getInstance().PlayerSprite->size, platform->position, platform->size))
        {
            Vector2 IntersectionLoc = HelperFunctions::GetIntersectionPointAABB(Player::getInstance().PlayerSprite->position, Player::getInstance().PlayerSprite->size, platform->position, platform->size);
				
            //Platform is to the left or right of player
            float Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - Player::getInstance().PlayerMiddle()), HelperFunctions::Normalize(Player::getInstance().GetMovementDirection()));
            if(Dot > 0.8f)
            {
                Player::getInstance().SetMovementDirection({0,0});
            }

            //Platform is below player
            Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - Player::getInstance().PlayerMiddle()), Vector2{0,1});
            if(Dot > 0.6f)
            {
                grounded = true;
                SDL_AddTimer(1, SetGroundedOnPlayer, const_cast<char*>("GroundedTimer")); //Timer because otherwise the players grounded value will always be set to true after touching a platform once, meaning they wont be able to jump
            }

            //Platform is above Player::getInstance()
            if(Dot < -0.6f)
            {
                Player::getInstance().YForce = HelperFunctions::Clamp(Player::getInstance().YForce, 0, INFINITY);
            }
				
        }
    }
    //Set the players grounded value even if collision wasn't detected. Otherwise, player would float when walking off platforms
    if(!grounded)
    {
        Player::getInstance().SetGrounded(false);
    }
}
