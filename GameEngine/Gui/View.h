#include <list>
#include <string>
#include <SDL_render.h>
#include<SDL_ttf.h>

#include "../HelperClasses/Constants.h"
#include "../EngineClasses/Font.h"
#include <iostream>



typedef void (*Func)();

class ViewItem {
public:
	std::string name;

	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;
	Uint8 a = 255;

	bool visible = true;
	Func callback = nullptr;
	float clickable = false;
	float posX = 0.0;
	float posY = 0.0;
	float sizeX = 1.0;
	float sizeY = 1.0;
	std::list<ViewItem*> children;

	virtual void Render(SDL_Renderer* renderer, float offsetX, float offsetY, float width, float height) = 0;
	virtual bool HandleClick(float p_posX, float p_posY) = 0;
};


class Image : public ViewItem {
public:
	SDL_Texture* image;

	//virtual void Render(SDL_Renderer* renderer) override;
};

class Button : public ViewItem {
public:
	Button(SDL_Renderer* renderer, float p_posX, float p_posY, float p_sizeX, float p_sizeY, std::string p_text, bool p_clickable, Func p_callback, Font* p_font) {
		posX = p_posX;
		posY = p_posY;
		sizeX = p_sizeX;
		sizeY = p_sizeY;
		text = p_text;
		clickable = p_clickable;
		callback = p_callback;
		text = p_text;

		SDL_Color textColor = SDL_Color{text_r, text_g, text_b, text_a};
		auto surface = TTF_RenderText_Solid(p_font->font, text.c_str(), textColor);
		text_texture = SDL_CreateTextureFromSurface(renderer, surface);
	};

	Uint8 text_r = 0;
	Uint8 text_g = 0;
	Uint8 text_b = 0;
	Uint8 text_a = 255;


	virtual void Render(SDL_Renderer* renderer, float offsetX, float offsetY, float width, float height) override {
		if (!visible)
		{
			return;
		}

		SDL_FRect backgroundRect{
			offsetX + (width * posX),
			offsetY + (height * posY),
			(width * sizeX),
			(height * sizeY)
		};

		if (a != 0)
		{
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderFillRectF(renderer, &backgroundRect);
		}

		if (text_a != 0)
		{
			SDL_RenderCopyF(renderer, text_texture, nullptr, &backgroundRect);
		}

		for (auto child : children)
		{
			child->Render(renderer, backgroundRect.x, backgroundRect.y, backgroundRect.w, backgroundRect.h);
		}
	};

	// using the returned bool to indicate if the "click" has been consumed by a child
	virtual bool HandleClick(float p_posX, float p_posY) override {
		bool is_inside = false;
		if (
			p_posX >= posX &&
			p_posX <= posX + sizeX &&
			p_posY >= posY &&
			p_posY <= posY + sizeY
			)
		{
			is_inside = true;
		}

		if (!is_inside)
		{
			return false;
		}

		for (auto child : children)
		{
			if (child->HandleClick(p_posX - posX, p_posY - posY))
			{
				return true;
			}
		}

		if (clickable)
		{
			if (callback != nullptr)
			{
				callback();
			}

			return true;
		}

		return false;
	}

protected:
	std::string text;
	SDL_Texture* text_texture;
};

class View {
public:
	View() {};

	void Render(SDL_Renderer* renderer) {
		for (auto item : items)
		{
			item->Render(renderer, 0.0, 0.0, (float)Constants::SCREEN_WIDTH, (float)Constants::SCREEN_HEIGHT);
		}
	};

	void HandleClick(float posX, float posY) {
		for (auto item : items)
		{
			item->HandleClick(
				posX / (float)Constants::SCREEN_WIDTH, 
				posY / (float)Constants::SCREEN_HEIGHT
			);
		}
	};

	std::list<ViewItem*> items;
};