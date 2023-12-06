#include <SDL.h>

#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "Window.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//File path constants
const char* pikachuImagePath {"img/pikachu.png"};
const char* fontFilePath {"font/lazy.ttf"};

//Window
Window window {SCREEN_WIDTH, SCREEN_HEIGHT};

//Sprites (GameObjects)
Sprite pikachu {window.renderer, pikachuImagePath};

//Functions
void RenderTexture(SDL_Texture* texture, int PosX, int PosY, int SizeX, int SizeY)
{
	SDL_Rect targetRectangle = SDL_Rect{
		PosX,
		PosY,
		SizeX,
		SizeY
	};
	SDL_RenderCopy(window.renderer, texture, NULL, &targetRectangle);
}

int main(int argc, char* args[])
{
	// All data related to pikachu
	bool pikachuMoveRight = false;
	int pik_x, pik_y;
	pik_x = pik_y = 0;
	int pik_w, pik_h;
	pik_w = pik_h = 200;
	
	// create text
	SDL_Color textColor = { 0xff, 0xff, 0xff };
	const char* textString = "This is a piece of text";
	Text text {textString, window.renderer, fontFilePath, textColor};

	SDL_Event e; bool quit = false;

	// while the user doesn't want to quit
	while (quit == false)
	{
		SDL_GetTicks(); // can be used, to see, how much time in ms has passed since app start


		// loop through all pending events from Windows (OS)
		while (SDL_PollEvent(&e))
		{
			// check, if it's an event we want to react to:
			switch (e.type) {
				case SDL_QUIT: {
					quit = true;
				} break;

					// This is an example on how to use input events:
				case SDL_KEYDOWN: {
					// input example: if left, then make pikachu move left
					if (e.key.keysym.sym == SDLK_LEFT) {
						pikachuMoveRight = false;
					}
					// if right, then make pikachu move right
					if (e.key.keysym.sym == SDLK_RIGHT) {
						pikachuMoveRight = true;
					}
				} break;
			} 
		}

		// This is an example for how to check, whether keys are currently pressed:
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_UP])
		{
			pik_y--;
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			pik_y++;
		}

		// our current game logic :)
		if (pikachuMoveRight) {
			pik_x++;
			if (pik_x > 599) pikachuMoveRight = false;
		}
		else {
			pik_x--;
			if (pik_x < 1) pikachuMoveRight = true;
		}
		
		// clear the screen
		SDL_SetRenderDrawColor(window.renderer, 120, 60, 255, 255);
		SDL_RenderClear(window.renderer);
		
		// render Pikachu
		RenderTexture(pikachu.sprite, pik_x, pik_y, pik_w, pik_h);

		// render the text
		RenderTexture(text.textTexture, 500, 500, text.textWidth, text.textHeight);

		// present screen (switch buffers)
		SDL_RenderPresent(window.renderer);

		SDL_Delay(10); // can be used to wait for a certain amount of ms
	}

	return 0;
}

