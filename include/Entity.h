#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
private:
	
public:
	Entity();
	virtual void draw(sf::RenderTarget &pTarget) const = 0;
};
