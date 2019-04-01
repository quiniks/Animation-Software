#pragma once
#include <SFML/Graphics.hpp>

//! Struct that holds object data i.e. position, rotation and vertices
class ObjectData {
public:
	float m_Rotation;
	sf::Vector2f m_Position;
	std::vector<sf::Vector2f> m_Vertices;
};