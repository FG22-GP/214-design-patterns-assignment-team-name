#pragma once

#include "Vector2.h"
#include "Sprite.h"
#include "Window.h"
#include "Texture.h"

#include <SDL.h>
#include <list>
#include <string>
#include <map>

class Engine
{
protected:
	Engine();
	inline static Engine* singleton_;

	Window* window = nullptr;

public:
	bool quit = false;
	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;

	static Engine* GetInstance();
	void Setup(int screenWidth, int screenHeight);

	void Clear();

	void Present();
protected:
	std::map<std::string, Texture*> textures;
	std::list<Sprite*> sprites;
public:
	Sprite* GetSprite(std::string path, Vector2 position, Vector2 size, bool isCollider);
	void ReturnSprite(Sprite* sprite);

	void RenderSprite(Sprite* sprite, Vector2 relativePosition);

	Window* GetWindow() const { return window; }
};
