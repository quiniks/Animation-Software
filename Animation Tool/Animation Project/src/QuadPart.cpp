#include "..\include\QuadPart.h"

void QuadPart::MoveVertices(sf::Vector2f p_Offset)
{
	m_Quad[0].position += p_Offset;
	m_Quad[1].position += p_Offset;
	m_Quad[2].position += p_Offset;
	m_Quad[3].position += p_Offset;
}

void QuadPart::RotateVertices(float p_Offset, sf::Vector2f p_PointOfRot)
{
	sf::Transform l_M;
	l_M.translate(p_PointOfRot);
	l_M.rotate(p_Offset);
	l_M.translate(-p_PointOfRot);

	for (int i = 0; i < m_Quad.getVertexCount(); i++) {
		m_Quad[i].position = l_M * m_Quad[i].position;
	}
	m_Position = l_M * m_Position;
}

sf::Vector2f QuadPart::MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2)
{
	sf::Vector2f l_Diff = p_Pos2 - p_Pos1;
	sf::Vector2f l_Middle = p_Pos1 + l_Diff / 2.0f;
	return l_Middle;
}

QuadPart::QuadPart()
{
	Initialise();
}

QuadPart::QuadPart(sf::Vector2f p_Pos, sf::Vector2f p_Size)
 {
	
	m_Position = p_Pos + p_Size / 2.0f;
	m_Quad[0].position = p_Pos;	//top left
	m_Quad[1].position = p_Pos + sf::Vector2f(p_Size.x, 0.0f);	//top right
	m_Quad[2].position = p_Pos + p_Size;	//bot right
	m_Quad[3].position = p_Pos + sf::Vector2f(0.0f, p_Size.y);	//bot left

	m_Quad[0].color = sf::Color(255.f, 0.f, 0.f, 50.f);
	m_Quad[1].color = sf::Color(0.f, 255.f, 0.f, 50.f);
	m_Quad[2].color = sf::Color(255.f, 0.f, 255.f, 50.f);
	m_Quad[3].color = sf::Color(238.f, 244.f, 66.f, 50.f);

	m_DebugPos.setFillColor(sf::Color::Red);
	m_DebugPos.setRadius(2.0f);
	m_DebugPos.setOrigin(2.0f, 2.0f);

	Initialise();
 }

void QuadPart::Initialise()
{
	m_AAVertices.reserve(4);
	m_Line = sf::VertexArray(sf::Lines, 2);
	m_Line[0].color = sf::Color::Blue;
	m_Line[1].color = sf::Color::Yellow;
	Update();
}

void QuadPart::Update()
{
	m_AAVertices = { m_Quad[0].position, m_Quad[1].position, m_Quad[2].position, m_Quad[3].position };
	sf::Transform l_M;
	l_M.translate(m_Position);
	l_M.rotate(0 - m_Rotation);
	l_M.translate(-m_Position);
	for (sf::Vector2f& l_Vertex : m_AAVertices) {
		l_Vertex = l_M * l_Vertex;
	}
}

 void QuadPart::SetOrigin(sf::Vector2f p_Pos)
 {
	 m_Position = p_Pos;
	 m_DebugPos.setPosition(m_Position);
	 Update();
 }

 void QuadPart::Move(sf::Vector2f p_Offset)
 {
	 m_Position += p_Offset;
	 MoveVertices(p_Offset);

	 for (int i = 0; i < m_JointChilds.size(); i++) {
		 m_JointChilds.at(i)->Move(p_Offset);
	 }

	 Update();
 }


 void QuadPart::SetPosition(sf::Vector2f p_Pos)
 {
	 sf::Vector2f l_Offset = p_Pos - m_Position;
	 m_Position = p_Pos;
	 MoveVertices(l_Offset);
	
	for (int i = 0; i < m_JointChilds.size(); i++) {
		m_JointChilds.at(i)->SetPosition(m_JointChilds.at(i)->GetPosition() + l_Offset);
	}

	Update();
 }

 void QuadPart::Rotate(float p_Offset)
 {
	 m_Rotation += p_Offset;
	 RotateVertices(p_Offset, m_Position);

	 for (int i = 0; i < m_JointChilds.size(); i++) {
		 m_JointChilds.at(i)->RotateChild(p_Offset, m_Position);
	 }

	 Update();
 }

 void QuadPart::RotateChild(float p_Offset, sf::Vector2f p_PointOfRot)
 {
	 m_Rotation += p_Offset;
	 RotateVertices(p_Offset, p_PointOfRot);
	 for (int i = 0; i < m_JointChilds.size(); i++) {
		 m_JointChilds.at(i)->RotateChild(p_Offset, p_PointOfRot);
	 }

	 Update();
 }

 void QuadPart::SetRotation(float p_Angle)
 {
	 float l_Offset = p_Angle - m_Rotation;
	 m_Rotation = p_Angle;
	 RotateVertices(l_Offset, m_Position);

	 for (int i = 0; i < m_JointChilds.size(); i++) {
		 m_JointChilds.at(i)->RotateChild(l_Offset, m_Position);
	 }

	 Update();
 }

 sf::Vector2f QuadPart::GetPosition()
 {
	 return m_Position;
 }

 float QuadPart::GetRotation()
 {
	 return m_Rotation;
 }

 sf::Vector2f QuadPart::GetVertex(unsigned int p_Vertex)
 {
	 if (p_Vertex >= 0 and p_Vertex < m_Quad.getVertexCount()) {
		 return m_Quad[p_Vertex].position;
	 }
	 return sf::Vector2f(0.0f, 0.0f);
 }

 sf::Vector2f QuadPart::GetVertex8(unsigned int p_Vertex)
 {
	 if (p_Vertex == 0 or p_Vertex == 2 or p_Vertex == 4 or p_Vertex == 6) {
		 return GetVertex(p_Vertex/2);
	 }
	 else if (p_Vertex == 1) {
		 return MiddleOf(GetVertex(0), GetVertex(2));
	 }
	 else if (p_Vertex == 3) {
		 return MiddleOf(GetVertex(2), GetVertex(4));
	 }
	 else if (p_Vertex == 5) {
		 return MiddleOf(GetVertex(4), GetVertex(6));
	 }
	 else if (p_Vertex == 7) {
		 return MiddleOf(GetVertex(6), GetVertex(0));
	 }
	 return sf::Vector2f(0.f, 0.f);
 }

 sf::Vector2f QuadPart::GetSize()
 {
	 sf::Vector2f l_Size = m_AAVertices[2] - m_AAVertices[0];
	 return l_Size;
 }

 ObjectData QuadPart::GetObjectData()
 {
	 ObjectData l_ObjectData;
	 l_ObjectData.m_Position = m_Position;
	 l_ObjectData.m_Rotation = m_Rotation;
	 l_ObjectData.m_Vertices.push_back(m_Quad[0].position);
	 l_ObjectData.m_Vertices.push_back(m_Quad[1].position);
	 l_ObjectData.m_Vertices.push_back(m_Quad[2].position);
	 l_ObjectData.m_Vertices.push_back(m_Quad[3].position);
	 return l_ObjectData;
 }

 void QuadPart::LoadObjectData(ObjectData p_ObjectData)
 {
	 m_Position = p_ObjectData.m_Position;
	 m_Rotation = p_ObjectData.m_Rotation;
	 m_Quad[0].position = p_ObjectData.m_Vertices.at(0);
	 m_Quad[1].position = p_ObjectData.m_Vertices.at(1);
	 m_Quad[2].position = p_ObjectData.m_Vertices.at(2);
	 m_Quad[3].position = p_ObjectData.m_Vertices.at(3);
 }

 bool QuadPart::Contains(sf::Vector2f p_Pos)
 {
	 sf::FloatRect l_Rect;
	 sf::Vector2f l_Size = GetSize();

	 l_Rect.left = m_AAVertices[0].x - GetPosition().x;
	 l_Rect.top = m_AAVertices[0].y - GetPosition().y;
	 l_Rect.width = l_Size.x;
	 l_Rect.height = l_Size.y;
	 
	 sf::Transform l_M2;
	 l_M2.rotate(-GetRotation());
	 p_Pos = p_Pos - GetPosition();
	 p_Pos = l_M2 * p_Pos;

	 if (l_Rect.contains(p_Pos)) {
		 return true;
	 }
	 return false;
 }

 void QuadPart::ReSize(sf::Vector2f p_Offset, unsigned int p_iHandle)
 {
	 m_DebugPos.setPosition(m_Position);
	 sf::Transform l_R;
	 l_R.rotate(-GetRotation());
	 p_Offset = l_R * p_Offset;
	 float l_PrevRot = GetRotation();
	 SetRotation(0);
	// std::cout << p_Offset.x << " / " << p_Offset.y << std::endl;
	 switch (p_iHandle) {
	 case 0:	//top left
		 m_Quad[1].position += sf::Vector2f(0.0f, p_Offset.y);
		 m_Quad[0].position += p_Offset;
		 m_Quad[3].position += sf::Vector2f(p_Offset.x, 0.0f);
		 break;
	 case 1:	//top
		 m_Quad[0].position += sf::Vector2f(0.0f, p_Offset.y);
		 m_Quad[1].position += sf::Vector2f(0.0f, p_Offset.y);
		 break;
	 case 2:	//top right
		 m_Quad[0].position += sf::Vector2f(0.0f, p_Offset.y);
		 m_Quad[1].position += p_Offset;
		 m_Quad[2].position += sf::Vector2f(p_Offset.x, 0.0f);
		 break;
	 case 3:	//right
		 m_Quad[1].position += sf::Vector2f(p_Offset.x, 0.0f);
		 m_Quad[2].position += sf::Vector2f(p_Offset.x, 0.0f);
		 break;
	 case 4:	//bot right
		 m_Quad[1].position += sf::Vector2f(p_Offset.x, 0.0f);
		 m_Quad[2].position += p_Offset;
		 m_Quad[3].position += sf::Vector2f(0.0f, p_Offset.y);
		 break;
	 case 5:	//bot
		 m_Quad[2].position += sf::Vector2f(0.0f, p_Offset.y);
		 m_Quad[3].position += sf::Vector2f(0.0f, p_Offset.y);
		 break;
	 case 6:	//bot left
		 m_Quad[0].position += sf::Vector2f(p_Offset.x, 0.0f);
		 m_Quad[3].position += p_Offset;
		 m_Quad[2].position += sf::Vector2f(0.0f, p_Offset.y);
		 break;
	 case 7:	//left
		 m_Quad[0].position += sf::Vector2f(p_Offset.x, 0.0f);
		 m_Quad[3].position += sf::Vector2f(p_Offset.x, 0.0f);
		 break;
	 default:
		 break;
	 }
	 SetRotation(l_PrevRot);
 }

 void QuadPart::SetParent(QuadPart * p_JointParent)
 {
	 m_JointParent = p_JointParent;
 }

 void QuadPart::AddChild(QuadPart * p_JointChild)
 {
	 m_JointChilds.push_back(p_JointChild);
 }

 QuadPart * QuadPart::getParent()
 {
	 return m_JointParent;
 }

 QuadPart * QuadPart::getChild(unsigned int p_I)
 {
	 return m_JointChilds.at(p_I);
 }
 
 void QuadPart::draw(sf::RenderTarget & target, sf::RenderStates states) const
 {
	 {
		 if (m_Visible) {
			 target.draw(m_Quad);
			 target.draw(m_DebugPos);
			 target.draw(m_Line);
		 }
	 };
 }



