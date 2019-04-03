#pragma once

#include <SFML/Graphics.hpp>

/**
* @class Slider
* @brief Used to create a very simple slider
*/
class Slider : public sf::Drawable
{
private:
	//! Is the slider being used
	bool m_Sliding = false;
	//! The rectangle used as the slider bar
	sf::RectangleShape m_SliderBar;
	//! The ractangle used as the slider's handle
	sf::RectangleShape m_SliderHandle;
	//! The mouse position
	sf::Vector2f m_MousePos;
	//! Is the mouse over the slider's handles
	bool isOver(sf::Vector2f p_MousePos);
public:
	//! constructor
	Slider();
	//! constructor that takes position and length
	Slider(sf::Vector2f p_Pos, float p_Length);
	//! Callback that handles the mouse button events
	void HandleMouseInput(sf::Mouse::Button p_Button, bool p_State);
	//! Callback that handles the mouse move events
	void HandleMouseMove(sf::Vector2i l_MousePos);
	//! Length of the slider setter
	void SetLength(float p_Length);
	//! Position setter
	void setPosition(sf::Vector2f p_Pos);
	//! Percentage that the bar has progress getter
	float getPercent();
	//! Draw method draws the UI
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};