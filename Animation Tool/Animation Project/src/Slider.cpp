#include "..\include\Slider.h"

bool Slider::isOver(sf::Vector2f p_MousePos)
{
	if (m_SliderHandle.getGlobalBounds().contains((sf::Vector2f)p_MousePos)) {
		
		return true;
	}
	return false;
}

Slider::Slider()
{
	m_SliderBar.setSize(sf::Vector2f(50.f, 3.f));
	m_SliderBar.setOrigin(0.f, m_SliderBar.getSize().y / 2.f);
	m_SliderBar.setFillColor(sf::Color::Black);

	m_SliderHandle.setSize(sf::Vector2f(7.f, 15.f));
	m_SliderHandle.setOrigin(m_SliderHandle.getSize() / 2.f);
	m_SliderHandle.setFillColor(sf::Color::White);
	m_SliderHandle.setOutlineColor(sf::Color::Black);
	m_SliderHandle.setOutlineThickness(1.f);
}

Slider::Slider(sf::Vector2f p_Pos, float p_Length)
{
	m_SliderBar.setSize(sf::Vector2f(p_Length, 3.f));
	m_SliderBar.setOrigin(0.f, m_SliderBar.getSize().y/2.f);
	m_SliderBar.setFillColor(sf::Color::Black);
	m_SliderBar.setPosition(p_Pos);

	m_SliderHandle.setSize(sf::Vector2f(7.f, 15.f));
	m_SliderHandle.setOrigin(m_SliderHandle.getSize() / 2.f);
	m_SliderHandle.setFillColor(sf::Color::White);
	m_SliderHandle.setOutlineColor(sf::Color::Black);
	m_SliderHandle.setOutlineThickness(1.f);
	m_SliderHandle.setPosition(p_Pos);
}

void Slider::HandleMouseInput(sf::Mouse::Button p_Button, bool p_State)
{
	if (p_Button == sf::Mouse::Left and p_State) {
		if (isOver(m_MousePos)) {
			m_Sliding = true;
			m_SliderHandle.setFillColor(sf::Color(100, 100, 100, 255));
		}
	}
	else if (p_Button == sf::Mouse::Left and !p_State) {
		m_Sliding = false;
		m_SliderHandle.setFillColor(sf::Color::White);
	}
}

void Slider::HandleMouseMove(sf::Vector2i l_MousePos)
{
	if (isOver((sf::Vector2f)l_MousePos)) {
		m_SliderHandle.setFillColor(sf::Color(200, 200, 200, 255));
	}
	else {
		m_SliderHandle.setFillColor(sf::Color::White);
	}
	m_MousePos = (sf::Vector2f)l_MousePos;
	if (m_Sliding) {
		float sliderPos;
		sliderPos = m_MousePos.x;
		if (m_MousePos.x < m_SliderBar.getPosition().x) {
			sliderPos = m_SliderBar.getPosition().x;
		}
		else if (m_MousePos.x >= m_SliderBar.getPosition().x + m_SliderBar.getSize().x) {
			sliderPos = m_SliderBar.getPosition().x + m_SliderBar.getSize().x;
		}
		m_SliderHandle.setPosition(sliderPos, m_SliderHandle.getPosition().y);
	}
}

void Slider::SetLength(float p_Length)
{
	m_SliderBar.setSize(sf::Vector2f(p_Length, 3.f));
}

void Slider::setPosition(sf::Vector2f p_Pos)
{
	m_SliderBar.setPosition(p_Pos);
	m_SliderHandle.setPosition(p_Pos);
}

float Slider::getPercent()
{
	float l_Percent = (m_SliderHandle.getPosition().x - m_SliderBar.getPosition().x)/ m_SliderBar.getSize().x;
	return l_Percent;
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_SliderBar);
	target.draw(m_SliderHandle);
}
