#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ObjectData.h"
/**
* @class QuadPart
* @brief A class that can handle more complex transformations and store joint data
* Made from a basic vertex array to allow for more precise transformations than that of an SFML shape
*/
class QuadPart //: public sf::Drawable
{
private:
	//! Initialise method called on construction
	void Initialise();
	//! Update method that handles an axis aligned set of vertices
	void Update();
	//! Method to move all and only the vertices
	void MoveVertices(sf::Vector2f p_Offset);
	//! Method to rotate the quadpart (vertices and pos) around a point of rotation
	void RotateVertices(float p_Offset, sf::Vector2f p_PointOfRot);
	//! Method that rotates this and all child joint quadparts around a given point of rotation
	void RotateChild(float p_Offset, sf::Vector2f p_PointOfRot);
	//! Method for calculating the middle point of two vectors
	sf::Vector2f MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2);
protected:
	//! The Position of the quadpart (treat it like a point that can be defined as being anywhere and not as something like centre point)
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	//! The rotation of the quadpart
	float m_Rotation = 0.0f;
	//! The quadrilateral vertex array 
	sf::VertexArray m_Quad = sf::VertexArray(sf::Quads, 4);
	//! Is the vertex array visible
	bool m_Visible = false;
	//! The axis aligned set of vertices
	std::vector<sf::Vector2f> m_AAVertices;
	//! A vector of quadpart pointers that are considered child joints
	std::vector<QuadPart*> m_JointChilds;
	//! the parent joint quadpart
	QuadPart* m_JointParent = nullptr;
	//! Circle shape used to visually debug the position point
	sf::CircleShape m_DebugPos;
	//! Line shape used to visually debug the joints
	sf::VertexArray m_Line;
public:
	//! Defualt constructor
	QuadPart();
	//! Constructor the sets the position and size
	QuadPart(sf::Vector2f p_Pos, sf::Vector2f p_Size);
	//Setters
	//! Method for setting the origin (only moves the position vector2f)
	void SetOrigin(sf::Vector2f p_Pos);
	//! Method for resizing the shape by a given offset and a handle that determines how to apply the offset
	//! Handle can 0 through 7 and will allow the translation of either one of the four vertices or one of the four sides
	//! sides being locked from translating in the direction along their line
	void ReSize(sf::Vector2f p_Offset, unsigned int p_iHandle);
	//! Moves the position and the vertices by an offset
	void Move(sf::Vector2f p_Offset);
	//! Method that rotates the shape by an offset
	void Rotate(float p_Offset);
	//! Method for setting the position of the quadpart, this includes the vertices
	void SetPosition(sf::Vector2f p_Pos);
	//! Method for setting the rotation at a given angle
	void SetRotation(float p_Angle);
	//Getters
	//! Returns the positon
	sf::Vector2f GetPosition();
	//! Returns the rotation
	float GetRotation();
	//! Returns one of the four vertices
	sf::Vector2f GetVertex(unsigned int p_Vertex);
	//! Returns one of the four vertices or four middle points of each side
	sf::Vector2f GetVertex8(unsigned int p_Vertex);
	//! Returns the size of the shape determined by the axis aligned vertices
	sf::Vector2f GetSize();
	//frame data getter
	//! Returns the objects data i.e. position, rotation and vertices
	ObjectData GetObjectData();
	//! Transforms the shape based on given object data
	void LoadObjectData(ObjectData p_ObjectData);
	//Checkers
	//! Checks if a positon is inside the quadpart
	bool Contains(sf::Vector2f p_Pos);
	//Joint methods
	//! Sets the joint parent quadpart pointer
	void SetParent(QuadPart* p_JointParent);
	//! Adds a joint child quadpart pointer
	void AddChild(QuadPart* p_JointChild);
	//! Returns a pointer of the joint parent quadpart
	QuadPart* getParent();
	//! Returms a pointer of a joint child quadpart using an index p_I
	QuadPart* getChild(unsigned int p_I);
	//Render
	//! Draw method for drawing debug shapes
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
