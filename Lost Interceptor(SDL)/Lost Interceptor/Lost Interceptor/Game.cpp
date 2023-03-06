#include "Game.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);
	//creates game window
	m_window = SDL_CreateWindow(
		"Lost Interceptor", // title
		250, // initial x
		50, // initial y
		1024, // width
		1024, // height
		0  // behavior flags
	);
	if (nullptr == m_window)
	{
		std::cout << "Window initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		return;
	}


	m_renderer = SDL_CreateRenderer(
		m_window, //link 
		-1, //index rendering driver
		0 //renderer behavior flags
	);
	if (nullptr == m_renderer)
	{
		std::cout << "Renderer initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		return;
	}

	m_backdrop = SDL_LoadBMP("assets/background.bmp"); //only works with .bmp files, sets up background
	if (nullptr == m_backdrop)
	{
		std::cout << "Background initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		return;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_backdrop);
	if (nullptr == m_texture)
	{
		std::cout << "Texture initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		return;
	}

	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	//item setup

	power_ups.push_back(new Boost(1000, 800, PlasmaMissile, "Assets/PlasmaMissile.bmp", m_renderer));
	
		
	p_audio = new Audio;
	Player_One = new Player(500, 800, 2, PlayerImage, m_renderer);
	
	bossed = new Enemy{ 400, 52, Boss, "Assets/Boss.bmp", m_renderer };

	for (int i = 0; i < 6; i++)
	{
		active_enemies.push_back(new Enemy((i * 110) + view_1->x + 40, 10, Swarmer, "Assets/Swarmer.bmp", m_renderer));
	}

	for (int i = 0; i < 4; i++)
	{
		active_enemies.push_back(new Enemy(view_1->x + view_1->w - ((i + 1) * 110), 10, Normal, "Assets/Normal.bmp", m_renderer));
	}

	for (int i = 0; i < 2; i++)
	{
		active_enemies.push_back(new Enemy((i * 110) + view_1->x + 240, 10, Bruiser, "Assets/Bruiser.bmp", m_renderer));
	}
	active_enemies.push_back(new Enemy((110) + view_1->x + 240, 10, Blank, "Assets/Bruiser.bmp", m_renderer));//used to prevent a crash

	p_audio->play(0);

	/*notes:
	* configuration manager linux (it is possible) wsl & gcc 
	* */
}

Game::~Game()
{
	//destroy items in reverse order of creation
	active_shots.clear();
	active_rounds.clear();
	active_enemies.clear();
	if (bossed != nullptr)
	{
		delete bossed;
		bossed = nullptr;
	}
	if (Player_One != nullptr)
	{
		delete Player_One;
		Player_One = nullptr;
	}
	p_audio->~Audio();	
	power_ups.clear();
	if (f_timer != nullptr)
	{
		delete f_timer;
		f_timer = nullptr;
	}
	if (m_timer != nullptr)
	{
		delete m_timer;
		m_timer = nullptr;
	}
	if (nullptr != m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_window = nullptr;
	}
	if (nullptr != m_backdrop)
	{
		SDL_FreeSurface(m_backdrop);
		m_renderer = nullptr;
	}
	if (nullptr != m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	if (nullptr != m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	
	SDL_Quit();
}

void Game::ClearAndPresent()
{
	//clears existing
	SDL_RenderClear(m_renderer);


	//will have to deal with the blip on repeat
	Y_offset += 2;
	view_1->y += 2;
	view_2->y += 2;

	if (Y_offset >= (view_2->h - background_start))
	{
		Y_offset = 0;
		view_1->y = background_start;
		view_2->y = (-view_1->h + background_start);
	}

	

	SDL_RenderCopy(m_renderer, m_texture, NULL, view_1);
	SDL_RenderCopy(m_renderer, m_texture, NULL, view_2);


	for (int i = 0; i < active_shots.size(); i++)//player shots
	{
		active_shots[i]->IncYpos(-2 * moveSpeed);
		if (active_shots[i]->GetYpos() < 0 || active_shots[i]->GetXpos() < view_1->x || active_shots[i]->GetXpos() > (view_1->x + view_1->w)) //out of bounds
		{
			active_shots.erase(active_shots.begin() + i);
		}
	}

	for (int i = 0; i < active_rounds.size(); i++)//enemy shots
	{
		active_rounds[i]->IncXpos(cos(active_rounds[i]->getAngle() * (M_PI / 180)));
		active_rounds[i]->IncYpos(sin(active_rounds[i]->getAngle() * (M_PI / 180)));

		if (active_rounds[i]->CheckEntityCollision(active_rounds[i]->ReturnCollider(), Player_One->ReturnCollider()) && !Player_One->Avoiding()) //if colliding with player
		{
			Player_One->descLives();
			active_rounds.erase(active_rounds.begin() + i);
		}

		if (active_rounds[i]->GetYpos() < 1040 || active_rounds[i]->GetXpos() < view_1->x || active_rounds[i]->GetXpos() > (view_1->x + view_1->w)) //out of bounds
		{
			active_rounds.erase(active_rounds.begin() + i);
		}
	}


	for (int i = 0; i < active_enemies.size(); i++) //enemies colliding with player bullets
	{
		if (active_enemies[i]->getStatus())
		{
			active_enemies[i]->IncYpos(moveSpeed * 0.5f);
			for (int n = 0; n < active_shots.size(); n++)
			{
				if (active_enemies[i]->CheckEntityCollision(active_shots[n]->ReturnCollider(), active_enemies[i]->ReturnCollider()))//if colliding with player shot
				{
					active_enemies[i]->Damage(Player_One->getDamage());
					if (!active_enemies[i]->getStatus())
					{
						active_shots.erase(active_shots.begin() + n);	
						switch (active_enemies[i]->getClass())
						{
							case Swarmer:
								Player_One->incScore(50);
								break;
							case Normal:
								Player_One->incScore(100);
								break;
							case Bruiser:
								Player_One->incScore(200);
								break;
							case Boss:
								Player_One->incScore(5000);
								break;
							default:
								break;
						}
					}	
					active_enemies.erase(active_enemies.begin() + i);
				}
				if (active_enemies[i]->CheckEntityCollision(Player_One->ReturnCollider(), active_enemies[i]->ReturnCollider()) && !Player_One->Avoiding())//if colliding directly with player
				{
					Player_One->descLives();
				}
			}
		}		
	}
//Why do only the player and walls have collision? They are set up properly. 
	


	for (int i = 0; i < power_ups.size(); i++)
	{
		if (power_ups[i]->getStatus())
		{
			if (power_ups[i]->CheckEntityCollision(Player_One->ReturnCollider(), power_ups[i]->ReturnCollider()))
			{
				power_ups[i]->Grant(Player_One);
				power_ups[i]->Activate(false);
			}
		}		
	}
	//e.g.  active_rounds.erase(active_rounds.begin() + 2);
	//draw items to the window
	Player_One->Draw();


	for (int i = 0; i < active_shots.size(); i++)
	{		
		active_shots[i]->Draw();
	}

	for (int i = 0; i < active_rounds.size(); i++)
	{
		active_rounds[i]->Draw();
	}

	for (int i = 0; i < active_enemies.size(); i++)
	{
		if (active_enemies[i]->getStatus())
		{
			active_enemies[i]->Draw();
		}
	}
	
	for (int i = 0; i < power_ups.size(); i++)
	{
		if (power_ups[i]->getStatus())
		{
			power_ups[i]->Draw();
		}		
	}

	if (boss_online)//only done when the boss is active
	{
		bossed->IncYpos(0.5 *  moveSpeed);
		if (bossed->GetYpos() >= 850)
		{
			bossed->SetYpos(20);
		}
		bossed->Draw();


		for (int i = 0; i < active_shots.size(); i++)
		{
			if (active_shots[i]->CheckEntityCollision(active_shots[i]->ReturnCollider(), bossed->ReturnCollider()))
			{
				bossed->Damage(Player_One->getDamage());
			}
		}

		if (bossed->getHealth() <= 0)
		{
			Player_One->incScore(5000);
			boss_online = false;
			
		}
	}


	//present everything to the player
	SDL_RenderPresent(m_renderer);
}

void Game::Run()
{
	p_input = new Input();
	//or symbol is shift, right alt, hash key 

	//use a do while loop for input
	if (nullptr == m_renderer || nullptr == p_input)
		return;
	do
	{
		//gets input from player, and executes appropriate code
		p_input->GetInput();
		//there might be a better way to do this, but this has to do
		if (p_input->KeyIsPressed(KEY_LEFT) && Player_One->GetXpos() >= view_1->x)
		{
			Player_One->IncXpos(-moveSpeed);
		}
		if (p_input->KeyIsPressed(KEY_RIGHT) && Player_One->GetXpos() <= (view_1->x + view_1->w - Player_One->ReturnCollider()->h))
		{
			Player_One->IncXpos(moveSpeed);
		}
		if (p_input->KeyIsPressed(KEY_UP) && Player_One->GetYpos() >= 4)
		{
			Player_One->IncYpos(-moveSpeed);
		}
		if (p_input->KeyIsPressed(KEY_DOWN) && Player_One->GetYpos() <= (1092 - Player_One->ReturnCollider()->h))
		{
			Player_One->IncYpos(moveSpeed);
		}
		if (p_input->KeyIsPressed(KEY_P) && canFire)
		{
			active_shots.push_back(new Blast(Player_One->GetXpos() + 34, Player_One->GetYpos(), true, Player_One->getAmmo(), m_renderer));
			canFire = false;
		}
		if (p_input->KeyIsPressed(KEY_ENTER) && Player_One->getInventory() > 0)
		{
			for (int i = 0; i < active_enemies.size(); i++)
			{
				if (active_enemies[i]->getStatus())
				{
					active_enemies.erase(active_enemies.begin() + i);
					Player_One->explode();
				}
			}
		}

		
		if (m_timer) m_timer->update_timer();
		f_timer->update_timer();
		s_activated += m_timer->delta_time();
		if (s_activated >= 5.0f)
		{
			for (int i = 0; i < active_enemies.size(); i++)
			{
				if (active_enemies[i]->getClass() == Swarmer)
				{
					active_enemies[i]->Activate(true);
				}				
			}
			swarm_online = true;
		}


		if (s_activated >= 15.0f)
		{
			for (int i = 0; i < active_enemies.size(); i++)
			{
				if (active_enemies[i]->getClass() == Normal)
				{
					active_enemies[i]->Activate(true);
				}
			}
			norm_online = true;
		}


		if (s_activated >= 25.0f)
		{
			for (int i = 0; i < active_enemies.size(); i++)
			{
				if (active_enemies[i]->getClass() == Bruiser)
				{
					active_enemies[i]->Activate(true);
				}
			}
			bruise_online = true;
		}

		if (s_activated >= 45.0f)
		{
			boss_online = true;
		}

		//e_firing += m_timer->delta_time();
		//if ((e_firing % 8) == 0 && swarm_online)
		//{
		//	int select = rand() % active_enemies.size(); //selects a random active enemy to fire from
		//	active_rounds.push_back(new Blast(active_enemies[select]->GetXpos() + 34, active_enemies[select]->GetYpos() + active_enemies[select]->ReturnCollider()->h, true, "Assets/PlayerShot.bmp", m_renderer));
		//	active_rounds.back()->MoveTo(Player_One->GetXpos(), Player_One->GetYpos());
		//}

		//this causes the shots to fire at intervals
		staggered += f_timer->delta_time();
		if (staggered >= 0.5f)
		{
			staggered = 0.0f;
			canFire = true;
		}

		ClearAndPresent();
		//potential delays 
		SDL_Delay(50);
	} while (!p_input->KeyIsPressed(KEY_1) && Player_One->getLives() >= 0 && bossed->getHealth() > 0);
	//program runs while this key is not pressed


	std::cout << "Final score: " << Player_One->final() << std::endl;

	std::ofstream file_stream;

	file_stream.open("scores.txt", std::ios_base::app);
	file_stream << (int)(Player_One->final()) << " \n\n" ;
	file_stream.close();
}
