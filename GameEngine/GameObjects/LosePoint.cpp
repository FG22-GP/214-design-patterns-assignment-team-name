#include "LosePoint.h"
#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Text.h"
#include "../EngineClasses/Engine.h"
#include "../HelperClasses/HelperFunctions.h"
#include "Player.h"

void LosePoint::Lose()
{
    Text winText = Text("You Lost!", Engine::GetInstance()->GetWindow()->renderer,
        Constants::FONTFILEPATH.c_str(), SDL_Color{255,255,255,255},
        {100, 600}, {Constants::SCREEN_WIDTH/2, Constants::SCREEN_HEIGHT/2} );
}

void LosePoint::LosePointHandle()
{
    if(HelperFunctions::CheckIntersection(Player::getInstance().sprite->position, Player::getInstance().sprite->size, losePointSprite->position, losePointSprite->size))
    {
        SetLoseBoolean(true);
    }
}
