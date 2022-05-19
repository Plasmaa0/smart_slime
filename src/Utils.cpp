#include "Utils.h"

using namespace std;

float dot(const sf::Vector2f &vector1, const sf::Vector2f &vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

float lengthSq(const sf::Vector2f &vector)
{
	return dot(vector, vector);
}

float length(const sf::Vector2f &vector)
{
	return sqrt(lengthSq(vector));
}

sf::Vector2f projectedOnto(const sf::Vector2f &vector, const sf::Vector2f &axis)
{
	return dot(axis, vector) / lengthSq(axis) * axis;
}

float sigmoid(const float x)
{
	return 1 / (1 + exp(-x));
}

float uniform(const float min, const float max)
{
	random_device dre;
	uniform_real_distribution distribution(min, max);
	return distribution(dre);
}

int uniformInt(const int min, const int max)
{
	random_device dre;
	uniform_int_distribution distribution(min, max);
	return distribution(dre);
}
