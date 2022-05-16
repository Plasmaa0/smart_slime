#include "Game.h"

Game::Game(unsigned int h, unsigned int w, Gamemode gm)
    : WINDOW_SIZE_H(h),
      WINDOW_SIZE_W(w),
      window(sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_W, WINDOW_SIZE_H),
                              "Smart Slimes",
                              sf::Style::Titlebar | sf::Style::Close)),
      gamemode(gm),
      mNet(WINDOW_SIZE_H * 0.3, WINDOW_SIZE_W * 0.01, WINDOW_SIZE_H * 0.7,
           WINDOW_SIZE_W * (0.5 - 0.01)),
      // mPlayer1(0, 0),
      // mPlayer2(0, 0),
      mBall(0, 0, (h + w) / 50)
{
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::KeyPressed: {
				switch (event.key.code) {
					case sf::Keyboard::Q: {
						window.close();
						break;
					}

					default:
						break;
				}
			}

			default:
				break;
		}
	}
}

void Game::update() {}

void Game::draw()
{
	window.clear(sf::Color(100, 100, 200));
	mNet.draw(window);
	mBall.draw(window);
	window.display();
}

void Game::run()
{
	while (window.isOpen()) {
		ProcessEvents();
		update();
		draw();
	}
}

void Game::test_application()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Test application");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
}
