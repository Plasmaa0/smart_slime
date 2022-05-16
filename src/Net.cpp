#include "Net.h"

Net::Net(float pHeight, float pWidth, float pTopY, float pLeftX)
    : height(pHeight),
      width(pWidth),
      TopY(pTopY),
      LeftX(pLeftX),
      mRect(sf::Vector2f(width, height))
{
	mRect.setPosition(sf::Vector2f(LeftX, TopY));
}

void Net::draw(sf::RenderTarget &pTarget) const
{
	pTarget.draw(mRect);
}
