#include <SDL.h>
#include <string>

#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "Window.h"
#include "Engine.h"
#include "Vector2.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//File path constants
std::string pikachuImagePath {"img/pikachu.png"};
std::string fontFilePath {"font/lazy.ttf"};

int main(int argc, char* args[])
{
	Engine* engine = Engine::GetInstance();
	engine->Setup(SCREEN_WIDTH, SCREEN_WIDTH);

	Sprite* pikachu = engine->GetSprite(pikachuImagePath, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);

	// All data related to pikachu
	bool pikachuMoveRight = false;

	// create text
	//SDL_Color textColor = { 0xff, 0xff, 0xff };
	//const char* textString = "This is a piece of text";
	//Text text {textString, window.renderer, fontFilePath, textColor};

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
			pikachu->position.y -= 1.0;
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			pikachu->position.y += 1.0;
		}

		// our current game logic :)
		if (pikachuMoveRight) {
			pikachu->position.x += 1.0;

			if (pikachu->position.x > 599) pikachuMoveRight = false;
		}
		else {
			pikachu->position.x -= 1.0;

			if (pikachu->position.x < 1) pikachuMoveRight = true;
		}
				
		engine->Clear();

		engine->RenderSprite(pikachu);

		// render Pikachu
		//RenderTexture(pikachu.sprite, pik_x, pik_y, pik_w, pik_h);

		// render the text
		//RenderTexture(text.textTexture, 500, 500, text.textWidth, text.textHeight);

		engine->Present();

		SDL_Delay(10); // can be used to wait for a certain amount of ms
	}

	return 0;
}

