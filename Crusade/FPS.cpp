#include "MiniginPCH.h"
#include "FPS.h"
#include "GameObject.h"
using namespace Crusade;
void FPSScript::Awake()
{
	m_CTextRender = m_Owner->GetComponent<CTextRender>();
}

void FPSScript::Update()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	m_CurrentFPS += 1 / deltaTime;
	m_CurrentFPS /= 2;
	if (m_RenderDelay.Update(deltaTime))
	{
		m_RenderDelay.Start();

		if (m_CTextRender != nullptr)
		{
			m_CTextRender->SetText(std::to_string(int(round(m_CurrentFPS))) + " FPS");
		}
	}
}