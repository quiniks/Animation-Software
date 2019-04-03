#pragma once
#include "Object.h"
#include "Signal.h"
/**
* @class Shapes 
* @brief container class that handles the creation and getting of objects via IDs
*/
class Shapes : public sf::Drawable {
private:
	//! Map of IDs and objects
	std::map<unsigned int, Object> m_Shapes;
	//std::vector<Object> m_Objects2;
	//! method for determining that smallest unused ID number
	unsigned int FindEmptyID(std::vector<unsigned int> p_InUseIDs);
public:
	//! Adds a copy of a shape to the shape map and returns its ID and pointer
	std::pair<unsigned int, Object*> NewShape(Object p_NewObject);
	//! Locates and returns a reference to a shape with ID 
	Object& FindShape(unsigned int p_ID);
	//! Returns a vector with pointers to all the current objects in the map
	std::vector<Object*> GetObjects();
	//! Returns a map containing all the IDs and object data of shapes currently in the shapes map
	std::map<unsigned int, ObjectData> GetIDAndDatas();
	//! Returns a map of IDs and object pointers
	std::map<unsigned int, Object*> GetIDAndObjects();
	//! Deletes an object with associated ID
	void DeleteShape(unsigned int p_ID);
	//! returns the size of the shapes' map
	unsigned int GetSize();
	//! calls all the shapes update methods
	void UpdateShapes();
	//! Draws the shapes
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	//! Signal for creation of shapes
	Signal<unsigned int> OnCreated;
};