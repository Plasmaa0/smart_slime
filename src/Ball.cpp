#include "Ball.h"

Ball::Ball(float px, float py, float radius)
    : m_position(px, py),
      m_velocity(0, 0),
      m_acceleration(0, 0),
      m_radius(radius)
{
}

void Ball::draw(sf::RenderTarget &pTarget) const
{
	sf::CircleShape circle;
	circle.setRadius(m_radius);
	circle.setPosition(m_position);
	pTarget.draw(circle);
}

void Ball::update(sf::Time deltatime)
{
	m_velocity +=
	    (m_acceleration + sf::Vector2f(0, 600)) * deltatime.asSeconds();
	m_position += m_velocity * deltatime.asSeconds();
}
