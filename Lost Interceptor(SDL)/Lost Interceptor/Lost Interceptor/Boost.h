#pragma once
#include "Entity.h"
#include "Player.h"

enum Powers
{
	SideMissiles,
	PlasmaMissile,
	Bomb,
	DisplacementField
};

class Boost : public Entity
{
public:
	Boost(int x, int y, Powers type, const std::string& filename, SDL_Renderer* renderer);
	~Boost();
	void Grant(Player* target);
	void Activate(bool status);
	bool getStatus();

private:
	Powers b_type;
	bool active = true; 
};

