#include "Pikachu.h"

#include <cstdio>
#include <SDL_image.h>


void Pikachu::LoadTexture()
{
    gameInfoInstance->window->screenSurface = IMG_Load(pikachuImagePath);
    if (gameInfoInstance->window->screenSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", pikachuImagePath, IMG_GetError());
        //return -1;
    }
    else
    {
        //Convert surface to screen format
        pikachu = SDL_CreateTextureFromSurface(gameInfoInstance->window->renderer,
                                               gameInfoInstance->window->screenSurface);
        if (pikachu == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", pikachuImagePath, SDL_GetError());
            //return -1;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(gameInfoInstance->window->screenSurface);
    }
}

void Pikachu::HandleInput(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        {
            // Input events for Pikachu
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                MoveLeft();
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                MoveRight();
            }
        }
        break;

    default:
        
        break;
    }
}

void Pikachu::MoveLeft()
{
    pik_x-=5;
}

void Pikachu::MoveRight()
{
    pik_x+=5;
}

void Pikachu::Update()
{
}

void Pikachu::Draw()
{
    SDL_Rect targetRectangle{
        pik_x,
        pik_y,
        pik_w,
        pik_h
    };
    SDL_RenderCopy(gameInfoInstance->window->renderer, pikachu, NULL, &targetRectangle);
}
