#include <iostream>

#include "Game.h"
using namespace std;

int main()
{
	Game g(600U, 800U, Game::Gamemode::GM_1PC2PLAYERS);
	g.run();
	return 0;
}
