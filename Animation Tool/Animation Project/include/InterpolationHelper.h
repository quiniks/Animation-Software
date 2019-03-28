#pragma once
#include "SFML/Graphics.hpp"

class InterpolationHelper {
public:
	sf::Vector2f Linear(float p_Progress, sf::Vector2f p_Prev, sf::Vector2f);
};