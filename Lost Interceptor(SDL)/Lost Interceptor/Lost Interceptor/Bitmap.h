#pragma once
#include <string>
#include <iostream>
#include "SDL.h"


//forward declarations
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;


class Bitmap
{
public:
	Bitmap(SDL_Renderer* renderer, const std::string& filename, bool useTransparency = true);
	~Bitmap();

	void Draw(int x, int y);
	int getWidth();
	int getHeight();

private:
	//SDL content
	SDL_Surface* b_bmpSurface{ nullptr };
	SDL_Texture* b_bmpPixelTexture{ nullptr };
	SDL_Texture* b_bmpTexture{ nullptr };
	SDL_Renderer* b_renderer{ nullptr };
	//attributes to be assigned
	int	width{ 0 }, height{ 0 }, b_x{ 0 }, b_y{ 0 };
};


