#include "..\include\ColourPanel.h"


ColourPanel::ColourPanel(sf::Vector2f p_Pos)
{
	m_Frame.setFillColor(sf::Color::Black);
	m_Frame.setSize(sf::Vector2f(100.f, 65.f));
	m_Frame.setPosition(p_Pos);

	m_SliderRed.setPosition(p_Pos + sf::Vector2f(10.f, 10.0f));
	m_SliderRed.SetLength(80.f);
	m_SliderGreen.setPosition(p_Pos + sf::Vector2f(10.f, 30.0f));
	m_SliderGreen.SetLength(80.f);
	m_SliderBlue.setPosition(p_Pos + sf::Vector2f(10.f, 50.0f));
	m_SliderBlue.SetLength(80.f);
}

sf::Color ColourPanel::getColour()
{
	return m_Colour;
}

void ColourPanel::Update(float p_DeltaTime)
{

}

void ColourPanel::HandleMouseInput(sf::Mouse::Button p_Button, bool p_bState)
{
	m_SliderRed.HandleMouseInput(p_Button, p_bState);
	m_SliderGreen.HandleMouseInput(p_Button, p_bState);
	m_SliderBlue.HandleMouseInput(p_Button, p_bState);
}

void ColourPanel::HandleMouseMove(sf::Vector2i p_Position)
{
	m_MousePos = (sf::Vector2f)p_Position;

	m_SliderRed.HandleMouseMove(p_Position);
	m_SliderGreen.HandleMouseMove(p_Position);
	m_SliderBlue.HandleMouseMove(p_Position);
	m_Colour = sf::Color(255 * m_SliderRed.getPercent(), 255 * m_SliderGreen.getPercent(), 255 * m_SliderBlue.getPercent(), 255);
	m_Frame.setFillColor(m_Colour);
}

void ColourPanel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Frame);

	target.draw(m_SliderRed);
	target.draw(m_SliderGreen);
	target.draw(m_SliderBlue);
}
