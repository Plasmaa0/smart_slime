#include "Game.h"

Game::Game(unsigned int h, unsigned int w, Gamemode gm)
    : WINDOW_SIZE_H(h),
      WINDOW_SIZE_W(w),
      window(sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_W, WINDOW_SIZE_H),
                              "Smart Slimes",
                              sf::Style::Titlebar | sf::Style::Close)),
      gamemode(gm),
      mNet(WINDOW_SIZE_H * 0.3, WINDOW_SIZE_W * 0.02, WINDOW_SIZE_H * 0.7,
           WINDOW_SIZE_W * (0.5 - 0.01)),
      mPlayer1(0, h - (h + w) / 30, (h + w) / 30),
      mPlayer2(w - 2 * (h + w) / 30, h - (h + w) / 30, (h + w) / 30),
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
				printf("pizda\n");
				switch (event.key.code) {
					case sf::Keyboard::Q: {
						window.close();
						break;
					}

					case sf::Keyboard::W: {
						mPlayer1.setJumping(true);
						break;
					}
					case sf::Keyboard::A: {
						mPlayer1.setMovingLeft(true);
						break;
					}
					case sf::Keyboard::D: {
						mPlayer1.setMovingRight(true);
						break;
					}

					case sf::Keyboard::Left: {
						mPlayer2.setMovingLeft(true);
						break;
					}
					case sf::Keyboard::Right: {
						mPlayer2.setMovingRight(true);
						break;
					}
					case sf::Keyboard::Up: {
						mPlayer2.setJumping(true);
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

void Game::update(sf::Time deltatime)
{
	if (mPlayer1.m_position.y < WINDOW_SIZE_H - mPlayer1.m_radius - 10)
		mPlayer1.setJumping(false);
	if (mPlayer2.m_position.y < WINDOW_SIZE_H - mPlayer2.m_radius - 10)
		mPlayer2.setJumping(false);

	if (mBall.m_position.x < 0) {
		mBall.m_velocity.x *= -1.0f;
		mBall.m_position.x = 0;
	}
	if (mBall.m_position.y < 0) {
		mBall.m_velocity.y *= -1.0f;
		mBall.m_position.y = 0;
	}
	if (mBall.m_position.x + 2 * mBall.m_radius > WINDOW_SIZE_W) {
		mBall.m_velocity.x *= -1.0f;
		mBall.m_position.x = WINDOW_SIZE_W - 2 * mBall.m_radius;
	}
	if (mBall.m_position.y + 2 * mBall.m_radius > WINDOW_SIZE_H) {
		mBall.m_velocity.y *= -1.0f;
		mBall.m_position.y = WINDOW_SIZE_H - 2 * mBall.m_radius;
	}

	mBall.update(deltatime);
	mPlayer1.update(deltatime);
	mPlayer2.update(deltatime);

	sf::Vector2f playerCenter;
	auto ballCenter =
	    mBall.m_position + sf::Vector2f(mBall.m_radius, mBall.m_radius);
	if (ballCenter.x < WINDOW_SIZE_W / 2.0f) {
		playerCenter = mPlayer1.m_position +
		               sf::Vector2f(mPlayer1.m_radius, mPlayer1.m_radius);
	} else {
		playerCenter = mPlayer2.m_position +
		               sf::Vector2f(mPlayer2.m_radius, mPlayer2.m_radius);
	}
	if (length(ballCenter - playerCenter) <
	    mBall.m_radius + mPlayer2.m_radius) {
		mBall.m_velocity -=
		    2.0f * projectedOnto(mBall.m_velocity, playerCenter - ballCenter);
	}

	if (mPlayer1.m_position.y + mPlayer1.m_radius > WINDOW_SIZE_H)
		mPlayer1.m_position.y = WINDOW_SIZE_H - mPlayer1.m_radius;
	if (mPlayer1.m_position.x < 0) mPlayer1.m_position.x = 0;
	if (mPlayer1.m_position.x + 2 * mPlayer1.m_radius >
	    WINDOW_SIZE_W * (0.5 - 0.01))
		mPlayer1.m_position.x =
		    WINDOW_SIZE_W * (0.5 - 0.01) - 2 * mPlayer1.m_radius;

	if (mPlayer2.m_position.y + mPlayer2.m_radius > WINDOW_SIZE_H)
		mPlayer2.m_position.y = WINDOW_SIZE_H - mPlayer2.m_radius;
	if (mPlayer2.m_position.x + mPlayer2.m_radius * 2 > WINDOW_SIZE_W)
		mPlayer2.m_position.x = WINDOW_SIZE_W - 2 * mPlayer2.m_radius;
	if (mPlayer2.m_position.x < WINDOW_SIZE_W * (0.5 + 0.01))
		mPlayer2.m_position.x = WINDOW_SIZE_W * (0.5 + 0.01);
}

void Game::draw()
{
	window.clear(sf::Color(100, 100, 200));
	mNet.draw(window);
	mBall.draw(window);
	mPlayer1.draw(window);
	mPlayer2.draw(window);
	window.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timePerFrame = sf::seconds(1.0f / 30.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			ProcessEvents();
			update(timePerFrame);
		}
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
