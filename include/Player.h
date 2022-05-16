#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Player : public Entity
{
   private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_radius;
	bool movingLeft;
	bool movingRight;
	bool jumping;

   public:
	friend class Game;
	Player(float pX, float pY, float radius);
	void draw(sf::RenderTarget &pTarget) const override;
	void update(sf::Time deltatime);
	void setMovingLeft(const bool state);
	void setMovingRight(const bool state);
	void setJumping(const bool state);
};
