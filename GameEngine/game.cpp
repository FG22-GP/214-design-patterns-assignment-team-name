#include <SDL.h>
#include <string>

#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "Window.h"
#include "Engine.h"
#include "Player.h"
#include "Vector2.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//File path constants
std::string pikachuImagePath {"img/pikachu.png"};
std::string fontFilePath {"font/lazy.ttf"};

float LastFrameTime = 0.f;
float CurrentFrameTime = 0.f;
float GetDeltaTime()
{
	return CurrentFrameTime - LastFrameTime;
}

int main(int argc, char* args[])
{
	Engine* engine = Engine::GetInstance();
	engine->Setup(SCREEN_WIDTH, SCREEN_WIDTH);

	Sprite* pikachu = engine->GetSprite(pikachuImagePath, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);
	

	// create text
	//SDL_Color textColor = { 0xff, 0xff, 0xff };
	//const char* textString = "This is a piece of text";
	//Text text {textString, window.renderer, fontFilePath, textColor};

	SDL_Event e;
	bool quit = false;

	// while the user doesn't want to quit
	while (quit == false)
	{
		//Update delta time values
		LastFrameTime = CurrentFrameTime;
		CurrentFrameTime = (float)SDL_GetTicks() / 1000.f;

		Player::getInstance().PlayerMovement(0);

		// loop through all pending events from Windows (OS)
		while (SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Input (should be moved to its own class)
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_A])
		{
			Player::getInstance().PlayerMovement(-1);
		}
		if (keystate[SDL_SCANCODE_D])
		{
			Player::getInstance().PlayerMovement(1);
		}
		if(keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_W])
		{
			Player::getInstance().Jump();
		}

		//Move player sprite to player location and tick player
		pikachu->position = Player::getInstance().GetPlayerPosition();
		Player::getInstance().Tick(GetDeltaTime());
				
		engine->Clear();
		engine->RenderSprite(pikachu);
		engine->Present();

		SDL_Delay(10); // can be used to wait for a certain amount of ms
	}

	return 0;
}

