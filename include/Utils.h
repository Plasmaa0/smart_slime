#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

float dot(const sf::Vector2f &vector1, const sf::Vector2f &vector2);

float lengthSq(const sf::Vector2f &vector);

float length(const sf::Vector2f &vector);

sf::Vector2f normalized(const sf::Vector2f &vector);

sf::Vector2f projectedOnto(const sf::Vector2f &vector,
                           const sf::Vector2f &axis);

float sigmoid(const float x);

float uniform(const float min, const float max);

// min and max are inclusive (both can be generated)
int uniformInt(const int min, const int max);
