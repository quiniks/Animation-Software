#pragma once

#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape {
private:
	sf::Vector2f m_radius;
	unsigned int m_uiPointCount;
public:
	explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0), unsigned int p_uiPointCount = 50) : m_radius(radius), m_uiPointCount(p_uiPointCount) {
		update();
	};

	void setRadius(const sf::Vector2f& radius);

	const sf::Vector2f& getRadius() const;

	virtual unsigned int getPointCount() const;

	virtual sf::Vector2f getPoint(unsigned int index) const;
};