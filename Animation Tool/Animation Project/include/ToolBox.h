#pragma once

#include <SFML/Graphics.hpp>

#include "InteractionPtrs.h"
#include <ShapeTool.h>
#include <TransformTool.h>
#include <ColourTool.h>
#include "JointTool.h"

class ToolBox : public sf::Drawable, public HasInteractionPtrs
{
private:
	std::map<std::string, ITool*> m_Tools;
	ITool* m_pSelectedTool = nullptr;
public:
	ToolBox(InteractionPtrs * p_pSP);
	~ToolBox();
	void Update(float p_DeltaTime);
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_State);
	void OnMouseMove(sf::Vector2i p_WindowPos, sf::Vector2f p_WorldPos);
	void SetActive(bool p_bActive);
	void SelectDraw();
	void SelectTransform();
	void SelectColour();
	void SelectJoint();

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};