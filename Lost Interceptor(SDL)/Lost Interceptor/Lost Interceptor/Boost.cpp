#include "Boost.h"

Boost::Boost(int x, int y, Powers type, const std::string& filename, SDL_Renderer* renderer) : Entity (x, y,filename, renderer)
{
	b_type = type;
}

Boost::~Boost()
{
}

void Boost::Grant(Player* target)
{
	//	//if the power up is colliding with a player
	//	//change a modifier based on the type that it is -- or run a function dedicated to it? 
		switch (b_type)
		{
		case SideMissiles:
			break;
		case PlasmaMissile:
			if (target->getDamage() == 4)
			{
				target->changeAmmo(1);
			}
			else if (target->getDamage() == 8)
			{
				target->changeAmmo(2);
			}			
			break;
		case Bomb:
			target->gather();
			break;
		case DisplacementField:
			target->Evasion(8);
			break;
		default:
			break;
		}
	
}

void Boost::Activate(bool status)
{
	active = status;
}

bool Boost::getStatus()
{
	return active;
}

	/*switch (b_type)
	{
	case SideMissiles:
		return "Assets/SideMissiles.bmp";
		break;
	case PlasmaMissile:
		return "Assets/PlasmaMissile.bmp";
		break;
	case Bomb:
		return "Assets/Bomb.bmp";
		break;
	case DisplacementField:
		return "Assets/DisplacementOn.bmp";
		break;
	default:
		break;
	}*/

