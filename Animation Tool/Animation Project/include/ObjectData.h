#pragma once
#include <SFML/Graphics.hpp>
//#include "QuadPart.h"

class ObjectData {
public:
	float m_Rotation;
	sf::Vector2f m_Position;
	std::vector<sf::Vector2f> m_Vertices;
};