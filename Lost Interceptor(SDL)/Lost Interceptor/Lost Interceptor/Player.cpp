#include "Player.h"

Player::Player(int x, int y, int m_lives, const std::string& filename, SDL_Renderer* renderer) : Entity (x, y, filename, renderer)
{
	lives = m_lives;
}

Player::~Player()
{
}

void Player::descLives()
{
	lives--;
	changeAmmo(0);
	Evasion(4);
}

std::string Player::getAmmo()
{
	switch (plasma_count)
	{
	case 0:
		player_damage = 4;
		return "Assets/PlayerShot.bmp";
	case 1:
		player_damage = 8;
		return "Assets/PlasmaMarkI.bmp";
	case 2:
		player_damage = 10;
		return "Assets/PlasmaMarkII.bmp";
	default:
		break;
	}
}

void Player::changeAmmo(int option)
{
	plasma_count = option;
}

void Player::Evasion(int duration)
{
	avoid = true;
	float field = 0.0f;
	Time* d_timer = new Time();
	d_timer->update_timer();
	field += d_timer->delta_time();
	if (field > duration)
	{
		field = 0.0f;
		avoid = false;
	}
}

bool Player::Avoiding()
{
	return avoid;
}

int Player::final()
{
	return score;
}

int Player::getLives()
{
	return lives;
}

int Player::getInventory()
{
	return bomb_count;
}

int Player::getDamage()
{
	return player_damage;
}

void Player::incScore(int amount)
{
	score += amount;
}

void Player::explode()
{
	bomb_count--;
}

void Player::gather()
{
	bomb_count++;
}