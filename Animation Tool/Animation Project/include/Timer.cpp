#include "Timer.h"

Q::Timer::Timer(unsigned int p_Hours, unsigned int p_Minutes, double p_Seconds)
{
	if (p_Seconds >= 60) {
		int l_ExtraMinutes = p_Seconds / 60;
		m_Minutes = l_ExtraMinutes;
		m_Seconds = 60 * ((p_Seconds / 60) - l_ExtraMinutes);
	}
	else {
		m_Seconds = p_Seconds;
	}
	m_Minutes += p_Minutes;
	if (m_Minutes >= 60) {
		int l_ExtraHours = m_Minutes / 60;
		m_Hours = l_ExtraHours;
		m_Minutes = 60 * (((double)m_Minutes / 60) - l_ExtraHours);
	}

	m_Hours += p_Hours;

	std::cout << m_Hours << ":" << m_Minutes << ":" << m_Seconds << std::endl;
}

void Q::Timer::Update(double p_DeltaTime)
{
	if (m_Hours >= 0 and m_Hours < 100) {
		m_Seconds += p_DeltaTime;
		///
		if (m_Seconds < 0) {
			m_Minutes--;
			m_Seconds = 59;
		}
		else if (m_Seconds >= 60) {
			m_Minutes++;
			m_Seconds = 0;
		}
		///
		if (m_Minutes < 0) {
			m_Hours--;
			m_Minutes = 59;
		}
		else if (m_Minutes >= 60) {
			m_Hours++;
			m_Minutes = 0;
		}
	}

	std::cout << m_Hours << ":" << m_Minutes << ":" << m_Seconds << std::endl;
}

Q::Time::Time(unsigned int p_Hours, unsigned int p_Minutes, double p_Seconds)
{
	if (p_Seconds >= 60) {
		int l_Minutes = p_Seconds / 60;
		m_Minutes = l_Minutes;
		m_Seconds = 60 * ((p_Seconds / 60) - l_Minutes);
	}
	else {
		m_Seconds = p_Seconds;
	}
	if (p_Minutes >= 60) {
		int l_Hours = p_Minutes / 60;
		m_Hours = l_Hours;
		m_Minutes = 60 * (((double)p_Minutes / 60) - l_Hours);
	}
	else {
		m_Minutes = p_Minutes;
	}

	m_Hours += p_Hours;

	std::cout << m_Hours << ":" << m_Minutes << ":" << m_Seconds << std::endl;
}

double Q::Time::GetSeconds()
{
	return m_Seconds;
}

int Q::Time::GetMinutes()
{
	return m_Minutes;
}

int Q::Time::GetHours()
{
	return m_Hours;
}

void Q::Time::SetSeconds(double p_Seconds)
{
	if (p_Seconds >= 60) {
		int l_Minutes = p_Seconds / 60;
		m_Minutes += l_Minutes;
		m_Seconds = 60 * ((p_Seconds / 60) - l_Minutes);
	}
	else if (p_Seconds < 0) {
		m_Seconds = p_Seconds;
	}
	if (m_Minutes >= 60) {
		int l_Hours = m_Minutes / 60;
		m_Hours += l_Hours;
		m_Minutes = 60 * (((double)m_Minutes / 60) - l_Hours);
	}
}

void Q::Time::SetMinutes(unsigned int p_Minutes)
{
	if (p_Minutes >= 60) {
		int l_Hours = p_Minutes / 60;
		m_Hours += l_Hours;
		m_Minutes = 60 * (((double)p_Minutes / 60) - l_Hours);
	}
	else {
		m_Minutes = p_Minutes;
	}
}

void Q::Time::SetHours(unsigned int p_Hours)
{
	m_Hours = p_Hours;
}
