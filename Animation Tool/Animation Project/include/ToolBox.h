#pragma once

#include <SFML/Graphics.hpp>

#include "InteractionPtrs.h"
#include <ShapeTool.h>
#include <TransformTool.h>
#include <ColourTool.h>
#include "JointTool.h"

/**
* @class ToolBox
* @brief Handles the creation and switching of tools
*/
class ToolBox : public sf::Drawable, public HasInteractionPtrs
{
private:
	//! map of polymorphic ITool pointers and their associated name keys
	std::map<std::string, ITool*> m_Tools;
	//! the currrently selected tool
	ITool* m_pSelectedTool = nullptr;
public:
	//! Constructor that takes "iteractionPtrs" which contains most of the useful classes that tools need to interact with
	ToolBox(InteractionPtrs * p_pSP);
	~ToolBox();
	//! Update function
	void Update(float p_DeltaTime);
	//! OnMouseClick callback function, registered to the input handlers mouse click signal
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_State);
	//! OnMouseMove callback function, registered to the input handlers mouse move extra signal
	void OnMouseMove(sf::Vector2i p_WindowPos, sf::Vector2f p_WorldPos);
	//! Set the active state of the current tool
	void SetActive(bool p_bActive);
	//! Set the draw tool as the currently selected tool
	void SelectDraw();
	//! Set the transform tool as the currently selected tool
	void SelectTransform();
	//! Set the colour tool as the currently selected tool
	void SelectColour();
	//! Set the joint tool as the currently selected tool
	void SelectJoint();
	//! Draw anything that the currently selected tool needs drawing
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};