#pragma once

#include <SFML/Graphics.hpp>
/**
* @class EllipseShape
* @brief Custom SFML shape class since sf::Circle cannont be scaled along the x and y axis individually
*/
class EllipseShape : public sf::Shape {
private:
	//! Radius in x and y
	sf::Vector2f m_radius;
	//! Point count determines how smooth the ellipse is
	unsigned int m_uiPointCount;
public:
	//! constructor sets up the initial variables i.e. radius and point count
	explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0), unsigned int p_uiPointCount = 50) : m_radius(radius), m_uiPointCount(p_uiPointCount) {
		update();
	};
	//! Radius setter
	void setRadius(const sf::Vector2f& radius);
	//! Radius getter
	const sf::Vector2f& getRadius() const;
	//! Point count getter
	virtual unsigned int getPointCount() const;
	//! Returns point with specified index
	virtual sf::Vector2f getPoint(unsigned int index) const;
};