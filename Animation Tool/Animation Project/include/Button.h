#pragma once

#include <SFML/Graphics.hpp>
#include <ToolBox.h>
#include <functional>
#include "Signal.h"
#include "EventHandler.h"

class Button : public sf::RectangleShape
{
private:
	//sf::Texture* m_TextureButton;
	//sf::Texture* m_TextureIcon;
	//sf::RenderTexture l_RenderTexture;
	bool m_isOver;
public:
	Button(std::string p_SignalName, std::string p_IconFilePath, const sf::Vector2f& p_Pos, const sf::Vector2f& p_Size);
	Signal<> onClicked;
	Signal<bool> onAnyButtonOver;

	void OnMouseClick(bool p_State);
	void OnMouseMove(sf::Vector2i p_Pos);
};