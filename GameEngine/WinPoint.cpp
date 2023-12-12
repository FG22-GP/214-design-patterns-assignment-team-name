#include "WinPoint.h"
#include "Constants.h"
#include "Text.h"
#include "Engine.h"

void WinPoint::Win()
{
    Text winText = Text("You won!", Engine::GetInstance()->GetWindow()->renderer,
        Constants::FONTFILEPATH.c_str(), SDL_Color{255,255,255,255},
        {100, 600}, {Constants::SCREEN_WIDTH/2, Constants::SCREEN_HEIGHT/2} );
    
    SetWinBoolean(true);
}

void WinPoint::WinPointHandle()
{
    
}
