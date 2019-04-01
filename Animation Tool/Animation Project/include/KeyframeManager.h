#pragma once
//#include "Object.h"
#include "Enums.h"
#include <chrono>
#include "EventHandler.h"
#include "Button.h"
#include "Shapes.h"
#include "InterpolationHelper.h"
//#include <set>
//#include <boost/container/flat_set.hpp>
#include "AnimStructs.h"

using namespace boost::container;

class KeyframeManager
{
private:
	AnimState m_State;
	std::chrono::duration<double> m_SecondLimit;
	std::chrono::duration<double> m_Accumulator;
	std::chrono::time_point<std::chrono::system_clock> m_PreviousTime;

	std::chrono::duration<double> m_FramePeriod;
	std::chrono::duration<double> m_AnimationTime;
	unsigned int m_TotalFrames;

	unsigned int m_CurrentFrame = 0;
	Shapes* m_Shapes;

	//std::vector<ShapeKeyFrames> m_ShapesAndKeyFrames;
	//std::map<unsigned int, std::map<unsigned int, ObjectData>> m_ShapeKeyFrames;
	//flat_map<unsigned int, flat_map<unsigned int, ObjectData>> test;
	flat_set<ShapeKeyFrames, CompareId> m_ShapesAndKeys;

	InterpolationHelper m_InterpolationHelper;
	AdjKeyFrameData GetAdjKeyFrameData(unsigned int p_ID);
public:
	KeyframeManager(unsigned int p_FrameRate, double p_AnimationTime, Shapes* p_Shapes);
	~KeyframeManager();

	void RecordKeyframe(unsigned int p_ID);
	void DeleteKeyframe(unsigned int p_ID, unsigned int p_FrameNumber);
	void SetCurrentFrame(unsigned int p_FrameNumber);
	void Play();
	void Stop();
	void Update();

	unsigned int GetTotalFrames();
	unsigned int GetCurrentFrame();


	//Potentially inefficient method?
	Signal<const flat_set<ShapeKeyFrames, CompareId>&, FrameState> OnUpdate;
};