#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Net : public Entity
{
   private:
	float height;
	float width;
	float TopY;
	float LeftX;

	sf::RectangleShape mRect;

   public:
	Net(float pHeight, float pWidth, float pLeftX, float pTopY);
	void draw(sf::RenderTarget &pTarget) const override;
};
