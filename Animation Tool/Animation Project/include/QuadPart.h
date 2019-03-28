#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ObjectData.h"

class QuadPart //: public sf::Drawable
{
private:
	//Private methods
	void Initialise();
	void Update();
	void MoveVertices(sf::Vector2f p_Offset);
	void RotateVertices(float p_Offset, sf::Vector2f p_PointOfRot);
	void RotateChild(float p_Offset, sf::Vector2f p_PointOfRot);
	sf::Vector2f MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2);
protected:
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	float m_Rotation = 0.0f;
	sf::VertexArray m_Quad = sf::VertexArray(sf::Quads, 4);
	///
	bool m_Visible = false;
	std::vector<sf::Vector2f> m_AAVertices;
	///
	std::vector<QuadPart*> m_JointChilds;
	QuadPart* m_JointParent = nullptr;
	///
	sf::CircleShape m_DebugPos;
	sf::VertexArray m_Line;
public:
	

	QuadPart();
	QuadPart(sf::Vector2f p_Pos, sf::Vector2f p_Size);
	//Setters
	void SetOrigin(sf::Vector2f p_Pos);
	void ReSize(sf::Vector2f p_Offset, unsigned int p_iHandle);
	void Move(sf::Vector2f p_Offset);
	void Rotate(float p_Offset);
	void SetPosition(sf::Vector2f p_Pos);
	void SetRotation(float p_Angle);
	//Getters
	sf::Vector2f GetPosition();
	float GetRotation();
	sf::Vector2f GetVertex(unsigned int p_Vertex);
	sf::Vector2f GetVertex8(unsigned int p_Vertex);
	sf::Vector2f GetSize();	//Doesnt work with rotation
	//frame data getter
	ObjectData GetObjectData();
	void LoadObjectData(ObjectData p_ObjectData);
	//Checkers
	bool Contains(sf::Vector2f p_Pos);
	//Joint methods
	void SetParent(QuadPart* p_JointParent);
	void AddChild(QuadPart* p_JointChild);
	QuadPart* getParent();
	QuadPart* getChild(unsigned int p_I);
	//Render
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
