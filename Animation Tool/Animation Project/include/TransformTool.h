#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include <cmath>
#include "Shapes.h"
//////////////////////////

//////////////////////////////////
class TransformTool : public  ITool {
private:
	Object* m_pSelectedObject = nullptr;
	unsigned int m_IDOfSelectedObject;
	bool m_bScaling = false;
	bool m_bTranslating = false;
	bool m_bRotating = false;
	bool m_bMoveingOrigin = false;
	bool m_HandlesActive = false;

	void CreateFrame();
	void SetFrame();
	void RemoveFrame();

	const int m_iHandleNum = 8;
	sf::CircleShape* m_ScaleHandles[8];
	int m_SelectedHandle;
	sf::CircleShape* m_OriginHandle;
	sf::CircleShape* m_RotateHandle;

	sf::Vector2f m_MouseInitialPos;
	sf::Vector2f m_ShapeInitialPos;
	float m_ShapeInitialRot;

	sf::Vector2i ToWindow(sf::Vector2f p_Pos);
	sf::Vector2f ToCanvas(sf::Vector2i p_Pos);
	sf::Vector2f MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2);

	sf::Cursor m_DefaultCursor;
	sf::Cursor m_MoveCursor;
	sf::Cursor m_HandCursor;
	sf::Cursor m_HoriCursor;
	sf::Cursor m_VertCursor;
	sf::Cursor m_Diag1Cursor;
	sf::Cursor m_Diag2Cursor;

	Signal<unsigned int> OnTransformEnd;
public:
	TransformTool(InteractionPtrs * p_pSP);
	~TransformTool();
	void Update(float p_DeltaTime) override;
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};