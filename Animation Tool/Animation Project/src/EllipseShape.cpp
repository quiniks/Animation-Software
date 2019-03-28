#include "..\include\EllipseShape.h"

void EllipseShape::setRadius(const sf::Vector2f & radius)
{
	m_radius = radius;
	update();
}

const sf::Vector2f & EllipseShape::getRadius() const
{
	return m_radius;
}

unsigned int EllipseShape::getPointCount() const
{
	return m_uiPointCount;
}

sf::Vector2f EllipseShape::getPoint(unsigned int index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * m_radius.x;
	float y = std::sin(angle) * m_radius.y;

	return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}
