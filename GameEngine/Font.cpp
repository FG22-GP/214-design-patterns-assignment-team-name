#include "Font.h"

#include <format>
#include <SDL.h>
#include <SDL_ttf.h>

Font::Font(const char* FontFilePath)
{
    font = TTF_OpenFont(FontFilePath, 100);
    if (font == NULL)
    {
        throw std::runtime_error(std::format("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError()));
    }
}
