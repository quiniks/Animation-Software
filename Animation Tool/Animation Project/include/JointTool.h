#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ITool.h"
#include <Enums.h>
#include "Object.h"
//////////////////////////

//////////////////////////////////
class JointTool : public  ITool {
private:
	bool m_bSelecting = false;
	Object* m_ParentObject = nullptr;
	Object* m_ChildObject = nullptr;

	sf::Vector2i ToWindow(sf::Vector2f p_Pos);

	sf::VertexArray m_Line;
public:
	JointTool(InteractionPtrs * p_pSP);
	~JointTool();
	void Update(float p_DeltaTime) override;
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};
