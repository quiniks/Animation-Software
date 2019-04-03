#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Enums.h>
#include <EllipseShape.h>
#include <QuadPart.h>
/**
* @class Object
* @brief Handles a quadpart and polyshape to make up a more transformable object that just using an SFML shape
*/
class Object : public QuadPart, public sf::Drawable {
private:
	//! Shape type enum used to recast the polyshape for transformations
	ShapeType m_Type;
	//! Create shape method creates the polyshape based on a given shape type enum and pointcount
	void CreateShape(ShapeType p_eShapeType, unsigned int p_uiPointCount);
public:
	//! The polymorphic sfml shape pointer
	sf::Shape* m_pPolyShape;
	//! Constructor that takes just a shape type enum
	Object(ShapeType p_eShapeType);
	//! Constructor that thake shape type, position and size
	Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size);
	//! Constructor that takes shape type, position, size and point count
	Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_uiPointCount);
	~Object();
	//! Name associated with this object (not yet used)
	std::string m_Name;
	//! Object copy constructor overload 
	Object(const Object& p_Other);
	//! Object assignment operator overload that prevents polyshape becoming invalid
	void operator=(const Object& p_Other);
	//! Update the polyshape to match the quadpart shape
	void UpdateShape();
	//! Draw the polyshape
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};