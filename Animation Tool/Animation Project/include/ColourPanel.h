#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Slider.h"

//////////////////////////////////
class ColourPanel : public sf::Drawable {
private:
	sf::RectangleShape m_Frame;
	sf::Vector2f m_MousePos;
	Slider m_SliderRed;
	Slider m_SliderBlue;
	Slider m_SliderGreen;
	sf::Color m_Colour;
public:
	ColourPanel(sf::Vector2f p_Pos);
	sf::Color getColour();
	void Update(float p_DeltaTime);
	void HandleMouseInput(sf::Mouse::Button p_Button, bool p_bState);
	void HandleMouseMove(sf::Vector2i p_Position);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};