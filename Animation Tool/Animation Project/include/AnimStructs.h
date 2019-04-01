#pragma once
#include "ObjectData.h"
#include <boost/container/flat_set.hpp>

using namespace boost::container;

//! Struct that holds adjacent keyframe data
struct AdjKeyFrameData {
	int Next;
	int Prev;
	bool Visible;
};
//! Struct that holds frame number and its corresponding object data
struct KeyFrame {
	unsigned int m_Frame;
	ObjectData m_ObjectData;
};
//! Comparator that orders frames via a the frame number
struct CompareFrame
{
	using is_transparent = void;
	bool operator()(const KeyFrame& p_A, const KeyFrame& p_B) const
	{
		return p_A.m_Frame < p_B.m_Frame;
	}
	bool operator()(unsigned int p_Frame, const KeyFrame& p_ShapeKeyFrames) const
	{
		return p_Frame < p_ShapeKeyFrames.m_Frame;
	}
	bool operator()(const KeyFrame& p_ShapeKeyFrames, unsigned int p_Frame) const
	{
		return p_ShapeKeyFrames.m_Frame < p_Frame;
	}
};
//! Struct that holds the ID and corresponding keyframes
struct ShapeKeyFrames {
	unsigned int m_ID;
	flat_set<KeyFrame, CompareFrame> m_KeyFrames2;
};
//! Comparator that orders ShapeKeyFrames by their ID
struct CompareId
{
	using is_transparent = void;
	bool operator()(const ShapeKeyFrames& p_A, const ShapeKeyFrames& p_B) const
	{
		return p_A.m_ID < p_B.m_ID;
	}
	bool operator()(unsigned int p_ID, const ShapeKeyFrames& p_ShapeKeyFrames) const
	{
		return p_ID < p_ShapeKeyFrames.m_ID;
	}
	bool operator()(const ShapeKeyFrames& p_ShapeKeyFrames, unsigned int p_ID) const
	{
		return p_ShapeKeyFrames.m_ID < p_ID;
	}
};