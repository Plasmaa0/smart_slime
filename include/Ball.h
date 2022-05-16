#pragma once

class Ball
{
   private:
	sf::Vector2f position;
	sf::Vector2f velocity;

   public:
	Ball(float px, float py);
	void draw(sf::RenderTarget &pTarget);
};
