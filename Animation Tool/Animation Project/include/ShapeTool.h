#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include <EllipseShape.h>
#include "Signal.h"
/**
* @class ShapeTool
* @brief Handles the drawing and creation of a shape
*/
class ShapeTool : public  ITool {
private:
	//! Is a shape currently being drawn
	bool m_bDrawing = false;
	//! the position of the mouse when beginning to draw the shape
	sf::Vector2f m_StartPos;
	//! the type of shape being drawn
	ShapeType m_eMode = RectangleType;
	//! a pointer to the shape being drawn
	Object* m_ShapeBeingDrawn;
	//! the ID of the shape being drawn
	unsigned int m_IDBeingDrawn;
	//! signal to notify callback functions when a shape has finished being drawn
	Signal<unsigned int> OnDrawEnd;
public:
	//! Constructor that takes the interactionPtrs that contain useful classes for the creation of new shapes
	ShapeTool(InteractionPtrs * p_pSP);
	//! update method used to visually update the shape benig drawn
	void Update(float p_DeltaTime) override;
	//! callback that is called on the mouse being clicked
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
};