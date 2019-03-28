#include "..\include\TransformTool.h"

sf::Vector2i TransformTool::ToWindow(sf::Vector2f p_Pos)
{
	return getWindow()->mapCoordsToPixel(p_Pos, *getCamera());
}

sf::Vector2f TransformTool::ToCanvas(sf::Vector2i p_Pos)
{
	return getWindow()->mapPixelToCoords(p_Pos, *getCamera());
}

sf::Vector2f TransformTool::MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2)
{
	sf::Vector2f l_Diff = p_Pos2 - p_Pos1;
	sf::Vector2f l_Middle = p_Pos1 + l_Diff / 2.0f;
	return l_Middle;
}

TransformTool::TransformTool(InteractionPtrs * p_pSP) : ITool(p_pSP)
{
	EventHandlerInstance.Register2("OnTransformEnd", &OnTransformEnd);

	m_DefaultCursor.loadFromSystem(sf::Cursor::Arrow);
	m_MoveCursor.loadFromSystem(sf::Cursor::SizeAll);
	m_HandCursor.loadFromSystem(sf::Cursor::Hand);
	m_VertCursor.loadFromSystem(sf::Cursor::SizeVertical);
	m_HoriCursor.loadFromSystem(sf::Cursor::SizeHorizontal);
	m_Diag1Cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
	m_Diag2Cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
}

TransformTool::~TransformTool()
{
	RemoveFrame();
}

void TransformTool::OnMouseClick(sf::Mouse::Button p_Button, bool p_bState)
{
	if (p_Button == sf::Mouse::Left and p_bState and m_Active) {
		bool l_bUsingHandle = false;
		bool l_bShapeFound = false;
		if (m_pSelectedObject != nullptr) {
			sf::Vector2f l_MouseWindowPos = (sf::Vector2f)getWindow()->mapCoordsToPixel(m_MouseCanvasPos, *getCamera());
			for (int i = 0; i < m_iHandleNum; i++) {
				if (m_ScaleHandles[i]->getGlobalBounds().contains(l_MouseWindowPos)) {
					m_ScaleHandles[i]->setFillColor(sf::Color(100, 100, 100, 255));
					m_SelectedHandle = i;

					l_bUsingHandle = true;
					m_bScaling = true;
					break;
				}
				else if (m_OriginHandle->getGlobalBounds().contains(l_MouseWindowPos)) {
					m_OriginHandle->setFillColor(sf::Color(100, 100, 100, 0));
					m_bMoveingOrigin = true;
					l_bUsingHandle = true;
				} else if (m_RotateHandle->getGlobalBounds().contains(l_MouseWindowPos)) {
					m_OriginHandle->setFillColor(sf::Color(0, 100, 0, 0));
					m_bRotating = true;
					l_bUsingHandle = true;
					m_ShapeInitialPos = m_pSelectedObject->GetPosition();
					m_ShapeInitialRot = m_pSelectedObject->GetRotation();
				}
			}
		}
		if (!l_bUsingHandle) {
			for (std::pair<unsigned int, Object*> i : getShapes()->GetIDAndObjects()) {
				if (i.second->Contains(m_MouseCanvasPos)) {
					l_bShapeFound = true;
					//std::cout << "!" << std::endl;
					m_MouseInitialPos = m_MouseCanvasPos;
					if (m_pSelectedObject != nullptr) {
						m_ShapeInitialPos = m_pSelectedObject->GetPosition();
					}
					m_bTranslating = true;
					if (m_pSelectedObject != i.second) {
						//Shape selected
						m_IDOfSelectedObject = i.first;
						m_pSelectedObject = i.second;
						m_ShapeInitialPos = m_pSelectedObject->GetPosition();
						CreateFrame();
						break;
					}
				}
			}
		}

		if (!l_bShapeFound and !l_bUsingHandle) {
			RemoveFrame();
			m_pSelectedObject = nullptr;
		}
	}
	else if (p_Button == sf::Mouse::Left and !p_bState) {
		m_bScaling = false;
		m_bTranslating = false;
		m_bMoveingOrigin = false;
		m_bRotating = false;
		if (m_HandlesActive) {
			for (int i = 0; i < m_iHandleNum; i++) {
				m_ScaleHandles[i]->setFillColor(sf::Color::White);
			}
			m_OriginHandle->setFillColor(sf::Color(255, 255, 255, 0));
		}
		//Finished transforming
		if (m_pSelectedObject != nullptr) {
			OnTransformEnd.Notify(m_IDOfSelectedObject);
		}
	}
}

void TransformTool::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_pSelectedObject != nullptr) {
		for (sf::CircleShape* handle : m_ScaleHandles) {
			target.draw(*handle);
		}
		target.draw(*m_OriginHandle);
		target.draw(*m_RotateHandle);
	}
}

void TransformTool::Update(float p_DeltaTime)
{
	bool l_HandleFound = false;
	if (m_pSelectedObject != nullptr) {
		sf::Vector2f l_MouseWindowPos = (sf::Vector2f)ToWindow(m_MouseCanvasPos);
		if (m_pSelectedObject->Contains(m_MouseCanvasPos) and !l_HandleFound) {
			getWindow()->setMouseCursor(m_MoveCursor);
		} else if (!m_bScaling and !m_bMoveingOrigin and !m_bTranslating and !l_HandleFound) {
			getWindow()->setMouseCursor(m_DefaultCursor);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	if (m_pSelectedObject != nullptr) {
		if (m_bScaling) {
			sf::Vector2f l_Diff = m_MouseCanvasPos - ToCanvas((sf::Vector2i)m_ScaleHandles[m_SelectedHandle]->getPosition());
			m_pSelectedObject->ReSize(l_Diff, m_SelectedHandle);
		}
		else if (m_bTranslating) {
			m_pSelectedObject->SetPosition(m_ShapeInitialPos + (m_MouseCanvasPos - m_MouseInitialPos));
		}
		else if (m_bMoveingOrigin) {
			m_pSelectedObject->SetOrigin(m_MouseCanvasPos);
		} else if (m_bRotating) {
			sf::Vector2f l_Up(0.0f, 1.0f);
			sf::Vector2f l_Hyp = m_MouseCanvasPos - m_ShapeInitialPos;
			float l_Angle = -std::atan2f(l_Up.x*l_Hyp.y - l_Up.y*l_Hyp.x, l_Up.x*l_Hyp.x - l_Up.y*l_Hyp.y) * 180 / 3.1415;
			m_pSelectedObject->SetRotation(l_Angle);
		}
		SetFrame();
	}
}

void TransformTool::CreateFrame()
{
	m_HandlesActive = true;
	for (int i = 0; i < m_iHandleNum; i++) {
		m_ScaleHandles[i] = new sf::CircleShape();
		m_ScaleHandles[i]->setRadius(5.0f);
		m_ScaleHandles[i]->setOrigin(sf::Vector2f(5.0f, 5.0f));
		m_ScaleHandles[i]->setFillColor(sf::Color::White);
		m_ScaleHandles[i]->setOutlineColor(sf::Color::Black);
		m_ScaleHandles[i]->setOutlineThickness(1.5f);
	}
	m_OriginHandle = new sf::CircleShape();
	m_OriginHandle->setRadius(5.0f);
	m_OriginHandle->setOrigin(sf::Vector2f(5.0f, 5.0f));
	m_OriginHandle->setFillColor(sf::Color(100, 100, 100, 0));
	m_OriginHandle->setOutlineColor(sf::Color::Black);
	m_OriginHandle->setOutlineThickness(1.5f);

	m_RotateHandle = new sf::CircleShape();
	m_RotateHandle->setRadius(5.0f);
	m_RotateHandle->setOrigin(sf::Vector2f(5.0f, 5.0f));
	m_RotateHandle->setFillColor(sf::Color::Green);
	m_RotateHandle->setOutlineColor(sf::Color::Black);
	m_RotateHandle->setOutlineThickness(1.5f);
	
	SetFrame();
}

void TransformTool::SetFrame()
{
	m_OriginHandle->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetPosition()));
	sf::Transform l_R;
	l_R.rotate(m_pSelectedObject->GetRotation());
	m_RotateHandle->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetPosition() + l_R * sf::Vector2f(0.f, -30.f)));
	m_ScaleHandles[0]->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(0)));
	m_ScaleHandles[1]->setPosition(MiddleOf((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(0)), (sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(1))));
	m_ScaleHandles[2]->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(1)));
	m_ScaleHandles[3]->setPosition(MiddleOf((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(1)), (sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(2))));
	m_ScaleHandles[4]->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(2)));
	m_ScaleHandles[5]->setPosition(MiddleOf((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(2)), (sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(3))));
	m_ScaleHandles[6]->setPosition((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(3)));
	m_ScaleHandles[7]->setPosition(MiddleOf((sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(3)), (sf::Vector2f)ToWindow(m_pSelectedObject->GetVertex(0))));

}

void TransformTool::RemoveFrame()
{
	m_HandlesActive = false;
	for (int i = 0; i < m_iHandleNum; i++) {
		if (m_ScaleHandles != nullptr) {
			delete m_ScaleHandles[i];
			m_ScaleHandles[i] = nullptr;
		}
	}
	if (m_OriginHandle != nullptr) {
		delete m_OriginHandle;
		m_OriginHandle = nullptr;
	}
	if (m_RotateHandle != nullptr) {
		delete m_RotateHandle;
		m_RotateHandle = nullptr;
	}
}
