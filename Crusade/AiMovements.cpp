#include "MiniginPCH.h"
#include "AIMovements.h"
#include "Event.h"
#include "PlayerController.h"
#include "Time.h"
#include "SceneManager.h"
#include "Qbert.h"
using namespace Crusade;
///////////////////////////////////////////////////////////////////////////////////////////////////
///COILY
///////////////////////////////////////////////////////////////////////////////////////////////////
void CoilyMovment::Start()
{
	m_Publisher = m_Owner->GetComponent<Publisher>();
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
	auto qberts = SceneManager::GetInstance().GetCurrentScene()->FindAllObjects("Qbert");
	for(const auto qbert :qberts)
	{
		m_QbertTransforms.push_back(qbert->GetCTransform());
	}
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
	case State::manualWaiting:
		EggUpdate();
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
			Transform();
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
void CoilyMovment::Transform()
{
	if (m_CurrentState == State::manualWaiting)
	{
		AddPlayerControls();
		m_CurrentState = State::manual;
	}
	else
	{
		m_CurrentState = State::chase;
		int number = rand() % m_QbertTransforms.size();
		m_QbertChoice = m_QbertTransforms[number];
	}
	m_Owner->Notify("Transform");
	m_MoveDelay.Start();
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
	if (col->GetOwner()->GetComponent<QbertController>())
	{
		if (!m_Owner->GetComponent<CharacterMovement>()->IsFalling())
		{
			col->GetOwner()->Notify("Death");
		}
	}
}
void CoilyMovment::AddPlayerControls()
{
	auto upMovementKey = new UpMovementTrigger{ m_Owner };
	auto downMovementKey = new DownMovementTrigger{ m_Owner };
	auto rightMovementKey = new RightMovementTrigger{ m_Owner };
	auto leftMovementKey = new LeftMovementTrigger{ m_Owner };
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<UpMovementTrigger>(upMovementKey),0 });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<DownMovementTrigger>(downMovementKey),0 });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<RightMovementTrigger>(rightMovementKey),0 });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<LeftMovementTrigger>(leftMovementKey),0 });
	m_UpSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(upMovementKey);
	m_DownSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(downMovementKey);
	m_RightSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(rightMovementKey);
	m_LeftSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(leftMovementKey);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///UGG
///////////////////////////////////////////////////////////////////////////////////////////////////
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
		if (!m_Owner->GetComponent<CharacterMovement>()->IsFalling())
		{
			col->GetOwner()->Notify("Death");
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///WRONGWAY
///////////////////////////////////////////////////////////////////////////////////////////////////
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
		if (!m_Owner->GetComponent<CharacterMovement>()->IsFalling())
		{
			col->GetOwner()->Notify("Death");
		}

	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///SLICK
///////////////////////////////////////////////////////////////////////////////////////////////////
void SlickMovement::Start()
{
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
	m_Publisher = m_Owner->GetComponent<Publisher>();
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
}
void SlickMovement::Update()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		m_MoveDelay.Start();
		if (rand() % 2 == 0)
		{
			m_Movement->Notify("Left");
		}
		else
		{
			m_Movement->Notify("Right");
		}
		m_Movement->Notify("Down");
	}
	m_Movement->ResetCurrentCube();
}
void SlickMovement::Notify(const std::string& message)
{
	if (message == "Death")
	{
		m_Owner->SetRemove();
	}
}
void SlickMovement::OnTriggerEnter(CCollider* col)
{
	if (col->GetOwner()->GetComponent<QbertController>())
	{
		if (!m_Owner->GetComponent<CharacterMovement>()->IsFalling())
		{
			m_Owner->SetRemove();
			m_Publisher->SendNotification("SamCatch");
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///SAM
///////////////////////////////////////////////////////////////////////////////////////////////////
void SamMovement::Start()
{
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
	m_Publisher = m_Owner->GetComponent<Publisher>();
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
}
void SamMovement::Update()
{
	const auto deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_MoveDelay.Update(deltaTime))
	{
		m_MoveDelay.Start();
		if(rand()%2==0)
		{
			m_Movement->Notify("Left");
		}
		else
		{
			m_Movement->Notify("Right");
		}
		m_Movement->Notify("Down");
	}
	m_Movement->ResetCurrentCube();
}
void SamMovement::Notify(const std::string& message)
{
	if (message == "Death")
	{
		m_Owner->SetRemove();
	}
}
void SamMovement::OnTriggerEnter(CCollider* col)
{
	if (col->GetOwner()->GetComponent<QbertController>())
	{
		if (!m_Owner->GetComponent<CharacterMovement>()->IsFalling())
		{
			m_Owner->SetRemove();
			m_Publisher->SendNotification("SamCatch");
		}
	}
}