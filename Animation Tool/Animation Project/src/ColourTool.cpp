#include "..\include\ColourTool.h"

ColourTool::ColourTool(InteractionPtrs * p_pSP) : ITool(p_pSP)
{
	m_pColourPanel = new ColourPanel(sf::Vector2f(1.f, 23.f));
}

ColourTool::~ColourTool()
{
	delete m_pColourPanel;
	m_pColourPanel = nullptr;
}

void ColourTool::Update(float p_DeltaTime)
{

}

void ColourTool::OnMouseClick(sf::Mouse::Button p_Button, bool p_bState)
{
	m_pColourPanel->HandleMouseInput(p_Button, p_bState);
	if (p_Button == sf::Mouse::Left and p_bState and m_Active) {
		for (Object* i : getShapes()->GetObjects()) {
			if (i->Contains(m_MouseCanvasPos)) {
				i->m_pPolyShape->setFillColor(m_pColourPanel->getColour());
				break;
			}
		}
	}
}

void ColourTool::OnMouseMove(sf::Vector2i p_MouseWindowPos, sf::Vector2f p_MouseWorldPos)
{
	m_MouseCanvasPos = p_MouseWorldPos;
	m_pColourPanel->HandleMouseMove(p_MouseWindowPos);
}

void ColourTool::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_pColourPanel);
}