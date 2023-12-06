#pragma once
#include <SDL_render.h>

class Sprite
{
public:
    Sprite(SDL_Renderer* renderer, const char* SpriteFilePath);

    SDL_Texture* sprite = NULL;
};
