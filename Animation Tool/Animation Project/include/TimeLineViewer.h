#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "EventHandler.h"

class TimeLineViewer : public sf::Drawable {
private:
	unsigned int m_VisibleFrames = 10;
	unsigned int m_TotalFrames = 0;
	//std::vector<sf::RectangleShape> m_FrameBoxes;
	sf::Texture* m_TimeLineBgTex;
	sf::RectangleShape m_TimeLineBg;
	sf::Texture* m_TimeLineTex;

	sf::RectangleShape m_TimeLineFrame;
	sf::RectangleShape m_CurrentFrameSlider;

	sf::RectangleShape m_SliderBar;
	sf::RectangleShape m_SliderHandle;
	bool m_IsOverSliderHandle = false;
	bool m_IsOverCurrentSlider = false;
	bool m_IsOverSliderBar = false;
	bool m_IsHandleActive = false;
	bool m_IsCurrentSliderActive = false;

	float m_Offset;
	float m_InitialMouseX;

	Signal<unsigned int> FrameSliderMoved;
	float m_FrameWidth;
public:
	TimeLineViewer(sf::Vector2f p_Pos, sf::Vector2f p_Size);
	void SetTotalFrames(unsigned int p_NumberOfFrames);
	////////
	void OnMouseClick(bool p_State);
	void OnMouseMove(sf::Vector2i p_Pos);
	////////
	void Update();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};