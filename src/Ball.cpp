#include "Ball.h"

Ball::Ball(float px, float py, float radius)
    : m_position(px, py), m_velocity(0, 0), m_radius(radius)
{
}

void Ball::draw(sf::RenderTarget &pTarget)
{
	sf::CircleShape circle;
	circle.setRadius(m_radius);
	circle.setPosition(m_position);
	pTarget.draw(circle);
}
