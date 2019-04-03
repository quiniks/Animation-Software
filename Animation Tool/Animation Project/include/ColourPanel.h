#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Slider.h"

/**
* @class ColourPanel
* @brief Provides a very simple UI for selecting a colour
*/
class ColourPanel : public sf::Drawable {
private:
	//! The UI frame
	sf::RectangleShape m_Frame;
	//! The mouse position
	sf::Vector2f m_MousePos;
	//! The slider for red
	Slider m_SliderRed;
	//! The slider for blue
	Slider m_SliderBlue;
	//! The slider for green
	Slider m_SliderGreen;
	//! The colour
	sf::Color m_Colour;
public:
	//! Constructor that takes the position for the panel
	ColourPanel(sf::Vector2f p_Pos);
	//! Colour getter
	sf::Color getColour();
	//! Update method
	void Update(float p_DeltaTime);
	//! Callback for handling mouse button events
	void HandleMouseInput(sf::Mouse::Button p_Button, bool p_bState);
	//! Callback for handling mouse move events
	void HandleMouseMove(sf::Vector2i p_Position);
	//! Draw method for drawing the panel
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};