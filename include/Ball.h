#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
   private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_radius;

   public:
	Ball(float px, float py, float radius);
	void draw(sf::RenderTarget &pTarget);
};
