#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Ball : public Entity
{
   private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_radius;

   public:
	friend class Game;
	Ball(float px, float py, float radius);
	void draw(sf::RenderTarget &pTarget) const override;
	void update(sf::Time deltatime);
};
