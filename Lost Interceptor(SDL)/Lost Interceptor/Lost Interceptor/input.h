#pragma once
#include <SDL.h>

enum KEYS_PRESSED_LIST
{
	 KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_1, KEY_P, KEY_ENTER, SIZE_OF_KEYS_PRESSED_ENUM
};

class Input
{
public:
	Input();
	~Input();
	void GetInput();
	bool KeyIsPressed(KEYS_PRESSED_LIST key);

private:
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];
};
