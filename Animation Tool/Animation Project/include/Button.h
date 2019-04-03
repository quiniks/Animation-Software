#pragma once

#include <SFML/Graphics.hpp>
#include <ToolBox.h>
#include <functional>
#include "Signal.h"
#include "EventHandler.h"
/**
* @class Button
* @brief A class that creates an easy to use button
*/
class Button : public sf::RectangleShape
{
private:
	//! Is the mouse over this button
	bool m_isOver;
public:
	//! Constructor
	Button(std::string p_SignalName, std::string p_IconFilePath, const sf::Vector2f& p_Pos, const sf::Vector2f& p_Size);
	//! Signal that the button has been clicked
	Signal<> onClicked;
	//! Redundant signal
	Signal<bool> onAnyButtonOver;
	//! Callback for mouse click events
	void OnMouseClick(bool p_State);
	//! Callback for mouse move events
	void OnMouseMove(sf::Vector2i p_Pos);
};