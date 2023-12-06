#pragma once
#include <SDL_ttf.h>

class Font
{
public:
    Font(const char* FontFilePath);

    TTF_Font* font;
};
