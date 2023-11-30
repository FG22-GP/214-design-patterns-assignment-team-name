#pragma once
//#include "Image.h"
#include <memory>
#include <SDL.h>
#include <SDL_render.h>

extern class IImageLoader;

class Window
{
	
	//Whether Window Startup was successful
	bool success;
	// dependency to the ImageLoader
	IImageLoader* imageLoader;
public:
	Window(int width, int height/*, IImageLoader* imageLoader*/)
	{
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO))
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			//return -1;
		}

		// Create Window and Renderer
		SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
		if (!window)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			//return -1;
		}

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
		SDL_RenderSetLogicalSize(renderer, 1024, 768);
	}
	~Window();
	bool wasSuccessful() { return success; }
	//void render(Image* image);
	void clear();
	void present();
	//std::unique_ptr<Image> loadImage(const char* path);

	//SDL
	SDL_Renderer* renderer;
	//The window we'll be rendering to
	SDL_Window* window{};
	//The surface contained by the window
	SDL_Surface* screenSurface{};
};

