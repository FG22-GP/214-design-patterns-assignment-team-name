#pragma once
#include <SDL_render.h>

class Window
{
public:
    Window(int ScreenWidth, int ScreenHeight);

    SDL_Renderer* renderer;
};
