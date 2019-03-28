#include "..\include\ScrollBox.h"

ScrollBox::ScrollBox(sf::Vector2f p_Pos, sf::Vector2f p_Size, sf::Vector2f p_ContainerSize, bool p_HasVertiBar, bool p_HasHoriBar)
{
	m_RenderTex.create(p_Size.x, p_Size.y);

	m_VertiBar.setFillColor(sf::Color::Black);
	m_HoriBar.setFillColor(sf::Color::Black);

	m_Box.setPosition(p_Pos);
	m_Box.setSize(p_Size);
	if (p_HasVertiBar) {
		m_Box.setSize(m_Box.getSize() - sf::Vector2f(m_BarWidth, 0));
	}
	if (p_HasHoriBar) {
		m_Box.setSize(m_Box.getSize() - sf::Vector2f(0, m_BarWidth));
	}

	m_HoriBarVisible = p_HasHoriBar;
	m_VertiBarVisible = p_HasVertiBar;

	m_VertiBar.setPosition(sf::Vector2f(m_Box.getPosition().x + m_Box.getSize().x - m_BarWidth, m_Box.getPosition().y));
	m_HoriBar.setPosition(sf::Vector2f(m_Box.getPosition().x, m_Box.getPosition().y + m_Box.getSize().y - m_BarWidth));
	m_VertiBar.setSize(sf::Vector2f(m_BarWidth, m_Box.getSize().y));
	m_HoriBar.setSize(sf::Vector2f(m_Box.getSize().x, m_BarWidth));

	if (p_ContainerSize.x > p_Size.x) {
		float l_HandleLength = (p_Size.x / p_ContainerSize.x) * p_Size.x;
		m_HoriHandle.setPosition(m_HoriBar.getPosition() + sf::Vector2f(2, 2));
		m_HoriHandle.setSize(sf::Vector2f(l_HandleLength - 4, m_BarWidth - 4));
	}
	if (p_ContainerSize.y > p_Size.y) {
		float l_HandleLength = (p_Size.y / p_ContainerSize.y) * p_Size.y;
		m_VertiHandle.setPosition(m_VertiBar.getPosition() + sf::Vector2f(2, 2));
		m_VertiHandle.setSize(sf::Vector2f(m_BarWidth - 4, l_HandleLength - 4));
	}
}

void ScrollBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Box);
	if (m_HoriBarVisible) {
		target.draw(m_HoriBar);
		target.draw(m_HoriHandle);
	}
	if (m_VertiBarVisible) {
		target.draw(m_VertiBar);
		target.draw(m_VertiHandle);
	}
}
