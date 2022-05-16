#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Net.h"
#include "Player.h"

class Game
{
   private:
	/* Game modes:
	 * GM_SINGLE - left player controlled by WAD, right player controlled by NN
	 * GM_1PC2PLAYERS - both controlled by WAD and arrows,
	 * GM_ZEROPLAYER - both controlled by NN, this GM used for training
	 */
	enum Gamemode { GM_SINGLE, GM_1PC2PLAYERS, GM_ZEROPLAYER };

   private:
	unsigned int WINDOW_SIZE_H;
	unsigned int WINDOW_SIZE_W;
	sf::RenderWindow window;
	void ProcessEvents();
	void update();
	void draw();
	Gamemode gamemode;

	Net mNet;
	// Player mPlayer1;
	// Player mPlayer2;
	Ball mBall;
   public:
	Game(unsigned int h = 600U, unsigned int w = 800U, Gamemode gm = GM_SINGLE);
	void run();
	void test_application();
};
