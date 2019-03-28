#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include "EventHandler.h"

class Camera : public sf::View
{
private:
	bool m_bMoving = false;
	sf::Vector2i m_MousePos;
	sf::Vector2i m_MouseStartPos;
	sf::Vector2f m_ViewStartPos;

	float m_ZoomSpeed = -50.0f;
	sf::Vector2f m_ZoomFactor = sf::Vector2f(1.0f, 1.0f);
	sf::Vector2f m_InitialSize;
	float m_Scale = 1.0f;
public:
	Camera(sf::Vector2f p_Center, sf::Vector2f p_Size);
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState);
	void OnMouseWheel(float p_fDelta);
	void OnMouseMove(sf::Vector2i p_Position);
	sf::Vector2f getScale();
};

