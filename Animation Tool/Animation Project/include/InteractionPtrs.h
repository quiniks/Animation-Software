#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include <Object.h>
#include "Shapes.h"

class Camera;

struct InteractionPtrs {
	std::vector<Object*>* m_pObjects;
	Shapes* m_Shapes;
	sf::RenderWindow* m_pWindow;
	Camera* m_pCamera;

	InteractionPtrs(std::vector<Object*>* p_pObjects, Shapes* p_Shapes, sf::RenderWindow* p_pWindow, Camera* p_pCamera) : m_pObjects(p_pObjects), m_Shapes(p_Shapes), m_pWindow(p_pWindow), m_pCamera(p_pCamera) {};
};

class HasInteractionPtrs {
private:
	InteractionPtrs * m_pIP = nullptr;
protected:
	HasInteractionPtrs(InteractionPtrs * p_pSP) : m_pIP(p_pSP) {};
public:
	void setSubsystemPointers(InteractionPtrs * p_pSP) { m_pIP = p_pSP; }
	InteractionPtrs * getSubsystemPointers() { return m_pIP; }

	inline std::vector<Object*> * getObjects() { return m_pIP->m_pObjects; }
	inline Shapes* getShapes() { return m_pIP->m_Shapes; }
	inline sf::RenderWindow * getWindow() { return m_pIP->m_pWindow; }
	inline Camera * getCamera() { return m_pIP->m_pCamera; }
};