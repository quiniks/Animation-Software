#include "..\include\InputHandler.h"

void SFMLInputHandler::HandleInputs(sf::RenderWindow & p_Window, sf::View& p_View)
{
	sf::Event event;
	while (p_Window.pollEvent(event))
	{
		sf::Vector2i l_MouseWindowPos = sf::Mouse::getPosition(p_Window);
		sf::Vector2f l_MouseCanvasPos = p_Window.mapPixelToCoords(l_MouseWindowPos, p_View);
		switch (event.type) {
		case sf::Event::Closed:
			p_Window.close();
			break;
		case sf::Event::KeyPressed:

			break;
		case sf::Event::MouseButtonPressed:
			m_MouseButton.Notify(event.mouseButton.button, true);
			if (event.mouseButton.button == sf::Mouse::Left) {
				m_LMB.Notify(true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			m_MouseButton.Notify(event.mouseButton.button, false);
			if (event.mouseButton.button == sf::Mouse::Left) {
				m_LMB.Notify(false);
			}
			break;
		case sf::Event::MouseMoved:
			m_MouseMoveExtra.Notify(l_MouseWindowPos, l_MouseCanvasPos);
			m_MouseMove.Notify(l_MouseWindowPos);
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				m_MouseWheel.Notify(event.mouseWheelScroll.delta);
			}
			break;
		default:
			break;
		}
	}
}
