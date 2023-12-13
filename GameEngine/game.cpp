#include <SDL.h>
#include <string>

#include "Camera.h"
#include "Constants.h"
#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "Window.h"
#include "Engine.h"
#include "LosePoint.h"
#include "PlatformHandler.h"
#include "Player.h"
#include "Vector2.h"
#include "Input/Input.h"
#include "Input/JumpCommand.h"
#include "Input/MoveLeftCommand.h"
#include "Input/MoveRightCommand.h"
#include "Input/QuitCommand.h"
#include "WinPoint.h"

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
	player.Setup();
	
	//Input setup
	Input input = Input{};
	MoveLeftCommand moveLeft = MoveLeftCommand{};
	MoveRightCommand moveRight = MoveRightCommand{};
	JumpCommand jump = JumpCommand{};
	QuitCommand quitting = QuitCommand{};
	input.MoveLeftAction = &moveLeft;
	input.MoveRightAction = &moveRight;
	input.JumpAction = &jump;
	input.QuitAction = &quitting;

	//Collision setup
	PlatformHandler platformHandler;

	//Camera setup
	Camera camera = Camera{};

	//Win Point setup
	WinPoint winPoint;
	winPoint.winPointSprite = engine->GetSprite(Constants::WINSPRITEFILEPATH, Vector2 {1150.0, 0.0}, Vector2 {50.0, 600.0}, false);
	
	LosePoint losePoint;
	losePoint.losePointSprite = engine->GetSprite(Constants::WINSPRITEFILEPATH, Vector2 {-500.0, 1000.0}, Vector2 {2500.0, 50.0}, false);
	
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
		if(!winPoint.GetWinBoolean() && !losePoint.GetLoseBoolean())
		{
			//Collision
			platformHandler.HandleCollision();
			winPoint.WinPointHandle();
			losePoint.LosePointHandle();
			
			//Tick player
			player.Tick(GetDeltaTime());
			player.PlayerSprite->position = player.GetPlayerPosition();

			//Update camera position
			camera.Position = Vector2{player.PlayerMiddle().x - Constants::SCREEN_WIDTH / 2, 0};
		}
#pragma region RENDERING
		engine->Clear();

		for (Sprite* platform : platformHandler.platforms)
		{
			engine->RenderSprite(platform, camera.GetRelativeLocation(platform->position));
		}
		engine->RenderSprite(player.PlayerSprite, camera.GetRelativeLocation(player.GetPlayerPosition()));
		engine->RenderSprite(winPoint.winPointSprite, camera.GetRelativeLocation(winPoint.winPointSprite->position));
		engine->RenderSprite(losePoint.losePointSprite, camera.GetRelativeLocation(losePoint.losePointSprite->position));
		
		//Check if you won
		if(winPoint.GetWinBoolean())
			winPoint.Win();
		//Check if you lose
		else if(losePoint.GetLoseBoolean())
			losePoint.Lose();
		
		engine->Present();
#pragma endregion

		SDL_Delay(10);
	}

	return 0;
}

