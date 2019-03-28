#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "InteractionPtrs.h"
#include <Camera.h>
#include <EventHandler.h>


class ITool : public sf::Drawable, public HasInteractionPtrs
{
private:
	
protected:
	ITool(InteractionPtrs * p_pSP) : HasInteractionPtrs(p_pSP) {
		
	};
	
	sf::Vector2f m_MouseCanvasPos;
	sf::Vector2i m_MouseWindowPos;
public:
	virtual void Update(float p_DeltaTime) = 0;
	virtual void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) {}
	virtual void OnMouseMove(sf::Vector2i p_MouseWindowPos, sf::Vector2f p_MouseCanvasPos) {
		m_MouseCanvasPos = p_MouseCanvasPos;
		m_MouseWindowPos = p_MouseWindowPos;
	}
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const {};
	bool m_Active = false;
};

