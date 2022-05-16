#pragma once
#include <SFML/Graphics.hpp>

class Net
{
private:
    float height;
    float width;
    float TopY;
    float LeftX;

    sf::RectangleShape mRect;
public:
    Net(float pHeight, float pWidth, float pLeftX, float pTopY);
    void draw(sf::RenderTarget &pTarget) const;
};
