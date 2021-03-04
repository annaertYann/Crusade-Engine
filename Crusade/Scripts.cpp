#include "MiniginPCH.h"
#include "Scripts.h"
#include <cmath>
#include "GameObject.h"
#include "Time.h"
#include "Prefabs.h"
#include "CAnimator2D.h"
#include <SDL.h>
#include "Camera2D.h"
#include "Scene.h"
#include "SceneManager.h"
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
QbertController::QbertController(int dieButton, int GainScoreButton)
{
	m_DieButton = dieButton;
	m_ScoreButton = GainScoreButton;
}
void QbertController::Start()
{
	QBertDied* dieCommand = new QBertDied{ m_Owner };
	QBertGainedPoints* pointCommand = new QBertGainedPoints{ m_Owner };
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<QBertDied>(dieCommand),0,-1,m_DieButton });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<QBertGainedPoints>(pointCommand),0,-1,m_ScoreButton });
	m_DieSwitch = InputManager::GetInstance().CreateCommandKillSwitch(dieCommand);
	m_ScoreSwitch = InputManager::GetInstance().CreateCommandKillSwitch(pointCommand);
}
void QbertController::Update()
{
	m_Owner->GetCTransform()->Rotate({0,0,100*Time::GetInstance().GetDeltaTime()});
	/*SceneManager::GetInstance().GetCurrentScene()->FindObject("Camera")->GetComponent<Camera2D>()->Track
	( Point2f{m_Owner->GetCTransform()->GetPosition().x,m_Owner->GetCTransform()->GetPosition().y}
		, Time::GetInstance().GetDeltaTime());*/
}

