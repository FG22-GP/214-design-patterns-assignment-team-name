#include "WinPoint.h"
#include "Text.h"
#include "Engine.h"

void WinPoint::Win()
{
    Text winText = Text("You won!", Engine::GetInstance()->GetWindow()->renderer, "font/lazy.ttf", SDL_Color{255,255,255,255} );
}