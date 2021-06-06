#include "MiniginPCH.h"
#include "CharacterAnimationTrigger.h"
#include "CAnimator2D.h"
#include "PlayerController.h"
using namespace Crusade;
void CharacterAnimationTrigger::Start()
{
	m_Animator = m_Owner->GetComponent<CAnimator2D>();
	m_Render = m_Owner->GetComponent<CRender>();
}
void CharacterAnimationTrigger::Notify(const std::string& message)
{
	if (message == "JumpFront")
	{
		m_IsBack = false;
		m_Animator->TriggerTransition(message);
	}
	else if (message == "JumpBack")
	{
		m_IsBack = true;
		m_Animator->TriggerTransition(message);
	}
	else if (message == "LookLeft")
	{
		m_Render->SetFliphorizontal(true);
	}
	else if (message == "LookRight")
	{
		m_Render->SetFliphorizontal(false);
	}
	else if (message == "Transform")
	{
		m_Animator->TriggerTransition(message);
	}
}
