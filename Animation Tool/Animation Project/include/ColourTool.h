#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include "ColourPanel.h"

//////////////////////////////////
class ColourTool : public  ITool {
private:
	//sf::Shape* hello;
	ColourPanel* m_pColourPanel;
public:
	ColourTool(InteractionPtrs * p_pSP);
	~ColourTool();
	void Update(float p_DeltaTime) override;
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	void OnMouseMove(sf::Vector2i p_MouseWindowPos, sf::Vector2f p_MouseWorldPos) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};