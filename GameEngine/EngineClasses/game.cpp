#include <SDL.h>

#include "../GameObjects/Camera.h"
#include "../HelperClasses/Constants.h"
#include "Sprite.h"
#include "Engine.h"
#include "../GameObjects/LosePoint.h"
#include "../GameObjects/PlatformHandler.h"
#include "../GameObjects/Player.h"
#include "Vector2.h"
#include "../GameObjects/CollisionManager.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/EntityManager.h"
#include "../Input/Input.h"
#include "../GameObjects/WinPoint.h"
#include "../Gui/View.h"

//Delta time
float LastFrameTime = 0.f;
float CurrentFrameTime = 0.f;
float GetDeltaTime()
{
	return CurrentFrameTime - LastFrameTime;
}

void ExitButtonClicked()
{
	auto engine = Engine::GetInstance();
	engine->quit = true;
}

int main(int argc, char* args[])
{
	Engine* engine = Engine::GetInstance();
	engine->Setup(Constants::SCREEN_WIDTH, Constants::SCREEN_WIDTH);

	//EntityManager entityManager = EntityManager{};
	CollisionManager collisionManager = CollisionManager{};
	
	//Player setup
	Player& player = Player::getInstance();
	player.Setup();
	EntityManager::GetInstance().AddEntity(&player);

	View* view = new View();
	view->items.push_back(new Button(engine->GetWindow()->renderer, 0.45, 0.95, 0.1, 0.05, "Exit", true, &ExitButtonClicked, new Font(Constants::FONTFILEPATH.c_str())));

	Enemy enemy = Enemy{Vector2(300, 0)};
	enemy.Setup();
	EntityManager::GetInstance().AddEntity(&enemy);
	
	//Input setup
	Input input = Input{};

	//Collision setup
	PlatformHandler platformHandler;

	//Camera setup
	Camera camera = Camera{};

	//Win and lose points setup
	WinPoint winPoint;
	winPoint.winPointSprite = engine->GetSprite(Constants::WINSPRITEFILEPATH, Vector2 {5850.0, 0.0}, Vector2 {50.0, 600.0}, false);
	LosePoint losePoint;
	losePoint.losePointSprite = engine->GetSprite(Constants::WINSPRITEFILEPATH, Vector2 {-500.0, 1000.0}, Vector2 {8000.0, 50.0}, false);

	SDL_Event e;
	// while the user doesn't want to quit
	while (Engine::GetInstance()->quit == false)
	{
		//Update delta time values
		LastFrameTime = CurrentFrameTime;
		CurrentFrameTime = (float)SDL_GetTicks() / 1000.f;

		player.PlayerMovement(0);

		//Event polling, mainly ui input and 
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				Engine::GetInstance()->quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					view->HandleClick((float)e.button.x, (float)e.button.y);
				}
				break;
			}
		}
		
		//Player input
		input.GetInput();
		
		if(!winPoint.GetWinBoolean() && !losePoint.GetLoseBoolean())
		{
			//Collision
			platformHandler.HandleCollision(enemy);
			platformHandler.HandleCollision(player);

			winPoint.WinPointHandle();
			losePoint.LosePointHandle();

			//Update Collision (Entities)
			collisionManager.CollisionUpdate();

			//Update Entities
			EntityManager::GetInstance().Update(GetDeltaTime());

			//player.Tick(GetDeltaTime());
			
			//Update camera position
			camera.Position = Vector2{player.GetMiddle().x - Constants::SCREEN_WIDTH / 2, 0};
		}
		
#pragma region RENDERING
		engine->Clear();

		for (Sprite* platform : platformHandler.platforms)
		{
			engine->RenderSprite(platform, camera.GetRelativeLocation(platform->position));
		}
		//engine->RenderSprite(player.sprite, camera.GetRelativeLocation(player.sprite->position));
		engine->RenderSprite(winPoint.winPointSprite, camera.GetRelativeLocation(winPoint.winPointSprite->position));
		engine->RenderSprite(losePoint.losePointSprite, camera.GetRelativeLocation(losePoint.losePointSprite->position));
		//engine->RenderSprite(enemy.sprite, camera.GetRelativeLocation(enemy.sprite->position));
			
		EntityManager::GetInstance().Draw(camera);
		
		//Check if you won
		if(winPoint.GetWinBoolean())
			winPoint.Win();
		//Check if you lose
		else if(losePoint.GetLoseBoolean())
			losePoint.Lose();
		
		view->Render(engine->GetWindow()->renderer);

		engine->Present();
#pragma endregion

		SDL_Delay(10);
	}
	return 0;
}