#include "..\include\Canvas.h"

Canvas::Canvas(sf::RenderWindow* p_pWindow)
{
	m_pWindow = p_pWindow;
	if (!RendTex.create(500, 500)) {
		std::cout << "Failed to create canvas" << std::endl;
	}
}

void Canvas::Update()
{
	if (m_bMoving) {
		setPosition((sf::Vector2f)sf::Mouse::getPosition(*m_pWindow) - m_MouseOffset);
		//std::cout << getPosition().x << std::endl;
	}
}

void Canvas::Draw(const sf::Drawable & p_Drawable)
{
	RendTex.draw(p_Drawable);
}

void Canvas::Clear(const sf::Color& color)
{
	RendTex.clear(color);
}

void Canvas::Display()
{
	RendTex.display();
	setTexture(RendTex.getTexture());
}

void Canvas::HandleMouseInput(sf::Mouse::Button p_Button, bool p_bState)
{
	if (p_Button == sf::Mouse::Middle and p_bState == true) {
		m_MouseOffset = (sf::Vector2f)sf::Mouse::getPosition(*m_pWindow) - getPosition();
		m_bMoving = true;
	}
	else if (p_Button == sf::Mouse::Middle and p_bState == false) {
		m_bMoving = false;
	}
}

sf::RenderTexture * Canvas::RendTexPtr()
{
	return &RendTex;
}
