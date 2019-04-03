#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Canvas.h>
#include "ITool.h"
#include <Enums.h>
#include <cmath>
#include "Shapes.h"
/**
* @class TransformTool
* @brief Handles the interaction of transforming an object
*/
class TransformTool : public  ITool {
private:
	//! The currently selectecd object
	Object* m_pSelectedObject = nullptr;
	//! The ID of the selected object
	unsigned int m_IDOfSelectedObject;
	//! Is a scale operation being preformed
	bool m_bScaling = false;
	//! Is a translation operation being preformed 
	bool m_bTranslating = false;
	//! Is a rotation operation being preformed
	bool m_bRotating = false;
	//! Is a translation of the origin being performed
	bool m_bMoveingOrigin = false;
	//! Are the transform handles active (visible)
	bool m_HandlesActive = false;
	//! Method for creationg the transform handles
	void CreateFrame();
	//! Method for setting the transform handles
	void SetFrame();
	//! Method for removing the transform handles
	void RemoveFrame();
	//! Number of scale handles
	const int m_iHandleNum = 8;
	//! Array of circle shapes that make of the scale handles
	sf::CircleShape* m_ScaleHandles[8];
	//! The currently selected handle
	int m_SelectedHandle;
	//! The circle that makes the origin handle
	sf::CircleShape* m_OriginHandle;
	//! The circle that makes the rotation handle
	sf::CircleShape* m_RotateHandle;
	//! The mouses initial position, used during transforms
	sf::Vector2f m_MouseInitialPos;
	//! The shapes initial position, used during transforms
	sf::Vector2f m_ShapeInitialPos;
	//! The shapes initial rotation, used during rotations
	float m_ShapeInitialRot;
	//! Conversion function to convert from canvas coordinates to window position
	sf::Vector2i ToWindow(sf::Vector2f p_Pos);
	//! Conversion function to convert from window position to canvas coordinates
	sf::Vector2f ToCanvas(sf::Vector2i p_Pos);
	//! "Middle of" calculates the centre point between two points
	sf::Vector2f MiddleOf(sf::Vector2f p_Pos1, sf::Vector2f p_Pos2);
	//! The default cursor
	sf::Cursor m_DefaultCursor;
	//! The move cursor
	sf::Cursor m_MoveCursor;
	//! The hand cursior
	sf::Cursor m_HandCursor;
	//! The horizontal move cursor
	sf::Cursor m_HoriCursor;
	//! The vertical move cursor
	sf::Cursor m_VertCursor;
	//! The 1st diagonal cursor
	sf::Cursor m_Diag1Cursor;
	//! The 2nd diagonal cursor
	sf::Cursor m_Diag2Cursor;
	//! The signal for a transform ending
	Signal<unsigned int> OnTransformEnd;
public:
	//! Constructor that takes the interaction pointer
	TransformTool(InteractionPtrs * p_pSP);
	~TransformTool();
	//! Update method
	void Update(float p_DeltaTime) override;
	//! Callback for mouse click event
	void OnMouseClick(sf::Mouse::Button p_Button, bool p_bState) override;
	//! Draw method for drawing all the handles
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};