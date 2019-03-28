#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Enums.h>
#include <EllipseShape.h>
#include <QuadPart.h>
//////////////////////////
class Object : public QuadPart, public sf::Drawable {
private:
	ShapeType m_Type;
	void CreateShape(ShapeType p_eShapeType, unsigned int p_uiPointCount);
public:
	sf::Shape* m_pPolyShape;
	Object(ShapeType p_eShapeType);
	Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size);
	Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_uiPointCount);
	~Object();

	std::string m_Name;

	Object(const Object& p_Other);
	void operator=(const Object& p_Other);

	void UpdateShape();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};