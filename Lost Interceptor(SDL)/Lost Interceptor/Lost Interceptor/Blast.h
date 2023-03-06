#pragma once
#include "Entity.h"

class Blast : public Entity
{
public:
	Blast(int x, int y, bool fired, const std::string& filename, SDL_Renderer* renderer);
	~Blast();
	bool GetOrigin(); //detects where the bullet came from, because the class is used by players and enemies
	void MoveTo(int xtarget, int ytarget);//used for tracking movement -- returns the angle
	float getAngle();
	SDL_Point* getPoint(int x, int y);

private:
	bool orig; //true if the player fired it
	int xorigin, yorigin;
	float angle;
	
};
