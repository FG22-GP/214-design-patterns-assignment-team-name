#pragma once
#include <SDL_render.h>
#include "Font.h"
#include "Vector2.h"

class Text
{
public:
    Text(const char* textString, SDL_Renderer* renderer, const char* fontFilePath, SDL_Color color, Vector2 TextSize, Vector2 TextPosition);
    
    SDL_Texture* textTexture;

    int textWidth;
    int textHeight;
};
