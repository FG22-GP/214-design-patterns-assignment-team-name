#include "Sprite.h"

#include <format>
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

Sprite::Sprite(SDL_Renderer* renderer, const char* SpriteFilePath)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(SpriteFilePath);
    if (loadedSurface == NULL)
    {
        throw std::runtime_error(std::format("Unable to load image %s! SDL_image Error: %s\n", SpriteFilePath, IMG_GetError()));
    }
    else
    {
        //Convert surface to screen format
        sprite = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (sprite == NULL)
        {
            throw std::runtime_error(std::format("Unable to create texture from %s! SDL Error: %s\n", SpriteFilePath, SDL_GetError()));
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
}
