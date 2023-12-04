//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameInfo.h"
#include "Pikachu.h"
#include "Window.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const char* pikachuImagePath{"img/pikachu.png"};

int main(int argc, char* args[])
{
    //The window we'll be rendering to
    //SDL_Window* window{};
    //SDL_Renderer* renderer; // the window's rendering surface

    // initialize SDL_Image for image loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    // initialize SDL_ttf for font loading
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    //Start up SDL and create window
    Window* window = new Window{SCREEN_WIDTH, SCREEN_HEIGHT};

    GameInfo* gameInfoInstance = GameInfo::GetInstance();
    gameInfoInstance->SetWindow(window);

    //Intialize Pikachu
    Pikachu* myPikachu = new Pikachu{};

    // load font
    auto font = TTF_OpenFont("font/lazy.ttf", 100);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // create text from font
    SDL_Color textColor = {0xff, 0xff, 0xff};
    //Render text surface
    SDL_Texture* textTexture; // The final optimized image

    // render the text into an unoptimized CPU surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "The lazy fox, blah blah", textColor);
    int textWidth, textHeight;
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    else
    {
        // Create texture GPU-stored texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface);
        if (textTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            return -1;
        }
        // Get image dimensions
        auto width = textSurface->w;
        auto height = textSurface->h;
        textWidth = textSurface->w;
        textHeight = textSurface->h;
        //Get rid of old loaded surface
        SDL_FreeSurface(textSurface);
    }

    SDL_Event e;
    bool quit = false;

    // while the user doesn't want to quit
    while (quit == false)
    {
        SDL_GetTicks(); // can be used, to see, how much time in ms has passed since app start

        
        // loop through all pending events from Windows (OS)
        while (SDL_PollEvent(&e))
        {
            myPikachu->HandleInput(e);
            
            // check, if it's an event we want to react to:
            switch (e.type)
            {
            case SDL_QUIT:
                {
                    quit = true;
                }
                break;
        
            // This is an example on how to use input events:
            // case SDL_KEYDOWN:
            //     {
            //         // input example: if left, then make pikachu move left
            //         if (e.key.keysym.sym == SDLK_LEFT)
            //         {
            //             //pikachuMoveRight = false;
            //         }
            //         // if right, then make pikachu move right
            //         if (e.key.keysym.sym == SDLK_RIGHT)
            //         {S
            //             //pikachuMoveRight = true;
            //         }
            //     }
            //     break;
            }
        }

        // This is an example for how to check, whether keys are currently pressed:
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_UP])
        {
            //pik_y--;
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            //pik_y++;
        }

        // clear the screen
        SDL_SetRenderDrawColor(window->renderer, 120, 60, 255, 255);
        SDL_RenderClear(window->renderer);

        // render Pikachu
        myPikachu->Draw();

        // SDL_Rect targetRectangle{
        // // render the text
        // targetRectangle = SDL_Rect{
        // 	500,
        // 	500,
        // 	textWidth,
        // 	textHeight
        // };
        // SDL_RenderCopy(window->renderer, textTexture, NULL, &targetRectangle);

        // present screen (switch buffers)
        SDL_RenderPresent(window->renderer);

        SDL_Delay(1); // can be used to wait for a certain amount of ms
    }

    return 0;
}
