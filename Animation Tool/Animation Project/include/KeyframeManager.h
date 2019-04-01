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

/**
* @class Keyframe manager
* @brief Manages keyframe data for objects
* Provides functionality to save, load, iterate and interpolate between keyframes
*/
class KeyframeManager
{
private:
	//! State of the animation i.e. is playing or is stopped
	AnimState m_State;
	//! Limiter for elapsed time to prevent large jumps in time due to long computation times
	std::chrono::duration<double> m_SecondLimit;
	//! The accumulated time every iteration
	std::chrono::duration<double> m_Accumulator;
	//! The time of the previous iteration
	std::chrono::time_point<std::chrono::system_clock> m_PreviousTime;
	//! Frame period is the time between each frame
	std::chrono::duration<double> m_FramePeriod;
	//! The run-time of the animation
	std::chrono::duration<double> m_AnimationTime;
	//! The total frames in the animation
	unsigned int m_TotalFrames;
	//! The current frame number
	unsigned int m_CurrentFrame = 0;
	//! Pointer to the shapes manager
	Shapes* m_Shapes;
	//! A vector based set for very fast search and iteration for a slow insertion and deletion.
	flat_set<ShapeKeyFrames, CompareId> m_ShapesAndKeys;
	//! A helper class that can do interpolation calculations
	InterpolationHelper m_InterpolationHelper;
	//! Method for determining the closest keyframes adjacent of the current frame number
	AdjKeyFrameData GetAdjKeyFrameData(unsigned int p_ID);
public:
	//! Constructor that takes framerate, runtime and a pointer to the shapes manager
	KeyframeManager(unsigned int p_FrameRate, double p_AnimationTime, Shapes* p_Shapes);
	~KeyframeManager();
	//! Record a keyframe at the current frame number for shape with given ID
	void RecordKeyframe(unsigned int p_ID);
	//! Delete the keyframe of shape with ID at frame p_FrameNumber
	void DeleteKeyframe(unsigned int p_ID, unsigned int p_FrameNumber);
	//! Sets the current frame to p_FrameNumber and places shapes at their interpolated positions
	void SetCurrentFrame(unsigned int p_FrameNumber);
	//! Sets the animation state to playing
	void Play();
	//! Sets the animation state to stopped
	void Stop();
	//! Updates the animation by calling "SetCurrentFrame" every update frame if the animation state is set to "Playing"
	void Update();
	//! Returns the total frame number
	unsigned int GetTotalFrames();
	//! Returns the current frame number
	unsigned int GetCurrentFrame();
	//! Signal that gives out the animation data to anything that needs it
	Signal<const flat_set<ShapeKeyFrames, CompareId>&, FrameState> OnUpdate;
};