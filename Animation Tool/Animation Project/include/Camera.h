#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include "EventHandler.h"

/**
* @class Camera
* @brief A class that inherits from sf::view that handles translations and zooming
*/
class Camera : public sf::View
{
private:
	//! is the camera being moved
	bool m_bMoving = false;
	//! The mouse position in the window
	sf::Vector2i m_MousePos;
	//! The mouse start position
	sf::Vector2i m_MouseStartPos;
	//! The view's start position
	sf::Vector2f m_ViewStartPos;
	//! The zoom speed
	float m_ZoomSpeed = -50.0f;
	//! by how much in the x and y have we zoomed in or out
	sf::Vector2f m_ZoomFactor = sf::Vector2f(1.0f, 1.0f);
	//! The initial size of the view
	sf::Vector2f m_InitialSize;
	//! The scale that we have zoomed
	float m_Scale = 1.0f;
public:
	//! constructor that takes a centre position and a size
	Camera(sf::Vector2f p_Center, sf::Vector2f p_Size);
	//! Callback for mouse click events
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState);
	//! Callback for mouse wheel events
	void OnMouseWheel(float p_fDelta);
	//! Callback for mouse move events
	void OnMouseMove(sf::Vector2i p_Position);
	//! Scale getter
	sf::Vector2f getScale();
};

