#include "Game.h"
#undef main

int main(int argc, char* argv[])
{
	Game* game = new Game; //creates new object

	if (nullptr == game)
		return -1; //if something is wrong, bail out

	game->Run(); //update and draw everything

	delete game;
	game = nullptr; //clean up

	return 0; //exit
}
