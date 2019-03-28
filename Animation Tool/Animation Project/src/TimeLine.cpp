#include "..\include\TimeLine.h"

TimeLine::TimeLine(sf::Vector2f p_Pos, sf::Vector2f p_Size, unsigned int p_FrameRate, unsigned int p_TotalFrames)
{
	std::function<void(bool)> l_OnMouseClick = std::bind(&TimeLine::OnMouseClick, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("LMB", l_OnMouseClick);
	std::function<void(sf::Vector2i)> l_OnMouseMove = std::bind(&TimeLine::OnMouseMove, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("MouseMoved", l_OnMouseMove);

	m_Pos = p_Pos;
	m_Size = p_Size;

	m_Font.loadFromFile("assets/fonts/Roboto-Regular.ttf");

	m_FramePeriod = 1.f / p_FrameRate;
	m_TotalFrames = p_TotalFrames;
	float l_HoriHandleScalar = (float)m_FrameSlots / m_TotalFrames;

	m_VertiBar.setFillColor(sf::Color(50, 50, 50, 255));
	m_HoriBar.setFillColor(sf::Color(50, 50, 50, 255));

	m_Box.setPosition(p_Pos + sf::Vector2f(m_BarWidth, 0));
	m_Box.setSize(p_Size - sf::Vector2f(m_BarWidth, m_BarWidth));

	m_VertiBar.setPosition(p_Pos);
	m_VertiBar.setSize(sf::Vector2f(m_BarWidth, p_Size.y - m_BarWidth));
	m_VertiHandle.setPosition(p_Pos);
	m_VertiHandle.setSize(m_VertiBar.getSize());
	m_VertiHandle.setFillColor(sf::Color(200, 200, 200, 100));

	m_HoriBar.setPosition(sf::Vector2f(p_Pos.x + m_ShapeBoxWidth + m_BarWidth, p_Pos.y + p_Size.y - m_BarWidth));
	m_HoriBar.setSize(sf::Vector2f(p_Size.x - (m_BarWidth + m_ShapeBoxWidth), m_BarWidth));
	m_HoriHandle.setPosition(m_HoriBar.getPosition());
	m_HoriHandle.setSize(sf::Vector2f(m_HoriBar.getSize().x * l_HoriHandleScalar, m_HoriBar.getSize().y));
	m_HoriHandle.setFillColor(sf::Color(200, 200, 200, 100));

	float l_ShapeSlotHeight = (p_Size.y - m_BarWidth) / m_ShapeSlots;
	m_FrameSlotWidth = (p_Size.x - (m_BarWidth + m_ShapeBoxWidth)) / m_FrameSlots;

	m_Line = sf::VertexArray(sf::Lines, 2);
	m_Line[0].position = sf::Vector2f(p_Pos.x + m_BarWidth + m_ShapeBoxWidth, p_Pos.y);
	m_Line[1].position = sf::Vector2f(p_Pos.x + m_BarWidth + m_ShapeBoxWidth, (p_Pos.y + p_Size.y) - m_BarWidth);
	m_Line[0].color = sf::Color::Black;
	m_Line[1].color = sf::Color::Black;

	//Set up slots
	for (int i = 0; i < m_ShapeSlots; i++) {
		ShapeSlot l_ShapeSlot;
		l_ShapeSlot.m_Rect.setPosition(sf::Vector2f(p_Pos.x + m_BarWidth, p_Pos.y + l_ShapeSlotHeight * i));
		l_ShapeSlot.m_Rect.setSize(sf::Vector2f(m_ShapeBoxWidth, l_ShapeSlotHeight));
		l_ShapeSlot.m_Text.setFont(m_Font);
		l_ShapeSlot.m_Text.setCharacterSize(15);
		l_ShapeSlot.m_Text.setFillColor(sf::Color::Black);
		l_ShapeSlot.m_Text.setPosition(l_ShapeSlot.m_Rect.getPosition());
		//l_ShapeSlot.m_Text.setString("hello");
		l_ShapeSlot.m_Rect.setOutlineColor(sf::Color::Black);
		l_ShapeSlot.m_Rect.setOutlineThickness(-1);
		for (int j = 0; j < m_FrameSlots; j++) {
			FrameSlot l_FrameSlot;
			l_FrameSlot.m_Rect.setPosition(sf::Vector2f((p_Pos.x + m_BarWidth + m_ShapeBoxWidth) + (m_FrameSlotWidth * j), l_ShapeSlot.m_Rect.getPosition().y));
			l_FrameSlot.m_Rect.setSize(sf::Vector2f(m_FrameSlotWidth, l_ShapeSlotHeight));
			l_FrameSlot.m_Rect.setOutlineColor(sf::Color::Black);
			l_FrameSlot.m_Rect.setOutlineThickness(-1);
			l_ShapeSlot.m_FrameSlots.push_back(l_FrameSlot);
		}
		m_Slots.push_back(l_ShapeSlot);
	}

	//Set up times
	SetUpTimes();

	m_KeySlider.setOutlineColor(sf::Color::Red);
	m_KeySlider.setFillColor(sf::Color::Transparent);
	m_KeySlider.setOutlineThickness(2);
	m_KeySlider.setPosition(sf::Vector2f(p_Pos.x + m_BarWidth + m_ShapeBoxWidth, p_Pos.y));
	m_KeySlider.setSize(sf::Vector2f(m_FrameSlotWidth, p_Size.y - m_BarWidth));
}

void TimeLine::Update(const flat_set<ShapeKeyFrames, CompareId>& p_ShapesAndKeys, FrameState p_FrameState)
{
	m_ShapesAndKeysPtr = &p_ShapesAndKeys;
	//std::cout << "container sizes" << m_ShapesAndKeysPtr->begin()->m_KeyFrames2.size() << "/" << p_ShapesAndKeys.begin()->m_KeyFrames2.size() << std::endl;
	//std::cout << "container sizes" << m_ShapesAndKeysPtr->begin()->m_KeyFrames2 << "/" << p_ShapesAndKeys.begin()->m_KeyFrames2.size() << std::endl;
	m_TotalShapes = p_ShapesAndKeys.size();
	flat_set<ShapeKeyFrames>::const_iterator l_IDItr = p_ShapesAndKeys.begin();

	if (m_TotalShapes > m_ShapeSlots) {
		m_VertiHandleVisible = true;
		m_VertiHandleScalar = (float)m_ShapeSlots / m_TotalShapes;
		m_VertiHandle.setSize(sf::Vector2f(m_BarWidth, m_VertiBar.getSize().y * m_VertiHandleScalar));
	}

	if (p_FrameState == FrameState::Recorded) {
		for (int i = 0; i < m_ShapeSlots; i++) {
			if (l_IDItr != p_ShapesAndKeys.end()) {
				ShapeSlot& l_ShapeSlot = m_Slots.at(i);
				if (!l_ShapeSlot.m_Active) {
					unsigned int l_ID = l_IDItr->m_ID;
					l_ShapeSlot.m_Text.setString(std::to_string(l_ID));
					l_ShapeSlot.m_ID = l_ID;
					l_ShapeSlot.m_Active = true;
				}
				++l_IDItr;
			}
		}
		//iterate over frame slots
		//if frame slot is inactive and a keyframe number matchs the slot number + frameindex
		UpdateFrameSlots();
	}
	else if (p_FrameState == FrameState::Deleted) {

	}
	else if (p_FrameState == FrameState::Set) {

	}
}

void TimeLine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Box);
	target.draw(m_VertiBar);
	target.draw(m_HoriBar);
	for (const auto& l_ShapeSlots : m_Slots) {
		target.draw(l_ShapeSlots.m_Rect);
		target.draw(l_ShapeSlots.m_Text);
		for (const auto& l_FrameSlots : l_ShapeSlots.m_FrameSlots) {
			target.draw(l_FrameSlots.m_Rect);
		}
	}
	for (const auto& l_FrameTime : m_FrameTimes) {
		target.draw(l_FrameTime);
	}
	target.draw(m_Line);
	if (m_KeySliderVisible) {
		target.draw(m_KeySlider);
	}
	if (m_HoriHandleVisible) {
		target.draw(m_HoriHandle);
	}
	if (m_VertiHandleVisible) {
		target.draw(m_VertiHandle);
	}
}

void TimeLine::OnMouseClick(bool p_State)
{
	if (m_IsOverVertiHandle and p_State) {
		m_UsingVertiHandle = true;
		m_MouseHandleOffset = m_MousePos - m_VertiHandle.getPosition();
	}
	else {
		m_UsingVertiHandle = false;
	}

	if (m_IsOverKeySlider and p_State) {
		m_IsUsingKeySlider = true;
		m_MouseHandleOffset = m_MousePos - m_KeySlider.getPosition();
	}
	else {
		m_IsUsingKeySlider = false;
	}

	if (m_IsOverHoriHandle and p_State) {
		m_UsingHoriHandle = true;
		m_MouseHandleOffset = m_MousePos - m_HoriHandle.getPosition();
	}
	else {
		m_UsingHoriHandle = false;
	}

}

void TimeLine::OnMouseMove(sf::Vector2i p_Pos)
{
	m_MousePos = (sf::Vector2f)p_Pos;
	if (m_VertiHandle.getGlobalBounds().contains(m_MousePos)) {
		m_IsOverVertiHandle = true;
		m_VertiHandle.setFillColor(sf::Color(100, 100, 100, 255));
	}
	else {
		m_IsOverVertiHandle = false;
		m_VertiHandle.setFillColor(sf::Color(200, 200, 200, 100));
	}

	if (m_HoriHandle.getGlobalBounds().contains(m_MousePos)) {
		m_IsOverHoriHandle = true;
		m_HoriHandle.setFillColor(sf::Color(100, 100, 100, 255));
	}
	else {
		m_IsOverHoriHandle = false;
		m_HoriHandle.setFillColor(sf::Color(200, 200, 200, 100));
	}

	if (m_UsingVertiHandle) {
		m_VertiHandle.setPosition(sf::Vector2f(m_VertiHandle.getPosition().x, p_Pos.y - m_MouseHandleOffset.y));
		if (m_VertiHandle.getPosition().y < m_VertiBar.getPosition().y) {
			m_VertiHandle.setPosition(m_VertiBar.getPosition());
		}
		else if (m_VertiHandle.getPosition().y + m_VertiHandle.getSize().y > m_VertiBar.getPosition().y + m_VertiBar.getSize().y) {
			m_VertiHandle.setPosition(sf::Vector2f(m_VertiBar.getPosition().x, (m_VertiBar.getPosition().y + m_VertiBar.getSize().y) - m_VertiHandle.getSize().y));
		}

		float l_VertiHandleDisp = m_VertiHandle.getPosition().y - m_VertiBar.getPosition().y;
		float l_VertiHandleProgress = l_VertiHandleDisp / m_VertiBar.getSize().y;
		m_ShapeIndex = round(m_TotalShapes * l_VertiHandleProgress);
		//std::cout << m_TotalShapes << "/" << l_ShapeIndex << std::endl;
		
		flat_set<ShapeKeyFrames>::const_iterator l_IDItr = m_ShapeIndex + m_ShapesAndKeysPtr->begin() ;
		for (int i = 0; i < m_ShapeSlots; i++) {
			if (l_IDItr != m_ShapesAndKeysPtr->end()) {
				ShapeSlot& l_ShapeSlot = m_Slots.at(i);
				unsigned int l_ID = l_IDItr->m_ID;
				l_ShapeSlot.m_Text.setString(std::to_string(l_ID));
				l_ShapeSlot.m_ID = l_ID;
				++l_IDItr;
			}
		}
		UpdateFrameSlots();
	}

	if (m_UsingHoriHandle) {
		m_HoriHandle.setPosition(sf::Vector2f(p_Pos.x - m_MouseHandleOffset.x, m_HoriHandle.getPosition().y));
		if (m_HoriHandle.getPosition().x < m_HoriBar.getPosition().x) {
			m_HoriHandle.setPosition(m_HoriBar.getPosition());
		}
		else if (m_HoriHandle.getPosition().x + m_HoriHandle.getSize().x > m_HoriBar.getPosition().x + m_HoriBar.getSize().x) {
			m_HoriHandle.setPosition(sf::Vector2f((m_HoriBar.getPosition().x + m_HoriBar.getSize().x) - m_HoriHandle.getSize().x, m_HoriBar.getPosition().y));
		}

		float l_HoriHandleDisp = m_HoriHandle.getPosition().x - m_HoriBar.getPosition().x;
		float l_HoriHandleProgress = l_HoriHandleDisp / m_HoriBar.getSize().x;
		m_FrameIndex = round(m_TotalFrames * l_HoriHandleProgress);

		int l_KeySliderSlot = m_CurrentFrame - m_FrameIndex;
		if (l_KeySliderSlot >= 0 and l_KeySliderSlot < m_FrameSlots) {
			m_KeySliderVisible = true;
			float l_FrameBoxLeft = m_Box.getPosition().x + m_ShapeBoxWidth;
			float l_FrameBoxWidth = m_Box.getSize().x - m_ShapeBoxWidth;
			float l_KeySliderPos = l_FrameBoxLeft + (l_FrameBoxWidth * ((float)l_KeySliderSlot / m_FrameSlots));
			m_KeySlider.setPosition(sf::Vector2f(l_KeySliderPos, m_KeySlider.getPosition().y));
			//SetUpFrameSlots();
		}
		else {
			m_KeySliderVisible = false;
		}
		UpdateFrameSlots();
		UpdateTimes();
		
		//std::cout << m_TotalFrames << "/" << m_FrameIndex << "/" << l_KeySliderSlot << std::endl;
	}

	m_IsOverKeySlider = m_KeySlider.getGlobalBounds().contains(m_MousePos) and m_KeySliderVisible;
	if (m_IsUsingKeySlider) {
		m_KeySlider.setPosition(sf::Vector2f(p_Pos.x - m_MouseHandleOffset.x, m_KeySlider.getPosition().y));
		float l_FrameBoxWidth = m_Box.getSize().x - m_ShapeBoxWidth;
		float l_FrameBoxLeft = m_Box.getPosition().x + m_ShapeBoxWidth;
		float l_FrameBoxRight = l_FrameBoxLeft + l_FrameBoxWidth;
		float l_KeySliderY = m_KeySlider.getPosition().y;
		float l_KeySliderX = m_KeySlider.getPosition().x;
		if (l_KeySliderX < l_FrameBoxLeft) {
			m_KeySlider.setPosition(sf::Vector2f(l_FrameBoxLeft, l_KeySliderY));
		}
		else if (l_KeySliderX + m_KeySlider.getSize().x > l_FrameBoxRight) {
			m_KeySlider.setPosition(sf::Vector2f(l_FrameBoxRight - m_KeySlider.getSize().x, l_KeySliderY));
		}

		float l_KeySliderDisp = m_KeySlider.getPosition().x - l_FrameBoxLeft;
		float l_KeySliderProgress = l_KeySliderDisp / l_FrameBoxWidth;
		unsigned int l_KeySlotIndex = round(m_FrameSlots * l_KeySliderProgress);
		m_CurrentFrame = m_FrameIndex + l_KeySlotIndex;
		SetKeyFrame.Notify(m_CurrentFrame);
		//std::cout << l_KeySlotIndex << "/" << m_CurrentFrame << std::endl;
	}
}

void TimeLine::UpdateFrameSlots()
{
	std::cout << "---" << " ShapeIndex: " << m_ShapeIndex << " FrameIndex: " << m_FrameIndex << " Key: " << m_CurrentFrame << std::endl;

	for (auto& l_ShapeSlot : m_Slots) {
		for (auto& l_FrameSlot : l_ShapeSlot.m_FrameSlots) {
			l_FrameSlot.m_Rect.setFillColor(sf::Color::White);
		}
	}

	flat_set<ShapeKeyFrames>::const_iterator l_IDItr = m_ShapesAndKeysPtr->begin();
	unsigned int l_ShapeSlotCounter = 0;
	for (l_IDItr; l_IDItr != m_ShapesAndKeysPtr->end(); ++l_IDItr) {
		if (l_ShapeSlotCounter < m_ShapeSlots and l_IDItr->m_ID >= m_ShapeIndex and l_IDItr->m_ID < m_ShapeIndex + m_ShapeSlots) {
			ShapeSlot& l_ShapeSlot = m_Slots.at(l_ShapeSlotCounter);
			flat_set<KeyFrame>::const_iterator l_keyframes = l_IDItr->m_KeyFrames2.begin();
			for (l_keyframes; l_keyframes != l_IDItr->m_KeyFrames2.end(); ++l_keyframes) {
				if (l_keyframes->m_Frame >= m_FrameIndex and l_keyframes->m_Frame < m_FrameIndex + m_FrameSlots) {
					unsigned int l_FrameSlotNum = l_keyframes->m_Frame - m_FrameIndex;
					FrameSlot& l_FrameSlot = l_ShapeSlot.m_FrameSlots.at(l_FrameSlotNum);
					l_FrameSlot.m_Rect.setFillColor(sf::Color::Red);
					l_FrameSlot.m_KeyFrame = l_keyframes->m_Frame;
					l_FrameSlot.m_Active = true;
				}
				std::cout << " - keyframe: " << l_keyframes->m_Frame << std::endl;
			}
			l_ShapeSlotCounter++;
		}
	}
}

void TimeLine::SetUpTimes()
{
	for (int i = 0; i < m_FrameSlots / 2; i++) {
		sf::Text l_FrameTime;
		l_FrameTime.setFont(m_Font);
		l_FrameTime.setCharacterSize(12);
		l_FrameTime.setFillColor(sf::Color::Red);
		l_FrameTime.setPosition(sf::Vector2f(m_Pos.x + m_BarWidth + m_ShapeBoxWidth + (i * (m_FrameSlotWidth * 2)), m_Pos.y + (m_Size.y - m_BarWidth)));

		int l_Digits = 2;
		std::stringstream l_SS;
		l_SS << std::fixed;
		l_SS.precision(l_Digits);
		l_SS << (i * m_FramePeriod);

		l_FrameTime.setString(l_SS.str());

		m_FrameTimes.push_back(l_FrameTime);
	}
}

void TimeLine::UpdateTimes()
{
	int l_Digits = 2;
	for (int i = 0; i < m_FrameTimes.size(); i++) {
		std::stringstream l_SS;
		l_SS << std::fixed;
		l_SS.precision(l_Digits);
		l_SS << ((m_FrameIndex * m_FramePeriod) + (i * m_FramePeriod));

		m_FrameTimes.at(i).setString(l_SS.str());
	}
}
