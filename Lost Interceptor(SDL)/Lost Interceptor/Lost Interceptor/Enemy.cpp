#include "Enemy.h"

Enemy::Enemy(int x, int y, Types classif, const std::string& filename, SDL_Renderer* renderer) : Entity(x, y, filename, renderer)
{
	//gets the class, and assigns attributes based on that
	classified = classif;
	switch (classified)
	{
	case Swarmer:
		hitpoints = 2;
		break;
	case Normal:
		hitpoints = 6;
		break;
	case Bruiser:
		hitpoints = 20;
		break;
	case Boss:
		hitpoints = 120;
		break;
	default:
		break;
	}
	//changed when the enemy is active, and a way to disable/enable them easily
}

Enemy::~Enemy()
{
}

void Enemy::Fire(Player* target)
{
	//meant to fire at player based on location
}

void Enemy::Damage(int amount)
{
	hitpoints -= amount;
	if (hitpoints <= 0)
	{
		online = false;
	}
}

void Enemy::Activate(bool status)
{
	online = status;
}

bool Enemy::getStatus()
{
	return online;
}

Types Enemy::getClass()
{
	return classified;
}

int Enemy::getHealth()
{
	return hitpoints;
}
