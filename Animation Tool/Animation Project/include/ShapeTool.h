#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include <EllipseShape.h>
#include "Signal.h"

class ShapeTool : public  ITool {
private:
	bool m_bDrawing = false;
	sf::Vector2f m_StartPos;
	ShapeType m_eMode = RectangleType;
	Object* m_ShapeBeingDrawn;
	unsigned int m_IDBeingDrawn;

	Signal<unsigned int> OnDrawEnd;
public:
	ShapeTool(InteractionPtrs * p_pSP);
	void Update(float p_DeltaTime) override;
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
};