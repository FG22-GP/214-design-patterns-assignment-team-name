#pragma once
#include <SDL_render.h>

class Window
{
public:
    Window(int ScreenWidth, int ScreenHeight);

    SDL_Renderer* renderer;

    void Clear(Uint8 r, Uint8 g, Uint8 b);
};
