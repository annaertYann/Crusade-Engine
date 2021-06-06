#include "MiniginPCH.h"
#include "Time.h"
using namespace Crusade;
void Time::Init(const std::chrono::steady_clock::time_point& startTime, const float& fixedDeltaTime,float* pDeltaTime)
{
	m_StartTime = startTime;
	m_pDeltaTime = pDeltaTime;
	m_FixedDeltaTime = fixedDeltaTime;
}


float Time::GetDeltaTime()const
{
	return *m_pDeltaTime;
}


float Time::GetFixedDeltaTime()const
{
	return m_FixedDeltaTime;
}

float Time::GetTotalRunTime()const
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto timeDiff = std::chrono::duration<float>(currentTime - m_StartTime).count();
	return timeDiff;
}