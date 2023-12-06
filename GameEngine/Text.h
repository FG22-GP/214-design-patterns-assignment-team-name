#pragma once
#include <SDL_render.h>
#include "Font.h"

class Text
{
public:
    Text(const char* textString, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);

    SDL_Texture* textTexture;

    int textWidth;
    int textHeight;
};
