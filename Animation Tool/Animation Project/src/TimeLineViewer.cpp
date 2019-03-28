#include "..\include\TimeLineViewer.h"

TimeLineViewer::TimeLineViewer(sf::Vector2f p_Pos, sf::Vector2f p_Size)
{
	std::function<void(sf::Vector2i)> test1 = std::bind(&TimeLineViewer::OnMouseMove, this, std::placeholders::_1);
	std::function<void(bool)> test2 = std::bind(&TimeLineViewer::OnMouseClick, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("MouseMoved", test1);
	EventHandlerInstance.Connect2("LMB", test2);
	EventHandlerInstance.Register2("FrameSliderMoved", &FrameSliderMoved);

	m_TimeLineFrame.setPosition(p_Pos);
	m_TimeLineFrame.setSize(p_Size);
	m_TimeLineFrame.setFillColor(sf::Color(255, 255, 255, 190));

	m_SliderBar.setPosition(sf::Vector2f(p_Pos.x, p_Pos.y + m_TimeLineFrame.getSize().y));
	m_SliderBar.setSize(sf::Vector2f(p_Size.x, 15.f));
	m_SliderBar.setFillColor(sf::Color(120, 120, 120, 190));

	m_SliderHandle.setPosition(sf::Vector2f(p_Pos.x, p_Pos.y + m_TimeLineFrame.getSize().y));
	m_SliderHandle.setSize(sf::Vector2f(60.f, 15.f));
	m_SliderHandle.setFillColor(sf::Color(140, 140, 140, 255));
	m_SliderHandle.setOutlineColor(sf::Color(90, 90, 90, 190));
	m_SliderHandle.setOutlineThickness(-1);

	m_CurrentFrameSlider.setPosition(m_TimeLineFrame.getPosition());
	m_CurrentFrameSlider.setSize(sf::Vector2f(5.f, m_TimeLineFrame.getSize().y));
	m_CurrentFrameSlider.setFillColor(sf::Color::Red);
}

void TimeLineViewer::SetTotalFrames(unsigned int p_NumberOfFrames)
{
	m_TotalFrames = p_NumberOfFrames;
	float l_FrameRatio = (float)m_VisibleFrames / m_TotalFrames;
	m_SliderHandle.setSize(sf::Vector2f(l_FrameRatio * m_SliderBar.getSize().x, m_SliderHandle.getSize().y));
	//////////////////////
	std::vector<sf::RectangleShape> l_FrameBoxes;
	l_FrameBoxes.clear();
	float l_FrameWidth = m_TimeLineFrame.getSize().x / m_VisibleFrames;
	m_FrameWidth = l_FrameWidth;
	for (int i = 0; i < p_NumberOfFrames; i++) {
		sf::RectangleShape l_NewFrame;
		l_NewFrame.setPosition(m_TimeLineFrame.getPosition() + sf::Vector2f((i * l_FrameWidth), 0.f));
		l_NewFrame.setSize(sf::Vector2f(l_FrameWidth, m_TimeLineFrame.getSize().y));
		if (i % 2) {
			l_NewFrame.setFillColor(sf::Color(120, 120, 120, 190));
		}
		else {
			l_NewFrame.setFillColor(sf::Color(100, 100, 100, 190));
		}
		l_FrameBoxes.push_back(l_NewFrame);
	}
	float l_TotalFramesLength = l_FrameBoxes.at(0).getSize().x * l_FrameBoxes.size();
	/////////////////////
	sf::RenderTexture l_RenderTexture;
	l_RenderTexture.create(l_TotalFramesLength, m_TimeLineFrame.getSize().y);
	for (const sf::RectangleShape& l_FrameBox : l_FrameBoxes) {
		l_RenderTexture.draw(l_FrameBox);
	}
	l_RenderTexture.display();
	m_TimeLineBg.setSize(sf::Vector2f(l_TotalFramesLength, m_TimeLineFrame.getSize().y));
	m_TimeLineBgTex = new sf::Texture(l_RenderTexture.getTexture());
	m_TimeLineBg.setTexture(m_TimeLineBgTex);
	//////////////////////
	l_RenderTexture.create(m_TimeLineFrame.getSize().x, m_TimeLineFrame.getSize().y);
	l_RenderTexture.draw(m_TimeLineBg);
	l_RenderTexture.display();
	m_TimeLineTex = new sf::Texture(l_RenderTexture.getTexture());
	m_TimeLineFrame.setTexture(m_TimeLineTex);
}

void TimeLineViewer::OnMouseClick(bool p_State)
{
	if (m_IsOverSliderHandle and p_State) {
		m_IsHandleActive = true;
		m_Offset = m_InitialMouseX - m_SliderHandle.getPosition().x;
	}
	else if (m_IsOverSliderBar and p_State) {
		m_IsHandleActive = true;
		m_Offset = m_SliderHandle.getSize().x/2.f;
	}
	else if (m_IsOverCurrentSlider and p_State) {
		m_IsCurrentSliderActive = true;
	}
	else if (!p_State) {
		m_IsCurrentSliderActive = false;
		m_IsHandleActive = false;
	}
}

void TimeLineViewer::OnMouseMove(sf::Vector2i p_Pos)
{
	if (m_SliderHandle.getGlobalBounds().contains((sf::Vector2f)(p_Pos))) {
		m_IsOverSliderHandle = true;
		m_InitialMouseX = p_Pos.x;
		m_SliderHandle.setFillColor(sf::Color(110, 110, 110, 255));
	}
	else {
		m_IsOverSliderHandle = false;
		m_SliderHandle.setFillColor(sf::Color(140, 140, 140, 255));
	}

	if (m_SliderBar.getGlobalBounds().contains((sf::Vector2f)(p_Pos))) {
		m_IsOverSliderBar = true;
	}
	else {
		m_IsOverSliderBar = false;
	}

	if (m_CurrentFrameSlider.getGlobalBounds().contains((sf::Vector2f)(p_Pos))) {
		m_IsOverCurrentSlider = true;
	}
	else {
		m_IsOverCurrentSlider = false;
	}

	if (m_IsHandleActive) {
		m_SliderHandle.setFillColor(sf::Color(110, 110, 110, 255));
		m_SliderHandle.setPosition(sf::Vector2f(p_Pos.x - m_Offset, m_SliderHandle.getPosition().y));

		if (m_SliderHandle.getPosition().x < m_SliderBar.getPosition().x) {
			m_SliderHandle.setPosition(sf::Vector2f(m_SliderBar.getPosition().x, m_SliderHandle.getPosition().y));
		}
		else if (m_SliderHandle.getPosition().x + m_SliderHandle.getSize().x > m_SliderBar.getPosition().x + m_SliderBar.getSize().x) {
			m_SliderHandle.setPosition(sf::Vector2f((m_SliderBar.getPosition().x + m_SliderBar.getSize().x) - m_SliderHandle.getSize().x, m_SliderHandle.getPosition().y));
		}

		float l_Progress = (m_SliderHandle.getPosition().x - m_SliderBar.getPosition().x) / m_SliderBar.getSize().x;
		m_CurrentFrameSlider.setPosition(sf::Vector2f((m_TimeLineBg.getSize().x * -l_Progress) + (m_CurrentFrameSlider.getPosition().x - m_TimeLineBg.getPosition().x), m_CurrentFrameSlider.getPosition().y));
		m_TimeLineBg.setPosition(sf::Vector2f(m_TimeLineBg.getSize().x * -l_Progress, m_TimeLineBg.getPosition().y));
	}
	else if (m_IsCurrentSliderActive) {
		m_CurrentFrameSlider.setPosition(sf::Vector2f(p_Pos.x, m_CurrentFrameSlider.getPosition().y));
		if (m_CurrentFrameSlider.getPosition().x < m_TimeLineBg.getPosition().x) {
			m_CurrentFrameSlider.setPosition(sf::Vector2f(m_TimeLineBg.getPosition().x, m_CurrentFrameSlider.getPosition().y));
		}
		else if (m_CurrentFrameSlider.getPosition().x + m_CurrentFrameSlider.getSize().x > m_TimeLineBg.getPosition().x + m_TimeLineBg.getSize().x) {
			m_CurrentFrameSlider.setPosition(sf::Vector2f((m_TimeLineBg.getPosition().x + m_TimeLineBg.getSize().x) - m_CurrentFrameSlider.getSize().x, m_CurrentFrameSlider.getPosition().y));
		}

		unsigned int l_CurrentFrame = (m_CurrentFrameSlider.getPosition().x - m_TimeLineBg.getPosition().x) / m_FrameWidth;
		FrameSliderMoved.Notify(l_CurrentFrame);
	}
}

void TimeLineViewer::Update()
{
	sf::RenderTexture l_RenderTexture;
	l_RenderTexture.create(m_TimeLineFrame.getSize().x, m_TimeLineFrame.getSize().y);
	l_RenderTexture.draw(m_TimeLineBg);
	l_RenderTexture.draw(m_CurrentFrameSlider);
	l_RenderTexture.display();
	delete m_TimeLineTex;
	m_TimeLineTex = new sf::Texture(l_RenderTexture.getTexture());
	m_TimeLineFrame.setTexture(m_TimeLineTex);
}


void TimeLineViewer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_TimeLineFrame);
	if (m_TotalFrames > m_VisibleFrames) {
		target.draw(m_SliderBar);
		target.draw(m_SliderHandle);
	}
}
