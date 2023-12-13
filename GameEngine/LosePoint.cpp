#include "LosePoint.h"
#include "Constants.h"
#include "Text.h"
#include "Engine.h"
#include "HelperFunctions.h"
#include "Player.h"

void LosePoint::Lose()
{
    Text winText = Text("You Lost!", Engine::GetInstance()->GetWindow()->renderer,
        Constants::FONTFILEPATH.c_str(), SDL_Color{255,255,255,255},
        {100, 600}, {Constants::SCREEN_WIDTH/2, Constants::SCREEN_HEIGHT/2} );
}

void LosePoint::LosePointHandle()
{
    if(HelperFunctions::CheckIntersection(Player::getInstance().PlayerSprite->position, Player::getInstance().PlayerSprite->size, losePointSprite->position, losePointSprite->size))
    {
        SetLoseBoolean(true);
    }
}
