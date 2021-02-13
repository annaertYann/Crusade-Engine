#include "MiniginPCH.h"
#include "FPS.h"
#include <cmath>
#include "../../../Foundation/Time.h"
using namespace Crusade;
void CFPS::Update()
{
	m_AccuSec += Time::GetInstance().GetDeltaTime();
	m_Frames++;
	if (m_Frames >= m_Frames)
	{
		m_LastFPS = m_Frames / m_AccuSec;
		Reset();
	}
}
int CFPS::GetCurrentFPS() const
{
	return int(round(m_LastFPS));
}
void CFPS::Reset()
{
	m_AccuSec = 0;
	m_Frames = 0;
}
