#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "InteractionPtrs.h"
#include <Camera.h>
#include <EventHandler.h>

/**
* @class ITool
* @brief handles generic methods that tools might need to use
*/
class ITool : public sf::Drawable, public HasInteractionPtrs
{
private:
	
protected:
	//! Constructor handles the inraction pointer giving it to the constructor of HasInteractionPtrs
	ITool(InteractionPtrs * p_pSP) : HasInteractionPtrs(p_pSP) {
		
	};
	//! The mouse position on the canvas
	sf::Vector2f m_MouseCanvasPos;
	//! The mouse position on the window
	sf::Vector2i m_MouseWindowPos;
public:
	//! Update method
	virtual void Update(float p_DeltaTime) = 0;
	//! Callback for mouse click events
	virtual void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) {}
	//! callback for mouse move events
	virtual void OnMouseMove(sf::Vector2i p_MouseWindowPos, sf::Vector2f p_MouseCanvasPos) {
		m_MouseCanvasPos = p_MouseCanvasPos;
		m_MouseWindowPos = p_MouseWindowPos;
	}
	//! draw method
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const {};
	//! Is the tool active
	bool m_Active = false;
};

