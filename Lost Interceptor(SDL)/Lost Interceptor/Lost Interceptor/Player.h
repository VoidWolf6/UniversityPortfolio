#pragma once
#include "Entity.h"
#include "Time.h"
#include <string>

class Player : public Entity
{
public:
	Player(int x, int y, int m_lives, const std::string& filename, SDL_Renderer* renderer);
	~Player();
	void descLives();
	int getLives(), getInventory(), getDamage();
	void incScore(int amount);
	void explode();
	void gather();
	std::string getAmmo();
	void changeAmmo(int option);
	void Evasion(int duration);
	bool Avoiding();
	int final();


private:
	int lives{ 2 };
	int score{ 0 };
	int bomb_count{ 2 };
	int plasma_count{ 0 };
	int player_damage{ 0 };
	bool avoid = false;
};

