#pragma once
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "EventHandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "AnimStructs.h"

//#include "KeyframeManager.h"

struct FrameSlot {
	bool m_Active = false;
	sf::RectangleShape m_Rect;
	unsigned int m_KeyFrame;
};

struct ShapeSlot {
	bool m_Active = false;
	sf::RectangleShape m_Rect;
	unsigned int m_ID;
	std::vector<FrameSlot> m_FrameSlots;
	sf::Text m_Text;
};

using namespace boost::container;

class TimeLine : public sf::Drawable {
private:
	sf::Vector2f m_Pos;
	sf::Vector2f m_Size;
	sf::RectangleShape m_Box;
	sf::RectangleShape m_HoriBar;
	sf::RectangleShape m_HoriHandle;
	sf::RectangleShape m_VertiBar;
	sf::RectangleShape m_VertiHandle;
	sf::RectangleShape m_KeySlider;
	sf::VertexArray m_Line;
	std::vector<ShapeSlot> m_Slots;

	const flat_set<ShapeKeyFrames, CompareId>* m_ShapesAndKeysPtr;
	unsigned int m_TotalFrames;
	unsigned int m_CurrentFrame = 0;
	float m_FramePeriod;

	bool m_VertiHandleVisible = false;
	bool m_HoriHandleVisible = true;
	bool m_KeySliderVisible = true;

	sf::Vector2f m_MouseHandleOffset;

	bool m_IsOverVertiHandle = false;
	bool m_UsingVertiHandle = false;
	float m_VertiHandleScalar;

	bool m_IsOverHoriHandle = false;
	bool m_UsingHoriHandle = false;

	bool m_IsOverKeySlider = false;
	bool m_IsUsingKeySlider = false;

	unsigned int m_FrameIndex = 0;
	unsigned int m_ShapeIndex = 0;

	sf::Font m_Font;
	std::vector<sf::Text> m_FrameTimes;

	float m_ShapeBoxWidth = 100;
	float m_BarWidth = 15;

	const int m_FrameSlots = 20;
	const int m_ShapeSlots = 5;
	unsigned int m_Index = 0;
	unsigned int m_TotalShapes;

	float m_FrameSlotWidth;

	sf::Vector2f m_MousePos;

	void UpdateFrameSlots();
	void SetUpTimes();
	void UpdateTimes();
public:
	TimeLine(sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_FrameRate, unsigned int p_TotalFrames);
	void Update(const flat_set<ShapeKeyFrames, CompareId>& p_ShapesAndKeys, FrameState p_FrameState);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void OnMouseClick(bool p_State);
	void OnMouseMove(sf::Vector2i p_Pos);

	Signal<unsigned int> SetKeyFrame;
};