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
      mBall(0, 0, (h + w) / 50),
      scores{0, 0},
      FPS{70},
      paused{false}
{
	if (gamemode != GM_1PC2PLAYERS) brains = new BrainContainer(1000);
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
				// printf("pizda\n");
				switch (event.key.code) {
					case sf::Keyboard::Q: {
						window.close();
						break;
					}
					case sf::Keyboard::R: {
						ResetBall();
						scores = {0, 0};
						break;
					}
					case sf::Keyboard::Space: {
						paused = !paused;
						break;
					}

					case sf::Keyboard::W: {
						mPlayer1.setJumping(true and not paused);
						break;
					}
					case sf::Keyboard::A: {
						mPlayer1.setMovingLeft(true and not paused);
						break;
					}
					case sf::Keyboard::D: {
						mPlayer1.setMovingRight(true and not paused);
						break;
					}

					case sf::Keyboard::Left: {
						mPlayer2.setMovingLeft(true and not paused);
						break;
					}
					case sf::Keyboard::Right: {
						mPlayer2.setMovingRight(true and not paused);
						break;
					}
					case sf::Keyboard::Up: {
						mPlayer2.setJumping(true and not paused);
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
	if (not paused) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			mPlayer1.setJumping(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			mPlayer1.setMovingLeft(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			mPlayer1.setMovingRight(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			mPlayer2.setMovingLeft(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			mPlayer2.setMovingRight(true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			mPlayer2.setJumping(true);
		}
	}
}

void Game::update(sf::Time deltatime)
{
	if (gamemode == GM_ZEROPLAYER) {
		mPlayer1.setMovingLeft(false);
		mPlayer1.setMovingRight(false);
		mPlayer1.setJumping(false);
		mPlayer2.setMovingLeft(false);
		mPlayer2.setMovingRight(false);
		mPlayer2.setJumping(false);
		int desicionleft = brains->left()(
		    mPlayer1.m_position.x, mPlayer1.m_position.y, mPlayer1.m_velocity.x,
		    mPlayer1.m_velocity.y, mBall.m_position.x, mBall.m_position.y,
		    mBall.m_velocity.x, mBall.m_velocity.y);
		int desicionright = brains->right()(
		    WINDOW_SIZE_W - mPlayer2.m_position.x, mPlayer2.m_position.y,
		    -mPlayer2.m_velocity.x, mPlayer2.m_velocity.y,
		    WINDOW_SIZE_W - mBall.m_position.x, mBall.m_position.y,
		    -mBall.m_velocity.x, mBall.m_velocity.y);
		if (desicionleft == 1)
			mPlayer1.setMovingLeft(true);
		else if (desicionleft == 2)
			mPlayer1.setMovingRight(true);
		else if (desicionleft == 3)
			mPlayer1.setJumping(true);

		if (desicionright == 1)
			mPlayer2.setMovingRight(true);
		else if (desicionright == 2)
			mPlayer2.setMovingLeft(true);
		else if (desicionright == 3)
			mPlayer2.setJumping(true);
	}

	ProcessPhysicsBefore();

	mBall.update(deltatime);
	mPlayer1.update(deltatime);
	mPlayer2.update(deltatime);

	ProcessPhysicsAfter();

	// ProcessWin();
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
	sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			ProcessEvents();
			if (not paused) {
				if (gamemode == GM_ZEROPLAYER and
				    (not sf::Keyboard::isKeyPressed(sf::Keyboard::P))) {
					for (unsigned int i = 0; i < 1000; i++)
						update(timePerFrame);
				} else {
					update(timePerFrame);
				}
			}
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

void Game::ProcessPhysicsBefore()
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
}

// if anyone won? / if is was left?
std::pair<bool, bool> Game::CheckWin()
{
	if (mBall.m_position.y + 2 * mBall.m_radius > WINDOW_SIZE_H) {
		// mBall.m_velocity.y *= -1.0f;
		// mBall.m_position.y = WINDOW_SIZE_H - 2 * mBall.m_radius;
		bool LeftWon = (mBall.m_position.x > WINDOW_SIZE_W / 2.0f);
		std::cout << "endgame" << std::endl;
		// Throw ball from the top
		ResetBall();

		return {true, LeftWon};
		// if (mBall.m_position.x <= WINDOW_SIZE_W / 2)  // left lose
		// 	return {true, false};
		// else  // left win
		// 	return {true, true};
	}
	return {false, false};
}

void Game::ProcessWin()
{
	std::pair<bool, bool> WinResults = CheckWin();
	if (WinResults.first) {
		if (gamemode == GM_ZEROPLAYER) brains->setResult(WinResults.second);
		if (WinResults.second)  // left
			scores.first++;
		else  // right
			scores.second++;
		using std::to_string;
		window.setTitle(to_string(scores.first) + ", " +
		                to_string(scores.second));
	}
}

void Game::ProcessPhysicsAfter()
{
	sf::Vector2f playerCenter;
	sf::Vector2f ballCenter =
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
		float penetration_depth = length(ballCenter - playerCenter) -
		                          mBall.m_radius - mPlayer2.m_radius;
		mBall.m_velocity -=
		    2.0f * projectedOnto(mBall.m_velocity, playerCenter - ballCenter);
		mBall.m_position += (ballCenter - playerCenter).normalized() *
		                    penetration_depth * (-1.5f);
		// std::cout << "penetration_depth: " << penetration_depth << std::endl;
	}

	if (WINDOW_SIZE_W * (0.5 - 0.01) < ballCenter.x + mBall.m_radius and
	    ballCenter.x - mBall.m_radius < WINDOW_SIZE_W * (0.5 + 0.01) and
	    ballCenter.y + mBall.m_radius > WINDOW_SIZE_H * 0.7) {
		mBall.m_velocity.x *= -1.0f;
		if (ballCenter.y < WINDOW_SIZE_H * 0.75) {
			mBall.m_velocity.y *= -1.0f;
		}
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

void Game::ResetBall()
{
	mBall.m_position = sf::Vector2f(0, 0);
	mBall.m_velocity = sf::Vector2f(100, 0);
	mBall.m_acceleration = sf::Vector2f(0, 0);
}
