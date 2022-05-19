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

#ifdef COLLISION_HELPERS
	sf::RectangleShape boundingBox(sf::Vector2f(m_radius * 2, m_radius * 2));
	boundingBox.setPosition(m_position);
	boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
	boundingBox.setOutlineColor(sf::Color(0, 255, 0));
	boundingBox.setOutlineThickness(5);

	sf::CircleShape center;
	center.setRadius(5);
	center.setPosition(m_position +
	                   sf::Vector2f(m_radius - 2.5f, m_radius - 2.5f));
	center.setFillColor(sf::Color(0, 0, 255));

	pTarget.draw(boundingBox);
	pTarget.draw(center);

	sf::Vertex vel[] = {
	    sf::Vertex(m_position + sf::Vector2f(m_radius - 2.5f, m_radius - 2.5f)),
	    sf::Vertex(m_position + sf::Vector2f(m_radius - 2.5f, m_radius - 2.5f) +
	               m_velocity)};
	pTarget.draw(vel, 2, sf::Lines);
#endif
}

void Ball::update(sf::Time deltatime)
{
	m_velocity +=
	    (m_acceleration + sf::Vector2f(0, 600)) * deltatime.asSeconds();
	m_position += m_velocity * deltatime.asSeconds();
}
