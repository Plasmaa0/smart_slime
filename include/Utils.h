#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

float dot(const sf::Vector2f &vector1, const sf::Vector2f &vector2);

float lengthSq(const sf::Vector2f &vector);

float length(const sf::Vector2f &vector);

sf::Vector2f projectedOnto(const sf::Vector2f &vector, const sf::Vector2f &axis);
