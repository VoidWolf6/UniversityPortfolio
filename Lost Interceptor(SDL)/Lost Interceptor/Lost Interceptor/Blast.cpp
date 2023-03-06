#include "Blast.h"

Blast::Blast(int x, int y, bool fired, const std::string& filename, SDL_Renderer* renderer) : Entity(x, y, filename, renderer)
{
	orig = fired;
	xorigin = x;
	yorigin = y;
}

Blast::~Blast()
{
}

bool Blast::GetOrigin()
{
	return orig;
}
//here we go -- trigonometry.
void Blast::MoveTo(int xtarget, int ytarget)
{
	angle = atan2(ytarget - yorigin, xtarget - xorigin) * (180/M_PI);	
}

float Blast::getAngle()
{
	return angle;
}

SDL_Point* Blast::getPoint(int x, int y)
{
	return new SDL_Point{ x, y };
}

