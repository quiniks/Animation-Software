#pragma once
#include "SFML/Graphics.hpp"

/**
 * @class Interpolation Helper
 * @brief Contains methods for interplating between two positions
 */
class InterpolationHelper {
public:
	//! Linear interpolation solver
	sf::Vector2f Linear(float p_Progress, sf::Vector2f p_Prev, sf::Vector2f);
};