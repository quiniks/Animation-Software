#include "..\include\Object.h"

void Object::CreateShape(ShapeType p_eShapeType, unsigned int p_uiPointCount)
{
	m_Type = p_eShapeType;
	sf::Vector2f l_Size = GetSize();
	if (p_eShapeType == RectangleType) {
		m_pPolyShape = new sf::RectangleShape(l_Size);
	}
	else if (p_eShapeType == EllipseType) {
		m_pPolyShape = new EllipseShape(l_Size, p_uiPointCount);
	}
	else {
		m_pPolyShape = new sf::RectangleShape(l_Size);
	}
	m_pPolyShape->setFillColor(sf::Color::Cyan);
	m_pPolyShape->setPosition(GetVertex(0));
	m_pPolyShape->setRotation(GetRotation());
}

Object::Object(ShapeType p_eShapeType) : QuadPart(sf::Vector2f(0.0f , 0.0f), sf::Vector2f(10.0f, 10.0f))
{
	CreateShape(p_eShapeType, 50);
}

Object::Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size) : QuadPart(p_Pos, p_Size)
{
	CreateShape(p_eShapeType, 50);
}

Object::Object(ShapeType p_eShapeType, sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_uiPointCount) : QuadPart(p_Pos, p_Size)
{
	CreateShape(p_eShapeType, p_uiPointCount);
}

Object::~Object()
{
	delete m_pPolyShape;
	m_pPolyShape = nullptr;
}

Object::Object(const Object & p_Other)
{
	*this = p_Other;
}

void Object::operator=(const Object & p_Other)
{
	m_Type = p_Other.m_Type;
	if (m_Type == RectangleType) {
		m_pPolyShape = new sf::RectangleShape(*dynamic_cast<sf::RectangleShape*>(p_Other.m_pPolyShape));
	}
	else if (m_Type == EllipseType) {
		m_pPolyShape = new EllipseShape(*dynamic_cast<EllipseShape*>(p_Other.m_pPolyShape));
	}
	m_Position = p_Other.m_Position;
	m_Rotation = p_Other.m_Rotation;
	m_Visible = p_Other.m_Visible;
	m_Quad = p_Other.m_Quad;
	m_AAVertices = p_Other.m_AAVertices;
	m_JointChilds = p_Other.m_JointChilds;
	m_JointParent = p_Other.m_JointParent;
	m_DebugPos = p_Other.m_DebugPos;
	m_Line = p_Other.m_Line;
}

void Object::UpdateShape()
{
	m_pPolyShape->setPosition(GetVertex(0));
	m_pPolyShape->setRotation(GetRotation());
	if (m_Type == RectangleType) {
		sf::RectangleShape* l_pRect = dynamic_cast<sf::RectangleShape*>(m_pPolyShape);
		l_pRect->setSize(GetSize());
		//std::cout << dynamic_cast<sf::RectangleShape*>(m_pPolyShape)->getSize().x << std::endl;
	}
	else if (m_Type == EllipseType) {
		EllipseShape* l_pEllipse = dynamic_cast<EllipseShape*>(m_pPolyShape);
		l_pEllipse->setRadius(GetSize()/2.0f);
	}

	m_DebugPos.setPosition(GetPosition());
	if (getParent() != nullptr) {
		m_Line[0].position = getParent()->GetPosition();
		m_Line[1].position = GetPosition();
	}
}

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (m_Type == RectangleType) {
		sf::RectangleShape* l_pRect = dynamic_cast<sf::RectangleShape*>(m_pPolyShape);
		target.draw(*l_pRect);
	}
	else if (m_Type == EllipseType) {
		
		EllipseShape* l_pEllipse = dynamic_cast<EllipseShape*>(m_pPolyShape);
		target.draw(*l_pEllipse);
	}
}