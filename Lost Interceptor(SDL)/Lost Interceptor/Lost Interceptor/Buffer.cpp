#include "Buffer.h"

void Buffer::clear()
{
	SDL_RenderClear(m_renderer);
}

void Buffer::create()
{
	SDL_Init(SDL_INIT_VIDEO);
	//creates game window
	m_window = SDL_CreateWindow(
		"Lost Interceptor", // title
		250, // initial x
		50, // initial y
		1024, // width
		1024, // height
		0  // behavior flags
	);
	if (nullptr == m_window)
	{
		std::cout << "Window initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
		return;
	}


	m_renderer = SDL_CreateRenderer(
		m_window, //link 
		-1, //index rendering driver
		0 //renderer behavior flags
	);
	if (nullptr == m_renderer)
	{
		std::cout << "Renderer initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
		return;
	}

	m_backdrop = SDL_LoadBMP("assets/background.bmp"); //only works with .bmp files
	if (nullptr == m_backdrop)
	{
		std::cout << "Background initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
		return;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_backdrop);
	if (nullptr == m_texture)
	{
		std::cout << "Texture initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
		return;
	}

	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Buffer::draw()
{
	
	SDL_RenderCopy(m_renderer, m_texture, NULL, &view_1);
	SDL_RenderCopy(m_renderer, m_texture, NULL, &view_2);

	Y_offset += 2;

	if (Y_offset >= 1024)
	{
		Y_offset = 0;
	}
	
	SDL_UpdateWindowSurface(m_window);
	SDL_RenderPresent(m_renderer);
}

void Buffer::destroy()
{
	if (nullptr != m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_window = nullptr;
	}
	if (nullptr != m_backdrop)
	{
		SDL_FreeSurface(m_backdrop);
		m_renderer = nullptr;
	}
	if (nullptr != m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	if (nullptr != m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}
