#include "MiniginPCH.h"
#include "CAnimator2D.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Time.h"
#pragma warning (disable:26815)
using namespace Crusade;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ANIMATION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Animation::Animation(const std::string& filepath, const int& colloms, const float& framesPerSec, const bool& isLoop)
{
	m_FilePath = filepath;
	m_Colloms = colloms;
	m_MaxColloms = m_Colloms;
	m_FramesPerSecond = framesPerSec;
	m_IsLoop = isLoop;
	m_Delay.SetDelayTime(1 / framesPerSec);
	m_Tag = m_NextTag;
	m_NextTag++;
	m_IsFinished = false;
}
Animation::Animation(const std::string& filepath, const int& colloms, const int& rows, const float& framesPerSec, const bool& isLoop)
{
	m_FilePath = filepath;
	m_Rows = rows;
	m_Colloms = colloms;
	m_MaxColloms = m_Colloms;
	m_FramesPerSecond = framesPerSec;
	m_IsLoop = isLoop;
	m_Delay.SetDelayTime(1 / framesPerSec);
	m_IsVertical = true;
	m_Tag = m_NextTag;
	m_NextTag++;
	m_IsFinished = false;
}

void Animation::Start(CTexture2DRender* renderer)
{
	renderer->SetTexture(m_FilePath );
	m_Width = int(renderer->GetTextureDimensions().x);
	m_height =int(renderer->GetTextureDimensions().y);
	m_CurrentCollom = 0;
	renderer->SetSourceRect({ m_CurrentCollom * (m_Width / m_Colloms),m_CurrentRow * (m_height / m_Rows),m_Width / m_Colloms,m_height / m_Rows });
	m_IsFinished = false;
	if (m_IsVertical)
	{
		m_CurrentRow = 0;
	}
}
void Animation::Update(CTexture2DRender* renderer, const float& deltaTime)
{
	if (m_Delay.Update(deltaTime))
	{
		m_Delay.Start();
		m_IsFinished = false;
		if (m_CurrentCollom <= m_MaxColloms-1 )
		{
			m_CurrentCollom++;
		}
		if (m_CurrentCollom >= m_MaxColloms)
		{
			if (m_IsVertical)
			{
				m_CurrentRow++;
				m_CurrentCollom = 0;
				if(m_CurrentRow>=m_Rows)
				{
					if (m_IsLoop)
					{
						m_CurrentRow = 0;
						m_IsFinished = true;
					}
					else
					{
						m_CurrentCollom = m_MaxColloms - 1;
						m_CurrentRow= m_Rows - 1;
						m_IsFinished = true;
					}
				}
			}
			else
			{
				if (m_IsLoop)
				{
					m_CurrentCollom = 0;
					m_IsFinished = true;
				}
				else
				{
					m_CurrentCollom = m_MaxColloms - 1;
					m_IsFinished = true;
				}
			}
		}
		renderer->SetSourceRect({ m_CurrentCollom * (m_Width / m_Colloms),m_CurrentRow * (m_height / m_Rows),m_Width / m_Colloms,m_height / m_Rows });
	}
}
void Animation::SetAsMultiSprite(const int& currentRow, const int& maxColloms)
{
	m_CurrentRow = currentRow;
	m_MaxColloms = maxColloms;
	m_IsVertical = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ANIMATOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CAnimator2D::CAnimator2D(const std::shared_ptr<Animation>& startAnimation, const glm::vec2& destDimension)
{
	m_CurrentAnimation = startAnimation.get();
	m_Animations.push_back(startAnimation);
	m_DestDimensions = destDimension;
}

void CAnimator2D::Start()
{
	m_Renderer = m_Owner->GetComponent<CTexture2DRender>();
	if (m_Renderer==nullptr)
	{
		const auto x = std::make_shared<CTexture2DRender>(m_CurrentAnimation->GetFilePath());
		m_Owner->AddComponent<CTexture2DRender>(x);
		m_Renderer = x.get();
	}
	
	m_CurrentAnimation->Start(m_Renderer);
	SetDestDimensions(int(m_DestDimensions.x), int(m_DestDimensions.y));
}


void CAnimator2D::Update()
{
	for (const auto& transition : m_Transitions)
	{
		if (m_CurrentAnimation->GetTag()==transition->GetFrom()->GetTag())
		{
			if (transition->ToTransition())
			{
				ResetAllConditions();
				m_CurrentAnimation = transition->GetTo().get();
				m_CurrentAnimation->Start(m_Renderer);
				break;
			}
		}
	}
	m_CurrentAnimation->Update(m_Renderer, Time::GetInstance().GetDeltaTime());
}
void CAnimator2D::TriggerTransition(const std::string& name)
{
	for (const auto& transition : m_Transitions)
	{
		if (transition->GetName()==name)
		{
			*transition->GetCondition() = true;
			return;
		}
	}
}
void CAnimator2D::ResetAllConditions()
{
	for (const auto& transition : m_Transitions)
	{
		if (transition->GetCondition()) { *transition->GetCondition() = false; }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///TRANSITION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Transition::Transition(const std::shared_ptr<Animation>& from, const std::shared_ptr<Animation>& to, const std::string& name,const bool& hasToFinishAnimation, const std::shared_ptr<bool>& condition)
	:m_From(from)
	,m_To(to)
	,m_Name(name)
	,m_HasToFinishAnimation(hasToFinishAnimation)
{
	
	m_Condition = condition;
	
}
bool Transition::ToTransition()const
{
	bool condition = true;
	if(m_Condition.get())
	{
		condition = *m_Condition;
	}
	if (m_HasToFinishAnimation)
	{
		const auto hasToFinish = m_From->GetIsFinished();
		return hasToFinish && condition;
	}
	else
	{
		return condition;
	}
	
}
