#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <format>
#include <stdexcept>

Texture::Texture(SDL_Renderer* renderer, std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        throw std::runtime_error(std::format("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError()));
    }
    else
    {
        //Convert surface to screen format
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            throw std::runtime_error(std::format("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError()));
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
}