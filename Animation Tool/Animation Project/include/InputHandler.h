#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "Signal.h"

/**
* @class SFMLInputHandler
* @brief Class that manages SFML's input events and notifies thier corresponding signals
*/
class SFMLInputHandler {
private:
	//! Signal for mouse movement
	Signal<sf::Vector2i> m_MouseMove;
	//! Signal for mouse movement that sends window and canvas position
	Signal<sf::Vector2i, sf::Vector2f> m_MouseMoveExtra;
	//! Signal for left mouse button states
	Signal<bool> m_LMB;
	//! Generic signal for all changes in mouse button states
	Signal<sf::Mouse::Button, bool> m_MouseButton;
	//! Signal for changes in the mouse wheel
	Signal<float> m_MouseWheel;
public:
	//! Constructor that registers all the signals with the event handler
	SFMLInputHandler() {
		EventHandlerInstance.Register2("MouseMoved", &m_MouseMove);
		EventHandlerInstance.Register2("LMB", &m_LMB);
		EventHandlerInstance.Register2("MouseMovedExtra", &m_MouseMoveExtra);
		EventHandlerInstance.Register2("MouseButton", &m_MouseButton);
		EventHandlerInstance.Register2("MouseWheel", &m_MouseWheel);
	}
	//! Handle inputs function (called in the main loop)
	void HandleInputs(sf::RenderWindow& p_Window, sf::View& p_View);
};