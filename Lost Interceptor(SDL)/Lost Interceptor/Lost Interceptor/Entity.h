#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Bitmap.h"

class Entity
{
public:
	Entity(int x, int y, const std::string& filename, SDL_Renderer* renderer);
	~Entity();
	void Draw();
	void Destroy();
	//position code
	void SetXpos(float x), SetYpos(float y), IncXpos(float amount), IncYpos(float amount);
	int GetXpos(), GetYpos();
	//collision code
	SDL_Rect* ReturnCollider();
	bool CheckEntityCollision(SDL_Rect* a, SDL_Rect* b);


protected:
	int m_Xpos{ 0 };
	int m_Ypos{ 0 };

	Bitmap* e_bitmap;
	SDL_Rect* e_collider;
	//it goes x coordinate of top left, y coordinate of top left, width of rectangle, height of rectangle
};
