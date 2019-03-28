#pragma once
#include <SFML/Graphics.hpp>

class ColourPicker {
private:
	sf::Color m_Colour;
	sf::RectangleShape m_Frame;

	sf::VertexArray m_SVPallette;
	sf::CircleShape m_SVHandle;

	sf::VertexArray m_HPallette;
	sf::RectangleShape m_HHandle;

	sf::RectangleShape m_ColourBox;
public:
	ColourPicker(sf::Vector2f p_Pos);
};