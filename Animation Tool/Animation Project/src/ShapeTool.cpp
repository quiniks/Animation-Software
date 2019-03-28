#include "ShapeTool.h"

ShapeTool::ShapeTool(InteractionPtrs * p_pSP) : ITool(p_pSP)
{
	EventHandlerInstance.Register2("OnDrawEnd", &OnDrawEnd);
}

void ShapeTool::Update(float p_DeltaTime)
{
	if (m_bDrawing == true) {
		sf::Vector2f l_Size2 = m_MouseCanvasPos - m_ShapeBeingDrawn->GetVertex(2);
		m_ShapeBeingDrawn->ReSize(l_Size2, 4);
		m_ShapeBeingDrawn->SetOrigin(m_ShapeBeingDrawn->GetVertex(0) + m_ShapeBeingDrawn->GetSize()/2.0f);
	}
}

void ShapeTool::OnMouseClick(sf::Mouse::Button p_Button, bool p_bState)
{
	if (p_Button == sf::Mouse::Left and m_Active and p_bState == true) {
		m_bDrawing = true;
		m_StartPos = m_MouseCanvasPos;
		Object l_NewObject2(m_eMode, m_MouseCanvasPos, sf::Vector2f(0.0f, 0.0f));
		std::pair<unsigned int, Object*> l_IDAndObject = getShapes()->NewShape(l_NewObject2);
		m_ShapeBeingDrawn = l_IDAndObject.second;
		m_IDBeingDrawn = l_IDAndObject.first;
	}
	else if (p_Button == sf::Mouse::Left and p_bState == false) {
		OnDrawEnd.Notify(m_IDBeingDrawn);
		m_bDrawing = false;
	}
	else if (p_Button == sf::Mouse::Right and p_bState == true) {
		m_eMode = static_cast<ShapeType>(static_cast<int>(m_eMode) + 1);
		if (m_eMode == End) {
			m_eMode = static_cast<ShapeType>(0);
		}
	}
}


