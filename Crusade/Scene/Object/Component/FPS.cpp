#include "MiniginPCH.h"
#include "FPS.h"
#include <cmath>
#include "../../../Foundation/Time.h"
#include "RenderComponents.h"
#include "../GameObject.h"
using namespace Crusade;
void CFPS::Update()
{
	m_AccuSec += Time::GetInstance().GetDeltaTime();
	m_Frames++;
	if (m_Frames >= m_MaxFrames)
	{
		m_LastFPS = m_Frames / m_AccuSec;
		Reset();
		if (m_DoRenderFPS)
		{
			const auto text = m_Owner->GetComponent<CTextRender>();
			if (text != nullptr)
			{
				text->SetText(std::to_string(GetCurrentFPS()) + " FPS");
			}
		}
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
