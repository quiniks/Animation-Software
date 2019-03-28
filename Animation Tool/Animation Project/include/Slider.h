#pragma once

#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable
{
private:
	bool m_Sliding = false;
	sf::RectangleShape m_SliderBar;
	sf::RectangleShape m_SliderHandle;
	sf::Vector2f m_MousePos;
	bool isOver(sf::Vector2f p_MousePos);
public:
	Slider();
	Slider(sf::Vector2f p_Pos, float p_Length);
	void HandleMouseInput(sf::Mouse::Button p_Button, bool p_State);
	void HandleMouseMove(sf::Vector2i l_MousePos);
	void SetLength(float p_Length);
	void setPosition(sf::Vector2f p_Pos);
	float getPercent();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};