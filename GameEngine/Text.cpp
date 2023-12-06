﻿#include "Text.h"

#include <format>
#include <SDL_image.h>
#include <SDL_ttf.h>

Text::Text(const char* textString, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color)
{
    // render the text into an unoptimized CPU surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textString, color);

    if (textSurface == NULL)
    {
        throw std::runtime_error(std::format("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError()));
    }
    else
    {
        // create texture GPU-stored texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL)
        {
            throw std::runtime_error(std::format("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError()));
        }
        // get image dimensions
        textWidth = textSurface->w;
        textHeight = textSurface->h;
        // get rid of old loaded surface
        SDL_FreeSurface(textSurface);
    }
}
