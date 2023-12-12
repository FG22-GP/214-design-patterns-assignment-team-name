#include "Input.h"
#include <SDL_keyboard.h>

void Input::GetInput()
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_A])
    {
        MoveLeftAction->Execute();
    }
    if (keystate[SDL_SCANCODE_D])
    {
        MoveRightAction->Execute();
    }
    if(keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_W])
    {
        JumpAction->Execute();
    }
}
