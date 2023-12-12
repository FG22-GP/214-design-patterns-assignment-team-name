#include <SDL.h>
#include <string>
#include "Constants.h"
#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "Window.h"
#include "Engine.h"
#include "PlatformHandler.h"
#include "Player.h"
#include "Vector2.h"
#include "Input/Input.h"
#include "Input/JumpCommand.h"
#include "Input/MoveLeftCommand.h"
#include "Input/MoveRightCommand.h"

//File path constants
std::string pikachuImagePath {"img/pikachu.png"};
std::string fontFilePath {"font/lazy.ttf"};

//Delta time
float LastFrameTime = 0.f;
float CurrentFrameTime = 0.f;
float GetDeltaTime()
{
	return CurrentFrameTime - LastFrameTime;
}

int main(int argc, char* args[])
{
	Engine* engine = Engine::GetInstance();
	engine->Setup(Constants::SCREEN_WIDTH, Constants::SCREEN_WIDTH);

	//Player setup
	Player& player = Player::getInstance();
	player.PlayerSprite = engine->GetSprite(pikachuImagePath, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);
	
	//Input setup
	Input input = Input{};
	MoveLeftCommand moveLeft = MoveLeftCommand{};
	MoveRightCommand moveRight = MoveRightCommand{};
	JumpCommand jump = JumpCommand{};
	input.MoveLeftAction = &moveLeft;
	input.MoveRightAction = &moveRight;
	input.JumpAction = &jump;

	PlatformHandler platformHandler;
	platformHandler.Setup();

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

		player.PlayerMovement(0);

#pragma region INPUT
		//Quit input
		while (SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Player input
		input.GetInput();
#pragma endregion

#pragma region COLLISION
		platformHandler.HandleCollision();
#pragma endregion

		//Tick player and move player sprite TODO move player sprite to a location thats relative to the cameras instead of setting it straight to the players location
		player.Tick(GetDeltaTime());
		player.PlayerSprite->position = player.GetPlayerPosition();
		
#pragma region RENDERING
		engine->Clear();

		for (Sprite* platform : platformHandler.platforms)
		{
			engine->RenderSprite(platform);
		}
		engine->RenderSprite(player.PlayerSprite);
		
		engine->Present();
#pragma endregion

		SDL_Delay(10);
	}

	return 0;
}

