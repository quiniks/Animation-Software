#include "..\include\KeyframeManager.h"

KeyframeManager::KeyframeManager(unsigned int p_FrameRate, double p_AnimationTime, Shapes* p_Shapes)
{
	std::function<void(unsigned int)> l_RecordKeyFrameCB = std::bind(&KeyframeManager::RecordKeyframe, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("OnDrawEnd", l_RecordKeyFrameCB);
	EventHandlerInstance.Connect2("OnTransformEnd", l_RecordKeyFrameCB);
	//EventHandlerInstance.Register2("OnKeyFrameAdded", &OnKeyFrameAdded);
	//EventHandlerInstance.Register2("OnKeyFrameDeleted", &OnKeyFrameDeleted);
	//EventHandlerInstance.Register2("OnFrameSet", &OnFrameSet);

	m_AnimationTime = std::chrono::duration<double>(p_AnimationTime);
	m_FramePeriod = std::chrono::duration<double>(1.0f / p_FrameRate);
	m_Shapes = p_Shapes;
	m_TotalFrames = p_AnimationTime / (1.0f / p_FrameRate);
}

KeyframeManager::~KeyframeManager()
{

}

AdjKeyFrameData KeyframeManager::GetAdjKeyFrameData(unsigned int p_ID)
{
	flat_set<ShapeKeyFrames>::iterator l_IDItr = m_ShapesAndKeys.find(p_ID);
	flat_set<KeyFrame, CompareFrame>& l_KeyFrames = l_IDItr->m_KeyFrames2;
	flat_set<KeyFrame>::const_iterator l_KeyFrameItr = l_KeyFrames.find(m_CurrentFrame);

	AdjKeyFrameData l_AdjFrameData;
	l_AdjFrameData.Prev = l_KeyFrames.begin()->m_Frame;
	l_AdjFrameData.Next = l_KeyFrames.end()->m_Frame;
	l_AdjFrameData.Visible = true;

	for (l_KeyFrameItr = l_KeyFrames.begin(); l_KeyFrameItr != l_KeyFrames.end(); ++l_KeyFrameItr) {
		if (m_CurrentFrame <= l_KeyFrameItr->m_Frame) {
			l_AdjFrameData.Next = l_KeyFrameItr->m_Frame;
			break;
		}
		l_AdjFrameData.Prev = l_KeyFrameItr->m_Frame;
	}
	if (l_AdjFrameData.Prev > m_CurrentFrame) {
		l_AdjFrameData.Visible = false;
	}
	return l_AdjFrameData;

	/////////
	/*
	std::vector<unsigned int> l_OrderedKeyFrames;
	for (auto l_KeyFrames : m_ShapeKeyFrames.at(p_ID)) {
		l_OrderedKeyFrames.push_back(l_KeyFrames.first);
	}
	std::sort(l_OrderedKeyFrames.begin(), l_OrderedKeyFrames.end());
	AdjKeyFrameData l_ShapeAnimData;
	l_ShapeAnimData.Prev = l_OrderedKeyFrames.at(0);
	l_ShapeAnimData.Next = l_OrderedKeyFrames.back();
	l_ShapeAnimData.Visible = true;
	for (int i = 0; i < l_OrderedKeyFrames.size(); i++) {
		if (m_CurrentFrame <= l_OrderedKeyFrames.at(i)) {
			l_ShapeAnimData.Next = l_OrderedKeyFrames.at(i);
			break;
		}
		l_ShapeAnimData.Prev = l_OrderedKeyFrames.at(i);
	}
	if (l_ShapeAnimData.Prev > m_CurrentFrame) {
		l_ShapeAnimData.Visible = false;
	}
	return l_ShapeAnimData;
	*/
}

void KeyframeManager::RecordKeyframe(unsigned int p_ID)
{
	ObjectData l_Data = m_Shapes->FindShape(p_ID).GetObjectData();
	KeyFrame l_KeyFrame;
	l_KeyFrame.m_Frame = m_CurrentFrame;
	l_KeyFrame.m_ObjectData = l_Data;

	flat_set<ShapeKeyFrames>::iterator l_IDItr = m_ShapesAndKeys.find(p_ID);
	flat_set<KeyFrame, CompareFrame>& l_KeyFrames = l_IDItr->m_KeyFrames2;
	//Check if ID already exists
	if (l_IDItr != m_ShapesAndKeys.end()) {
		//exists
		flat_set<KeyFrame>::const_iterator l_KeyFrameItr = l_KeyFrames.find(m_CurrentFrame);
		//check if current frame exists
		if (l_KeyFrameItr != l_KeyFrames.end()) {
			//exists: overwrite object data
			l_KeyFrames.erase(l_KeyFrameItr);
			l_KeyFrames.insert(l_KeyFrame);
		}
		else {
			//exist'nt
			l_KeyFrames.insert(l_KeyFrame);
		}
	}
	else {
		//exist'nt
		ShapeKeyFrames l_ShapeKeyFrames;
		l_ShapeKeyFrames.m_ID = p_ID;
		l_ShapeKeyFrames.m_KeyFrames2.insert(l_KeyFrame);
		m_ShapesAndKeys.insert(l_ShapeKeyFrames);
	}

	OnUpdate.Notify(m_ShapesAndKeys, FrameState::Recorded);

	/*
	if (!ContainsID(p_ID)) {
		//No: record first frame
		KeyFrame l_KeyFrame;
		l_KeyFrame.m_Frame = m_CurrentFrame;
		l_KeyFrame.m_ObjectData = l_Data;
		ShapeKeyFrames l_ShapeKeyFrames;
		l_ShapeKeyFrames.m_ID = p_ID;
		l_ShapeKeyFrames.m_KeyFrames.push_back(l_KeyFrame);

		m_ShapesAndKeys.insert(l_ShapeKeyFrames);
		//m_ShapesAndKeyFrames.push_back(l_ShapeKeyFrames);
	}
	else {
		//Yes: Check if current frame exists for given ID
		if (!ContainsKeyFrame(p_ID, m_CurrentFrame)) {
			//No: record frame
			KeyFrame l_KeyFrame;
			l_KeyFrame.m_Frame = m_CurrentFrame;
			l_KeyFrame.m_ObjectData = l_Data;

			FindID(p_ID).m_KeyFrames.push_back(l_KeyFrame);
		}
		else {
			//Yes: overwrite frame
			FindKeyFrame(p_ID, m_CurrentFrame).m_ObjectData = l_Data;
		} 
	}
	//std::sort(FindID(p_ID).m_KeyFrames.begin(), FindID(p_ID).m_KeyFrames.end(), SortByFrame);
	*/
}

void KeyframeManager::DeleteKeyframe(unsigned int p_ID, unsigned int p_FrameNumber)
{
	/*
	if (m_ShapeKeyFrames.at(p_ID).find(m_CurrentFrame) != m_ShapeKeyFrames.at(p_ID).end()) {
		m_ShapeKeyFrames.at(p_ID).erase(m_CurrentFrame);
	}
	*/
	/*
	std::vector<KeyFrame>& l_KeyFrames = FindID(p_ID).m_KeyFrames;
	l_KeyFrames.erase(l_KeyFrames.begin() + FrameIndex(p_ID, p_FrameNumber));
	*/
	flat_set<ShapeKeyFrames>::iterator l_IDItr = m_ShapesAndKeys.find(p_ID);
	flat_set<KeyFrame, CompareFrame>& l_KeyFrames = l_IDItr->m_KeyFrames2;
	flat_set<KeyFrame>::const_iterator l_KeyFrameItr = l_KeyFrames.find(m_CurrentFrame);
	l_KeyFrames.erase(l_KeyFrameItr);
}

void KeyframeManager::SetCurrentFrame(unsigned int p_FrameNumber)
{
	m_CurrentFrame = p_FrameNumber;
	flat_set<ShapeKeyFrames>::iterator l_IDItr;
	for (l_IDItr = m_ShapesAndKeys.begin(); l_IDItr != m_ShapesAndKeys.end(); ++l_IDItr) {
		unsigned int l_ID = l_IDItr->m_ID;
		AdjKeyFrameData l_ShapeAnimData = GetAdjKeyFrameData(l_ID);
		if (l_ShapeAnimData.Visible) {
			//Do interpolation
			float l_NextPrevFrameDiff = l_ShapeAnimData.Next - l_ShapeAnimData.Prev;
			if (l_NextPrevFrameDiff > 0) {
				flat_set<KeyFrame, CompareFrame>& l_KeyFrames = l_IDItr->m_KeyFrames2;
				float l_CurrentPrevFrameDiff = m_CurrentFrame - l_ShapeAnimData.Prev;
				float l_IntepolationProgress = l_CurrentPrevFrameDiff / l_NextPrevFrameDiff;
				const sf::Vector2f& l_Prev = l_KeyFrames.find(l_ShapeAnimData.Prev)->m_ObjectData.m_Position;
				const sf::Vector2f& l_Next = l_KeyFrames.find(l_ShapeAnimData.Next)->m_ObjectData.m_Position;
				const sf::Vector2f& l_InterplatedPos = m_InterpolationHelper.Linear(l_IntepolationProgress, l_Prev, l_Next);
				m_Shapes->FindShape(l_ID).SetPosition(l_InterplatedPos);
			}
		}
		else {
			m_Shapes->FindShape(l_ID).SetPosition(sf::Vector2f(1000, 1000));
		}
	}
	///////
	/*
	for (auto const& l_ShapeKeyFrames : m_ShapeKeyFrames) {
		unsigned int l_ID = l_ShapeKeyFrames.first;
		AdjKeyFrameData l_ShapeAnimData = GetAdjKeyFrameData(l_ID);
		if (l_ShapeAnimData.Visible) {
			//Do interpolation
			float l_Diff = l_ShapeAnimData.Next - l_ShapeAnimData.Prev;
			if (l_Diff > 0) {
				float l_Dist = m_CurrentFrame - l_ShapeAnimData.Prev;
				float l_Progress = l_Dist / l_Diff;
				const sf::Vector2f& l_Prev = l_ShapeKeyFrames.second.at(l_ShapeAnimData.Prev).m_Position;
				const sf::Vector2f& l_Next = l_ShapeKeyFrames.second.at(l_ShapeAnimData.Next).m_Position;
				m_InterpolationHelper.Linear(l_Progress, l_Prev, l_Next);
			}
		}
		else {
			m_Shapes->FindShape(l_ID).SetPosition(sf::Vector2f(1000, 1000));
		}
	}
	*/
}

void KeyframeManager::Play()
{
	m_State = AnimState::Playing;
}

void KeyframeManager::Stop()
{
	m_State = AnimState::Stopped;
}

void KeyframeManager::Update()
{
	std::chrono::time_point<std::chrono::system_clock> m_CurrentTime(std::chrono::system_clock::now());
	std::chrono::duration<double> m_ElapsedSeconds = m_CurrentTime - m_PreviousTime;
	m_PreviousTime = m_CurrentTime;
	if (m_ElapsedSeconds > m_SecondLimit) {
		m_ElapsedSeconds = m_SecondLimit;
	}

	switch (m_State) {
	case AnimState::Playing:
		if (m_CurrentFrame < m_TotalFrames) {
			m_Accumulator += m_ElapsedSeconds;
			if (m_Accumulator >= m_FramePeriod) {
				m_Accumulator = std::chrono::duration<double>(0);
				m_CurrentFrame++;
				SetCurrentFrame(m_CurrentFrame);
			}
		}
		else {
			m_State = AnimState::Stopped;
			m_CurrentFrame = 0;
		}
		break;
	case AnimState::Stopped:

		break;
	default:
		break;
	}
}

unsigned int KeyframeManager::GetTotalFrames()
{
	return m_TotalFrames;
}

unsigned int KeyframeManager::GetCurrentFrame()
{
	return m_CurrentFrame;
}
