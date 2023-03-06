#pragma once
#include "Entity.h"

class Player;

enum Types
{
	Swarmer,
	Normal,
	Bruiser,
	Boss, 
	Blank
};

class Enemy : public Entity
{
public:
	Enemy(int x, int y, Types classif, const std::string& filename, SDL_Renderer* renderer);
	~Enemy();
	void Fire(Player* target);
	void Damage(int amount);
	void Activate(bool status);
	bool getStatus();
	Types getClass();
	int getHealth();

private:
	Types classified;
	int hitpoints;
	bool online = false;
};
