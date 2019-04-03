#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include <Object.h>
#include "Shapes.h"

class Camera;
//! Interaction pointers struct
struct InteractionPtrs {
	std::vector<Object*>* m_pObjects;
	//! shapes container used to create and interact with shapes
	Shapes* m_Shapes;
	//! pointer to the window
	sf::RenderWindow* m_pWindow;
	//! pointer to the camera view
	Camera* m_pCamera;
	//! interaction pointers constructor
	InteractionPtrs(std::vector<Object*>* p_pObjects, Shapes* p_Shapes, sf::RenderWindow* p_pWindow, Camera* p_pCamera) : m_pObjects(p_pObjects), m_Shapes(p_Shapes), m_pWindow(p_pWindow), m_pCamera(p_pCamera) {};
};
/**
* @class HasInteractionPtrs
* @brief inherited by classes that need to used the interaction pointers
*/
class HasInteractionPtrs {
private:
	//! Interaction pointers pointer
	InteractionPtrs * m_pIP = nullptr;
protected:
	//! constructor
	HasInteractionPtrs(InteractionPtrs * p_pSP) : m_pIP(p_pSP) {};
public:
	//! Setter for m_pIP
	void setSubsystemPointers(InteractionPtrs * p_pSP) { m_pIP = p_pSP; }
	//! Returns the interaction pointer
	InteractionPtrs * getSubsystemPointers() { return m_pIP; }
	inline std::vector<Object*> * getObjects() { return m_pIP->m_pObjects; }
	//! Returns a pointer to the shapes container
	inline Shapes* getShapes() { return m_pIP->m_Shapes; }
	//! Returns a pointer to the window
	inline sf::RenderWindow * getWindow() { return m_pIP->m_pWindow; }
	//! Returns a pointer to the camera
	inline Camera * getCamera() { return m_pIP->m_pCamera; }
};