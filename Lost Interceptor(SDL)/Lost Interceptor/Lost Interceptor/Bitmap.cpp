#include "Bitmap.h"


using namespace std;

Bitmap::Bitmap(SDL_Renderer* renderer, const std::string& filename, bool useTransparency)
	: b_renderer{ renderer }
{
	b_bmpSurface = SDL_LoadBMP(filename.c_str());
	if (nullptr == b_bmpSurface)
	{
		//in case of loading failure, print error and stop
		std::cout << "SURFACE for bitmap: " << filename << " not loaded!"
			<< std::endl << SDL_GetError() << std::endl;
		return;
	}
	
	//if transparency is used, and it is for all bitmaps bar a stubborn border, assume magenta is the key
	if (useTransparency)
	{
		Uint32 colourKey = SDL_MapRGB(b_bmpSurface->format, 255, 0, 255);
		SDL_SetColorKey(b_bmpSurface, SDL_TRUE, colourKey);
	}
	//create texture from the surface
	b_bmpTexture = SDL_CreateTextureFromSurface(renderer, b_bmpSurface);
	if (nullptr == b_bmpTexture)
	{
		//print error in case of failure
		std::cout << "TEXTURE for bitmap: " << filename << " not loaded!"
			<< std::endl << SDL_GetError() << std::endl;
	}
	width = b_bmpSurface->w;
	height = b_bmpSurface->h;

}

Bitmap::~Bitmap()
{
	if (nullptr != b_bmpTexture)
	{
		SDL_DestroyTexture(b_bmpTexture);
		b_bmpTexture = nullptr;
	}

	if (nullptr != b_bmpSurface)
	{
		SDL_FreeSurface(b_bmpSurface);
		b_bmpSurface = nullptr;
	}
}

void Bitmap::Draw(int x, int y)
{
	//check that it isn't nullptr first
	if (nullptr == b_bmpTexture)
		return;
	//render bit map at stored coordinates
	SDL_Rect	destRect{ x, y, b_bmpSurface->w, b_bmpSurface->h };
	SDL_RenderCopy(b_renderer, b_bmpTexture, NULL, &destRect);
}


int Bitmap::getWidth()
{
	return b_bmpSurface->w;
}

int Bitmap::getHeight()
{
	return b_bmpSurface->h;
}
