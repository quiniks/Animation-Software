#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ITool.h"
#include <Enums.h>
#include "Object.h"

/**
* @class JointTool
* @brief Handles the linking joints between objest
*/
class JointTool : public  ITool {
private:
	//! Is a joint waiting for a selection to be made
	bool m_bSelecting = false;
	//! Pointer to the parent object
	Object* m_ParentObject = nullptr;
	//! Pointer to the child object
	Object* m_ChildObject = nullptr;
	//! Conversion function for the mouse position
	sf::Vector2i ToWindow(sf::Vector2f p_Pos);
	//! Visual line for when a joint is being made
	sf::VertexArray m_Line;
public:
	//! Constructor
	JointTool(InteractionPtrs * p_pSP);
	~JointTool();
	//! Updates the joint line during a selection
	void Update(float p_DeltaTime) override;
	//! callback for mouse click events used to determine the parent and child of a joint
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	//! Draw the joint line
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};
