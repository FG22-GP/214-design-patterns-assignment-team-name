#pragma once
#include <SDL_render.h>
#include <string>

class Texture
{
public:
	SDL_Texture* texture = NULL;
	int references = 0;


	Texture(SDL_Renderer* renderer, std::string path);
};

