#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "Signal.h"

class SFMLInputHandler {
private:
	Signal<sf::Vector2i> m_MouseMove;
	Signal<sf::Vector2i, sf::Vector2f> m_MouseMoveExtra;
	Signal<bool> m_LMB;
	Signal<sf::Mouse::Button, bool> m_MouseButton;
	Signal<float> m_MouseWheel;
public:
	SFMLInputHandler() {
		//std::cout << &m_MouseMove << std::endl;
		EventHandlerInstance.Register2("MouseMoved", &m_MouseMove);
		EventHandlerInstance.Register2("LMB", &m_LMB);
		EventHandlerInstance.Register2("MouseMovedExtra", &m_MouseMoveExtra);
		EventHandlerInstance.Register2("MouseButton", &m_MouseButton);
		EventHandlerInstance.Register2("MouseWheel", &m_MouseWheel);
	}
	void HandleInputs(sf::RenderWindow& p_Window, sf::View& p_View);
};