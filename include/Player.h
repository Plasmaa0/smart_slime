#pragma once

class Player
{
   private:
	sf::Vector2f position;

   public:
	Player(float pX, float pY);
	void draw(sf::RenderTarget &pTarget);
};
