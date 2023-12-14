#include "Engine.h"

#include "Vector2.h"
#include "Window.h"
#include "Sprite.h"

#include <SDL.h>

Engine::Engine()
{
	window = nullptr;
}

Engine* Engine::GetInstance()
{
	if (singleton_ == nullptr)
	{
		singleton_ = new Engine();
	}
	return singleton_;
}

void Engine::Setup(int screenWidth, int screenHeight)
{
	window = new Window(screenWidth, screenHeight);
}

void Engine::Clear()
{
	window->Clear(0, 0, 0);
}

void Engine::Present()
{
	SDL_RenderPresent(window->renderer);
}

Sprite* Engine::GetSprite(std::string path, Vector2 position, Vector2 size, bool isCollider)
{
	Texture* texture = nullptr;

	if (!textures.contains(path))
	{
		texture = new Texture(window->renderer, path);
		textures[path] = texture;
	}
	else
	{
		texture = textures[path];
	}

	texture->references++;

	Sprite* sprite;

	if (sprites.empty())
	{
		sprite = new Sprite();
	}
	else
	{
		sprite = sprites.front();
		sprites.pop_front();
	}

	sprite->texture = texture;
	sprite->position = position;
	sprite->size = size;
	sprite->isCollider = isCollider;

	return sprite;
}

void Engine::ReturnSprite(Sprite* sprite) 
{
	sprite->texture->references--;

	// TODO: Delete texture if references are 0

	sprite->Reset();
	sprites.push_back(sprite);
}

void Engine::RenderSprite(Sprite* sprite, Vector2 relativePosition)
{
	SDL_Rect targetRectangle = SDL_Rect{
		(int)relativePosition.x,
		(int)relativePosition.y,
		(int)sprite->size.x,
		(int)sprite->size.y
	};

	if(sprite->flip)
	{
		SDL_RenderCopyEx(window->renderer, sprite->texture->texture, nullptr, &targetRectangle, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}else
	{
		SDL_RenderCopy(window->renderer, sprite->texture->texture, nullptr, &targetRectangle);
	}
}