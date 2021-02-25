#include "MiniginPCH.h"
#include "Scripts.h"
#include <cmath>
#include "GameObject.h"
#include "Time.h"
#include "Prefabs.h"
using namespace Crusade;
void FPSScript::Start()
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
			m_CTextRender->SetText(std::to_string( int(round(m_CurrentFPS)) ) + " FPS");
		}
	}
}
void Lives::Start()
{
	const auto command = new PlayerDied(m_Owner);
	m_KillSWitch = InputManager::GetInstance().CreateCommandKillSwitch(command);
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<PlayerDied>{command},0,-1,SDL_SCANCODE_P });
}
