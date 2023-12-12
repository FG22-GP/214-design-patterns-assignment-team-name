#include <SDL.h>
#include <string>

#include "Camera.h"
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
#include "Input/QuitCommand.h"

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
	player.PlayerSprite = engine->GetSprite(Constants::PLAYERSPRITEFILEPATH, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);
	
	//Input setup
	Input input = Input{};
	MoveLeftCommand moveLeft = MoveLeftCommand{};
	MoveRightCommand moveRight = MoveRightCommand{};
	JumpCommand jump = JumpCommand{};
	QuitCommand quitting = QuitCommand{};
	input.MoveLeftAction = &moveLeft;
	input.MoveRightAction = &moveRight;
	input.JumpAction = &jump;

	//Collision setup
	PlatformHandler platformHandler;
	platformHandler.Setup();

	//Camera setup
	Camera camera = Camera{};

	// create text
	//SDL_Color textColor = { 0xff, 0xff, 0xff };
	//const char* textString = "This is a piece of text";
	//Text text {textString, window.renderer, fontFilePath, textColor};

	SDL_Event e;

	// while the user doesn't want to quit
	while (Engine::GetInstance()->quit == false)
	{
		//Update delta time values
		LastFrameTime = CurrentFrameTime;
		CurrentFrameTime = (float)SDL_GetTicks() / 1000.f;

		player.PlayerMovement(0);

		//Quit input
		while (SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				Engine::GetInstance()->quit = true;
			}
		}

		//Player input
		input.GetInput();

		//Collision
		platformHandler.HandleCollision();

		//Tick player
		player.Tick(GetDeltaTime());
		player.PlayerSprite->position = player.GetPlayerPosition();

		//Update camera position
		camera.Position = Vector2{player.PlayerMiddle().x - Constants::SCREEN_WIDTH / 2, 0};
		
#pragma region RENDERING
		engine->Clear();

		for (Sprite* platform : platformHandler.platforms)
		{
			engine->RenderSprite(platform, camera.GetRelativeLocation(platform->position));
		}
		engine->RenderSprite(player.PlayerSprite, camera.GetRelativeLocation(player.GetPlayerPosition()));
		
		engine->Present();
#pragma endregion

		SDL_Delay(10);
	}

	return 0;
}

