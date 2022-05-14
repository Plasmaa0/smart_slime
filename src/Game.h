#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	int WINDOW_SIZE_H;
	int WINDOW_SIZE_W;
	sf::RenderWindow window;
	bool Running();
	void ProcessEvents();

public:
	Game(int h = 600, int w = 800);
	void run();
	void test_application();
};