#pragma once
#include "SFML/Graphics.hpp"

class ScrollBox : public sf::Drawable {
private:
	sf::Vector2f p_Pos;
	sf::Vector2f p_Size;
	sf::Vector2f m_ContainerSize;

	float m_BarWidth = 15.f;
	bool m_HoriBarVisible;
	bool m_VertiBarVisible;

	sf::RectangleShape m_Box;
	sf::RectangleShape m_HoriBar;
	sf::RectangleShape m_HoriHandle;
	sf::RectangleShape m_VertiBar;
	sf::RectangleShape m_VertiHandle;

	sf::RenderTexture m_RenderTex;
public:
	ScrollBox(sf::Vector2f p_Pos, sf::Vector2f p_Size, sf::Vector2f p_ContainerSize, bool p_HasVertiBar, bool p_HasHoriBar);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};