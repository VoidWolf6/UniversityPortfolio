#include "input.h"

Input::Input()
{
	for (int i = 0; i < SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		m_keysPressed[i] = false;
	}

}

Input::~Input()
{
}

void Input::GetInput()
{
	static SDL_Event event;

	while (0 != SDL_PollEvent(&event))
	{
		SDL_Keycode keyPressed = event.key.keysym.sym;
		switch (event.type) 
		{
			case SDL_KEYDOWN:
				if (keyPressed == SDLK_RIGHT)//move right
					m_keysPressed[KEY_RIGHT] = true;
				if (keyPressed == SDLK_LEFT)//move left
					m_keysPressed[KEY_LEFT] = true;
				if (keyPressed == SDLK_DOWN)//move down
					m_keysPressed[KEY_DOWN] = true;
				if (keyPressed == SDLK_UP)//move up
					m_keysPressed[KEY_UP] = true;
				if (keyPressed == SDLK_1)//exit
					m_keysPressed[KEY_1] = true;
				if (keyPressed == SDLK_p)//fire
					m_keysPressed[KEY_P] = true;
				if (keyPressed == SDLK_RETURN)//use bomb
					m_keysPressed[KEY_ENTER] = true;
				break;

			case SDL_KEYUP:
				if (keyPressed == SDLK_RIGHT)
					m_keysPressed[KEY_RIGHT] = false;
				if (keyPressed == SDLK_LEFT)
					m_keysPressed[KEY_LEFT] = false;
				if (keyPressed == SDLK_DOWN)
					m_keysPressed[KEY_DOWN] = false;
				if (keyPressed == SDLK_UP)
					m_keysPressed[KEY_UP] = false;
				if (keyPressed == SDLK_1)
					m_keysPressed[KEY_1] = false;
				if (keyPressed == SDLK_p)
					m_keysPressed[KEY_P] = false;
				if (keyPressed == SDLK_RETURN)
					m_keysPressed[KEY_ENTER] = false;
				break;

			default:
				break;
		}
		
	}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}
