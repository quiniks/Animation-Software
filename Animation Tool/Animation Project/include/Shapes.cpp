#include "Shapes.h"

unsigned int Shapes::FindEmptyID(std::vector<unsigned int> p_InUseIDs)
{
	std::sort(p_InUseIDs.begin(), p_InUseIDs.end());
	unsigned int l_Next = 0;
	for (std::vector<unsigned int>::iterator l_Itr = p_InUseIDs.begin(); l_Itr != p_InUseIDs.end(); ++l_Itr) {
		if (*l_Itr != l_Next) {
			return l_Next;
		}
		++l_Next;
	}
	return l_Next;
}

std::pair<unsigned int, Object*> Shapes::NewShape(Object p_NewObject)
{
	
	std::vector<unsigned int> l_InUseIDs;
	for (std::pair<unsigned int, Object> l_Pair : m_Shapes) {
		l_InUseIDs.push_back(l_Pair.first);
	}
	unsigned int l_ID = FindEmptyID(l_InUseIDs);
	m_Shapes.emplace(l_ID, p_NewObject);
	OnCreated.Notify(l_ID);

	return std::pair<unsigned int, Object*>(l_ID, &m_Shapes.at(l_ID));
}

Object & Shapes::FindShape(unsigned int p_ID)
{
	if (m_Shapes.find(p_ID) != m_Shapes.end()) {
		return m_Shapes.at(p_ID);
	}
	std::cout << "Shape " << p_ID << " not found." << std::endl;
}

std::vector<Object*> Shapes::GetObjects()
{
	std::vector<Object*> l_Objects;
	for (std::map<unsigned int, Object>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it) {
		l_Objects.push_back(&it->second);
	}
	return l_Objects;
}

std::map<unsigned int, ObjectData> Shapes::GetIDAndDatas()
{
	std::map<unsigned int, ObjectData> l_Data;
	for (std::map<unsigned int, Object>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it) {
		l_Data.emplace(it->first, it->second.GetObjectData());
	}
	return l_Data;
}

std::map<unsigned int, Object*> Shapes::GetIDAndObjects()
{
	std::map<unsigned int, Object*> l_Data;
	for (std::map<unsigned int, Object>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); ++it) {
		l_Data.emplace(it->first, &it->second);
	}
	return l_Data;
}

void Shapes::DeleteShape(unsigned int p_ID)
{
	m_Shapes.erase(p_ID);
}

unsigned int Shapes::GetSize()
{
	return m_Shapes.size();
}

void Shapes::UpdateShapes()
{
	for (auto& l_Pair : m_Shapes) {
		l_Pair.second.UpdateShape();
	}
}


void Shapes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (std::pair<unsigned int, Object> l_Pair : m_Shapes) {
		target.draw(l_Pair.second);
	}
}
