#include <SDL.h>
#include <string>

#include "HelperFunctions.h"
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

//Platforms
const int platformAmount = 7;
Vector2 platformLocations[platformAmount]
{
	Vector2{0,600},
	Vector2{300,600},
	Vector2{600,600},
	Vector2{900,600},

	Vector2{0,200},
	Vector2{300,500},
	Vector2{600,400},
};
Sprite* platforms[platformAmount];

//Delta time
float LastFrameTime = 0.f;
float CurrentFrameTime = 0.f;
float GetDeltaTime()
{
	return CurrentFrameTime - LastFrameTime;
}

Uint32 SetGroundedOnPlayer(Uint32 interval, void* name)
{
	Player::getInstance().SetGrounded(true);
	return 0;
}

int main(int argc, char* args[])
{
	Engine* engine = Engine::GetInstance();
	engine->Setup(SCREEN_WIDTH, SCREEN_WIDTH);

	Player& player = Player::getInstance();

	player.PlayerSprite = engine->GetSprite(pikachuImagePath, Vector2 {0.0, 0.0}, Vector2 {200.0, 200.0}, false);
	
	//Create platforms
	for (int i = 0; i < platformAmount; i++)
	{
		platforms[i] = engine->GetSprite("img/Wall.png", platformLocations[i], Vector2 {300, 100}, false);
	}

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
			player.PlayerMovement(-1);
		}
		if (keystate[SDL_SCANCODE_D])
		{
			player.PlayerMovement(1);
		}
		if(keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_W])
		{
			player.Jump();
		}
#pragma endregion

#pragma region COLLISION
		//Collision
		bool grounded = false;
		for (Sprite* platform : platforms)
		{
			if(HelperFunctions::CheckIntersection(player.PlayerSprite->position, player.PlayerSprite->size, platform->position, platform->size))
			{
				Vector2 IntersectionLoc = HelperFunctions::GetIntersectionPointAABB(player.PlayerSprite->position, player.PlayerSprite->size, platform->position, platform->size);
				
				//Platform is to the left or right of player
				float Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - player.PlayerMiddle()), HelperFunctions::Normalize(player.GetMovementDirection()));
				if(Dot > 0.8f)
				{
					player.SetMovementDirection({0,0});
				}

				//Platform is below player
				Dot = HelperFunctions::DotProduct(HelperFunctions::Normalize(IntersectionLoc - player.PlayerMiddle()), Vector2{0,1});
				if(Dot > 0.6f)
				{
					grounded = true;
					SDL_AddTimer(1, SetGroundedOnPlayer, const_cast<char*>("GroundedTimer")); //Timer because otherwise the players grounded value will always be set to true after touching a platform once, meaning they wont be able to jump
				}

				//Platform is above player
				if(Dot < -0.6f)
				{
					player.YForce = HelperFunctions::Clamp(player.YForce, 0, INFINITY);
				}
				
			}
		}
		//Set the players grounded value even if collision wasn't detected. Otherwise, player would float when walking off platforms
		if(!grounded)
		{
			player.SetGrounded(false);
		}
#pragma endregion

		//Tick player and move player sprite TODO move player sprite to a location thats relative to the cameras instead of setting it straight to the players location
		player.Tick(GetDeltaTime());
		player.PlayerSprite->position = player.GetPlayerPosition();
		
#pragma region RENDERING
		engine->Clear();

		for (Sprite* platform : platforms)
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

