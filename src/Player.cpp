#include "Player.h"

Player::Player(float pX, float pY, float radius)
    : m_position(pX, pY),
      m_velocity(0, 0),
      m_acceleration(0, 0),
      m_radius(radius),
      movingLeft(false),
      movingRight(false),
      jumping(false)
{
}

void Player::draw(sf::RenderTarget &pTarget) const
{
	sf::CircleShape circle;
	circle.setFillColor(sf::Color(255, 0, 0));
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

void Player::update(sf::Time deltatime)
{
	if (movingLeft) {
		movingLeft = false;
		// printf("movingLeft\n");
		m_velocity.x = -m_radius * 10;
	}
	if (movingRight) {
		movingRight = false;
		// printf("movingRight\n");
		m_velocity.x = m_radius * 10;
	}
	if (jumping) {
		jumping = false;
		// printf("jumping\n");
		m_velocity.y = -m_radius * 22;
	}
	// m_acceleration.y += 10;
	// if (m_acceleration.y > 1000) m_acceleration.y = 1000;
	auto summ_acceleration = m_acceleration + sf::Vector2f(0, 3000);
	m_velocity += summ_acceleration * deltatime.asSeconds();
	// printf("%f, %f\n", summ_acceleration.x, summ_acceleration.y);
	m_position += m_velocity * deltatime.asSeconds();
	m_acceleration.x *= 0.0f;
	m_velocity.x *= 0.9f;
}

void Player::setMovingLeft(const bool state)
{
	movingLeft = state;
}
void Player::setMovingRight(const bool state)
{
	movingRight = state;
}
void Player::setJumping(const bool state)
{
	jumping = state;
}
