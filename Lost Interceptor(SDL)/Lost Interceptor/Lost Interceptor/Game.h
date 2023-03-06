#pragma once
#include <SDL.h>
#include <vector> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include "Audio.h"
#include "input.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Boost.h"
#include "Bitmap.h"
#include "Blast.h"
#include "Time.h"

using namespace std;

struct SDL_Window;
struct SDL_Renderer; 

class Game
{
public:
	Game();
	~Game();
	void ClearAndPresent();
	void Run();

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	SDL_Surface* m_backdrop{ nullptr };
	SDL_Texture* m_texture{ nullptr };
	//I have tried to use double buffering, but objects/bitmaps did not work. The reason for the cutting was the relatively long delay. 
	
	int Y_offset = 0;
	int background_start = 52;
	int moveSpeed = 4;
	bool canFire = true;
	float s_activated, staggered = 0.0f;
	bool swarm_online, norm_online, bruise_online, boss_online = false;
	int e_firing = 0;
	//game variables


	SDL_Rect* view_1 = new SDL_Rect{ 256, background_start, 1024, 1024 };
	SDL_Rect* view_2 = new SDL_Rect{ 256, (-view_1->h) + background_start, 1024, 1024 };
	//These set up the backdrops.

	
	//set up pools for bullets, boosts, and enemies. Bullets fire at 2-4 second intervals. 
	std::vector<Boost*> power_ups;
	std::vector<Enemy*> active_enemies;
	std::vector<Blast*> active_shots, active_rounds;
	Enemy* bossed;
	

	//objects to be set up in the constructor.
	Time* m_timer = new Time();
	Time* f_timer = new Time();
	Time* b_timer = new Time();
	Audio* p_audio;
	Input* p_input;
	Player* Player_One{ nullptr };
	std::string PlayerImage = "Assets/Player(Standard).bmp";
};

