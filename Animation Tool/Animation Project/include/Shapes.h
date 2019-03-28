#pragma once
#include "Object.h"
#include "Signal.h"

class Shapes : public sf::Drawable {
private:
	std::map<unsigned int, Object> m_Shapes;
	std::vector<Object> m_Objects2;
	unsigned int FindEmptyID(std::vector<unsigned int> p_InUseIDs);
public:
	std::pair<unsigned int, Object*> NewShape(Object p_NewObject);
	Object& FindShape(unsigned int p_ID);
	std::vector<Object*> GetObjects();
	std::map<unsigned int, ObjectData> GetIDAndDatas();
	std::map<unsigned int, Object*> GetIDAndObjects();
	void DeleteShape(unsigned int p_ID);
	unsigned int GetSize();
	void UpdateShapes();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	Signal<unsigned int> OnCreated;
};