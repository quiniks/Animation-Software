#pragma once
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "EventHandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "AnimStructs.h"

//! Struct that holds data for frame slots
struct FrameSlot {
	bool m_Active = false;
	sf::RectangleShape m_Rect;
	unsigned int m_KeyFrame;
};

//! Struct that holds data for shape slots and their corrisponding frame slots
struct ShapeSlot {
	bool m_Active = false;
	sf::RectangleShape m_Rect;
	unsigned int m_ID;
	std::vector<FrameSlot> m_FrameSlots;
	sf::Text m_Text;
};

using namespace boost::container;
/**
 * @class Time-line
 * @brief Creates and manages a user interface to deal with "ShapeKeyFrame" data
 */
class TimeLine : public sf::Drawable {
private:
	//! Position of time line
	sf::Vector2f m_Pos;
	//! Size of the time line UI
	sf::Vector2f m_Size;
	//! Main rectangle 
	sf::RectangleShape m_Box;
	//! Background rectangle for horizontal slider bar
	sf::RectangleShape m_HoriBar;
	//! Handle rectangle for the horizontal slider bar
	sf::RectangleShape m_HoriHandle;
	//! Background rectangle for the vertical slider bar
	sf::RectangleShape m_VertiBar;
	//! Handle rectangle for the vertical slider bar
	sf::RectangleShape m_VertiHandle;
	//! Current keyframe slider rectangle
	sf::RectangleShape m_KeySlider;
	//! Line to seperate shape slots from frame slots
	sf::VertexArray m_Line;
	//! Vector containing the shape slots that in turn hold the frame slots
	std::vector<ShapeSlot> m_Slots;
	//! pointer to the ordered shape data
	const flat_set<ShapeKeyFrames, CompareId>* m_ShapesAndKeysPtr;
	//! Total frames
	unsigned int m_TotalFrames;
	//! The current frame number
	unsigned int m_CurrentFrame = 0;
	//! The time between frames
	float m_FramePeriod;
	//! Is the vertical slider bar visible boolean
	bool m_VertiHandleVisible = false;
	//! Is the horizontal slider bar visible boolean
	bool m_HoriHandleVisible = true;
	//! Is the current frame slider visible boolean
	bool m_KeySliderVisible = true;
	//! The mouse's offset from another position i.e. the slider handles
	sf::Vector2f m_MouseHandleOffset;
	//! Is the mouse over the vertical slider handle
	bool m_IsOverVertiHandle = false;
	//! Is the vertical slider being used
	bool m_UsingVertiHandle = false;
	//! Scalar for the vertical slider handle
	float m_VertiHandleScalar;
	//! Is the the mouse over the horizontal handle
	bool m_IsOverHoriHandle = false;
	//! is the horizontal handle being used
	bool m_UsingHoriHandle = false;
	//! is the mouse over the current frame slider
	bool m_IsOverKeySlider = false;
	//! is the current frame slider being used
	bool m_IsUsingKeySlider = false;
	//! Frame index is the offset to the first frame slot
	unsigned int m_FrameIndex = 0;
	//! Shape index is the offset to the first shape slot
	unsigned int m_ShapeIndex = 0;
	//! Font used by the time line UI
	sf::Font m_Font;
	//! Vector of text for frame times along the time line
	std::vector<sf::Text> m_FrameTimes;
	//! width of the shape slot box
	float m_ShapeBoxWidth = 100;
	//! width of the slider bars
	float m_BarWidth = 15;
	//! number of visible frame slots
	const int m_FrameSlots = 20;
	//! number of shape slots
	const int m_ShapeSlots = 5;
	//! Not used
	unsigned int m_Index = 0;
	//! Total shapes
	unsigned int m_TotalShapes;
	//! Frame slot width
	float m_FrameSlotWidth;
	//! Mouse position
	sf::Vector2f m_MousePos;
	//! Update the frame slots data
	void UpdateFrameSlots();
	//! Sets up the frame times on the time line
	void SetUpTimes();
	//! Updates the frame times
	void UpdateTimes();
public:
	//! Constructor
	TimeLine(sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_FrameRate, unsigned int p_TotalFrames);
	//! Update the shape and frame slots with the keyframe data
	void Update(const flat_set<ShapeKeyFrames, CompareId>& p_ShapesAndKeys, FrameState p_FrameState);
	//! draw the the UI
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	//! callback for mouse click
	void OnMouseClick(bool p_State);
	//! callback for mouse move
	void OnMouseMove(sf::Vector2i p_Pos);
	//! Signal for keyframe being set
	Signal<unsigned int> SetKeyFrame;
};