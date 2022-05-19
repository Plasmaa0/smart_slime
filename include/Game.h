#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Ball.h"
#include "BrainContainer.h"
#include "Net.h"
#include "Player.h"
#include "Utils.h"

class Game
{
   public:
	/* Game modes:
	 * GM_SINGLE - left player controlled by WAD, right player controlled by NN
	 * GM_1PC2PLAYERS - both controlled by WAD and arrows,
	 * GM_ZEROPLAYER - both controlled by NN, this GM used for training
	 */
	enum Gamemode { GM_ZEROPLAYER, GM_SINGLE, GM_1PC2PLAYERS };

   private:
	unsigned int WINDOW_SIZE_H;
	unsigned int WINDOW_SIZE_W;
	sf::RenderWindow window;
	void ProcessPhysicsAfter();
	void ProcessPhysicsBefore();
	std::pair<bool, bool> ProcessWin();  // if anyone won? / if is was left?
	void ProcessEvents();
	void update(sf::Time deltatime);
	void draw();
	Gamemode gamemode;

	Net mNet;
	Player mPlayer1;
	Player mPlayer2;
	Ball mBall;

	BrainContainer *brains;
	std::pair<int, int> scores;
	uint8_t FPS;

   public:
	Game(unsigned int h = 600U, unsigned int w = 800U, Gamemode gm = GM_SINGLE);
	void run();
	void test_application();
};
