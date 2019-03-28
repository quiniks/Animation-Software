#include "..\include\JointTool.h"

sf::Vector2i JointTool::ToWindow(sf::Vector2f p_Pos)
{
	return getWindow()->mapCoordsToPixel(p_Pos, *getCamera());
}

JointTool::JointTool(InteractionPtrs * p_pSP) : ITool(p_pSP)
{
	m_Line = sf::VertexArray(sf::Lines, 2);
	m_Line[0].color = sf::Color::Black;
	m_Line[1].color = sf::Color::Cyan;
}

JointTool::~JointTool()
{

}

void JointTool::Update(float p_DeltaTime)
{
	m_Line[1].position = (sf::Vector2f)m_MouseWindowPos;
}

void JointTool::OnMouseClick(sf::Mouse::Button p_Button, bool p_bState)
{
	if (p_Button == sf::Mouse::Left and p_bState and m_Active and getShapes()->GetSize() >= 2) {
		if (!m_bSelecting) {
			for (Object* i : getShapes()->GetObjects()) {
				if (i->Contains(m_MouseCanvasPos)) {
					m_ParentObject = i;
					m_bSelecting = true;

					m_Line[0].position = (sf::Vector2f)ToWindow(m_ParentObject->GetPosition());
					break;
				}
			}
		}
		else {
			for (Object* i : getShapes()->GetObjects()) {
				//TODO
				//Add a form of joint child checking to prevent joint loops
				//Or change QuadPart to not rotate itself when doing resizing and contain checks
				if (i->Contains(m_MouseCanvasPos) and i != m_ChildObject) {
					m_ChildObject = i;
					m_bSelecting = false;

					m_ParentObject->AddChild(m_ChildObject);
					m_ChildObject->SetParent(m_ParentObject);

					break;
				}
			}
		}
	}
}

void JointTool::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_bSelecting) {
		target.draw(m_Line);
	}
}
