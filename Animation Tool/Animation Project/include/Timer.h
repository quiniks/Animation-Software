#pragma once
#include <chrono>
#include <iostream>

namespace Q {
	class Time {
	protected:
		double m_Seconds = 0;
		int m_Minutes = 0;
		int m_Hours = 0;
	public:
		Time() = default;
		Time(unsigned int p_Hours, unsigned int p_Minutes, double p_Seconds);
		double GetSeconds();
		int GetMinutes();
		int GetHours();

		void SetSeconds(double p_Seconds);
		void SetMinutes(unsigned int p_Minutes);
		void SetHours(unsigned int p_Hours);
	};

	class Timer : public Time {
	public:
		Timer(unsigned int p_Hours, unsigned int p_Minutes, double p_Seconds);
		void Update(double p_DeltaTime);
	};
}