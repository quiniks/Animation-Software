#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include "ColourPanel.h"
/**
* @class ColourTool
* @brief Used as a simple temporary means to recolour shapes
*/
class ColourTool : public  ITool {
private:
	//! pointer to a colour panel that determines the colour to be used
	ColourPanel* m_pColourPanel;
public:
	//! constructor that takes interactionPtrs that contains useful classes needed to recolour shapes
	ColourTool(InteractionPtrs * p_pSP);
	~ColourTool();
	void Update(float p_DeltaTime) override;
	//! Callback method that is notified on a mouse button event
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	//! Callback method that is notified on a mouse move extra event
	void OnMouseMove(sf::Vector2i p_MouseWindowPos, sf::Vector2f p_MouseWorldPos) override;
	//! draw method that draws the colour panel
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};