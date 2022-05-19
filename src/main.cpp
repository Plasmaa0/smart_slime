#include <iostream>

#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	Game::Gamemode gamemode;
	cout << "choose gamemode: " << endl
	     << "0) 0 player" << endl
	     << "1) 1 player" << endl
	     << "2) 2 players" << endl
	     << "choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
		case 0:
			gamemode = Game::Gamemode::GM_ZEROPLAYER;
			break;
		case 1:
			cout << "not implemented" << endl;
			abort();
			gamemode = Game::Gamemode::GM_SINGLE;
			break;
		case 2:
			gamemode = Game::Gamemode::GM_1PC2PLAYERS;
			break;
		default:
			cout << "unexpected input" << endl;
			abort();
			break;
	}
	Game g(600U, 800U, gamemode);
	g.run();
	return 0;
}
