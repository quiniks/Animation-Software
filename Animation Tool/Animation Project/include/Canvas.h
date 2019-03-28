#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Canvas : public sf::Sprite
{
public:
	Canvas(sf::RenderWindow* p_pWindow);
	void Update();
	void Draw(const sf::Drawable& p_Drawable);
	void Clear(const sf::Color& color);
	void Display();
	void HandleMouseInput(sf::Mouse::Button p_Button, bool p_bState);
	sf::RenderTexture* RendTexPtr();
private:
	sf::RenderTexture RendTex;
	sf::RenderWindow* m_pWindow;

	bool m_bMoving;
	sf::Vector2f m_MouseOffset;
};

