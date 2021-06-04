#include "MiniginPCH.h"
#include "AIMovements.h"
#include "Event.h"
#include "PlayerController.h"
#include "Time.h"
#include "SceneManager.h"
#include "Qbert.h"
using namespace Crusade;
void CoilyMovment::Start()
{
	m_Publisher = m_Owner->GetComponent<Publisher>();
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
	auto qberts = SceneManager::GetInstance().GetCurrentScene()->FindAllObjects("Qbert");
	for(const auto qbert :qberts)
	{
		m_QbertTransforms.push_back(qbert->GetCTransform());
	}
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
}
void CoilyMovment::Update()
{
	switch (m_CurrentState)
	{
	case State::egg:
		EggUpdate();
		break;
	case State::chase:
		ChaseUpdate();
		break;
	default: ;
	}

	m_Movement->IgnoreCurrentCube();
}
void CoilyMovment::EggUpdate()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		if (m_JumpCounter >= m_maxJumpsBeforeTransform)
		{
			m_CurrentState = State::chase;
			m_Owner->Notify("Transform");
			m_MoveDelay.Start();
			int number = rand()%m_QbertTransforms.size();
			m_QbertChoice = m_QbertTransforms[number];
		}
		else
		{
			m_JumpCounter++;
			m_MoveDelay.Start();
			m_Movement->Notify("Down");
			utils::SwitchBoolean(m_MoveLeftSwitch);
			if (m_MoveLeftSwitch)
			{
				m_Movement->Notify("Left");
			}
			else
			{
				m_Movement->Notify("Right");
			}
		}
	}
}
void CoilyMovment::ChaseUpdate()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		m_MoveDelay.Start();
		glm::vec3 closestPos{m_QbertChoice->GetPosition()};
		const auto coilyPos = m_Owner->GetCTransform()->GetPosition();
		if((closestPos-coilyPos).x>0)
		{
			m_Movement->Notify("Right");
		}
		if ((closestPos - coilyPos).x < 0)
		{
			m_Movement->Notify("Left");
		}
		if ((closestPos - coilyPos).y > 0)
		{
			m_Movement->Notify("Up");
		}
		if ((closestPos - coilyPos).y < 0)
		{
			m_Movement->Notify("Down");
		}
	}
}
void CoilyMovment::Notify(const std::string& message)
{
	if (message == "Death")
	{
		m_Owner->SetRemove();
		m_Publisher->SendNotification("CoilyDeath");
	}
}
void CoilyMovment::OnTriggerEnter(CCollider* col)
{
	if(col->GetOwner()->GetComponent<QbertController>())
	{
		col->GetOwner()->Notify("Death");
	}
}


void UggMovement::Start()
{
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
}
void UggMovement::Update()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		m_MoveDelay.Start();
		m_Movement->Notify("Up");
		m_Movement->Notify("Right");
	}
	m_Movement->IgnoreCurrentCube();
}
void UggMovement::Notify(const std::string& message)
{
	if (message == "Death")
	{
		m_Owner->SetRemove();
	}
}
void UggMovement::OnTriggerEnter(CCollider* col)
{
	if (col->GetOwner()->GetComponent<QbertController>())
	{
		col->GetOwner()->Notify("Death");
	}
}


void WrongWayMovement::Start()
{
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
}
void WrongWayMovement::Update()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		m_MoveDelay.Start();
		m_Movement->Notify("Up");
		m_Movement->Notify("Left");
	}
	m_Movement->IgnoreCurrentCube();
}
void WrongWayMovement::Notify(const std::string& message)
{
	if (message == "Death")
	{
		m_Owner->SetRemove();
	}
}
void WrongWayMovement::OnTriggerEnter(CCollider* col)
{
	if (col->GetOwner()->GetComponent<QbertController>())
	{
		col->GetOwner()->Notify("Death");
	}
}