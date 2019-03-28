#include "..\include\Camera.h"

Camera::Camera(sf::Vector2f p_Center, sf::Vector2f p_Size)
{
	std::function<void(sf::Vector2i)> test1 = std::bind(&Camera::OnMouseMove, this, std::placeholders::_1);
	std::function<void(sf::Mouse::Button, bool)> test2 = std::bind(&Camera::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2);
	std::function<void(float)> test3 = std::bind(&Camera::OnMouseWheel, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("MouseMoved", test1);
	EventHandlerInstance.Connect2("MouseButton", test2);
	EventHandlerInstance.Connect2("MouseWheel", test3);
	setCenter(p_Center);
	setSize(p_Size);
	m_InitialSize = p_Size;
}

void Camera::OnMouseClick(sf::Mouse::Button p_Button, bool p_bState)
{
	if (p_Button == sf::Mouse::Middle and p_bState == true) {
		//m_MouseViewOffset = m_MouseWorldPos - getCenter();
		m_MouseStartPos = m_MousePos;
		m_ViewStartPos = getCenter();
		m_bMoving = true;
	}
	else if (p_Button == sf::Mouse::Middle and p_bState == false) {
		m_bMoving = false;
	}
}

void Camera::OnMouseWheel(float p_fDelta)
{
	//std::cout << p_fDelta << std::endl;
	float l_AspectRatio = getSize().y / getSize().x;
	sf::Vector2f l_NewSize = getSize() + (sf::Vector2f(p_fDelta, p_fDelta * l_AspectRatio) * m_ZoomSpeed);
	setSize(l_NewSize);
	m_ZoomFactor = sf::Vector2f(getSize().x / m_InitialSize.x, getSize().y / m_InitialSize.y);
}

void Camera::OnMouseMove(sf::Vector2i p_Position)
{
	m_MousePos = p_Position;
	//std::cout << "mouse: " << m_MouseWorldPos.x << std::endl;
	//std::cout << "start: " << m_MouseStartPos.x << std::endl;
	if (m_bMoving) {
		sf::Vector2i l_MouseOffset = m_MouseStartPos - m_MousePos;
		sf::Vector2f l_ScaledMouseOffset = sf::Vector2f(l_MouseOffset.x * m_ZoomFactor.x, l_MouseOffset.y * m_ZoomFactor.y);
		setCenter(m_ViewStartPos + l_ScaledMouseOffset);
		//std::cout << (m_MouseViewOffset - m_MouseWorldPos).x << std::endl;
	}
}

sf::Vector2f Camera::getScale()
{
	return m_ZoomFactor;
}
