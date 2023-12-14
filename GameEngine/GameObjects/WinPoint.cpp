#include "WinPoint.h"
#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Text.h"
#include "../EngineClasses/Engine.h"
#include "../HelperClasses/HelperFunctions.h"
#include "Player.h"

void WinPoint::Win()
{
    Text winText = Text("You won!", Engine::GetInstance()->GetWindow()->renderer,
        Constants::FONTFILEPATH.c_str(), SDL_Color{255,255,255,255},
        {100, 600}, {Constants::SCREEN_WIDTH/2, Constants::SCREEN_HEIGHT/2} );
}

void WinPoint::WinPointHandle()
{
    if(HelperFunctions::CheckIntersection(Player::getInstance().sprite->position, Player::getInstance().sprite->size, winPointSprite->position, winPointSprite->size))
    {
        SetWinBoolean(true);
    }
}
