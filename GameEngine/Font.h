#pragma once
#include <SDL_ttf.h>

class Font
{
public:
    Font(const char* fontFilePath);

    TTF_Font* font;
};
