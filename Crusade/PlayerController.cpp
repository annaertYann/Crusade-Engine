#include "MiniginPCH.h"
#include "PlayerController.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Qbert.h"
using namespace Crusade;
CharacterMovement::CharacterMovement(float objectSize)
{
	m_ObjectSize = objectSize;
}
void CharacterMovement::Start()
{
	m_DirectionChoiceDelay.Stop();
	m_DieDelay.Stop();
	m_MovementSteering = m_Owner->GetComponent<MovementSteering>();
	auto cubes  = SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Cube");
	for (auto cube:cubes)
	{
		auto col = cube->GetComponent<CCollider>();
		m_Cubes.push_back(col);
	}
	m_CurrentCube = m_Cubes[0];
	SetTargetToCurrentCube();
	m_Renderer = m_Owner->GetComponent<CRender>();
	m_RigidBody = m_Owner->GetComponent<CRigidBody2D>();
	m_StartPos = m_Owner->GetCTransform()->GetPosition();
}
void CharacterMovement::Update()
{
	auto& time = Time::GetInstance();
	if(m_DirectionChoiceDelay.Update(time.GetDeltaTime())&&m_IsEnabled&&m_CubeIsTriggerd)
	{
		if (!Move())
		{
			SetTargetWhenNoCubeFound();
		}
		m_Direction = Vector2f{};
	}
	if(m_DieDelay.Update(time.GetDeltaTime()))
	{
		m_MovementSteering->SetMovementBehaviour(std::make_shared<NullSteering>());
		m_RigidBody->SetGravityEnabled(true);
		if (m_JumpedToBack)
		{
			m_Renderer->SetCurrentLayer("Back");
		}
		
	}
}

void CharacterMovement::SetOffMapTarget(const Vector2f& pos, const float& speed)
{
	m_IsEnabled = false;
	m_MovementSteering->SetMovementBehaviour(std::make_shared<Seek>(speed, Vector2f{ }));
	m_MovementSteering->SetTarget(pos);
	m_Renderer->SetCurrentLayer("Front");
	m_DieDelay.Stop();
	m_DieDelay.Reset();
	m_RigidBody->SetGravityEnabled(false);
	m_RigidBody->SetVelocity(glm::vec2{});
}
bool CharacterMovement::Move()
{
	utils::HitInfo info{};
	Point2f pos1{ m_CurrentCube->GetCenter() };
	Point2f pos2{ m_CurrentCube->GetCenter() };
	if (abs(m_Direction.x) < 0.1f)
	{
		if (m_IsLeftSelected)
		{
			m_Direction.x = -1;
		}
		else
		{
			m_Direction.x = 1;
		}
	}
	if (abs(m_Direction.y) < 0.1f)
	{
		m_Direction = Vector2f{  };
	}
	pos2.x += m_Direction.x * m_CurrentCube->GetDimensions().x / 2;
	pos2.y += m_Direction.y * m_CurrentCube->GetDimensions().x / 2;
	for (auto cube : m_Cubes)
	{
		if (cube->GetOwner()->GetObjectNummer() != m_CurrentCube->GetOwner()->GetObjectNummer())
		{
			if (Raycast(cube->GetVertices(), pos1, pos2, info))
			{
				m_CurrentCube = cube;
				SetTargetToCurrentCube();
				NotifyObjectOfJump();
				m_Direction = Vector2f{};
				m_CubeIsTriggerd = false;
				return true;
			}
		}
	}
	return false;
}
void CharacterMovement::SetTargetWhenNoCubeFound()
{
	if (!(abs(m_Direction.x) < 0.1f))
	{
		auto target = m_CurrentCube->GetCenter();
		target.x += m_Direction.x * m_ObjectSize*2;
		target.y += m_Direction.y * m_ObjectSize*2;
		m_MovementSteering->SetTarget(Vector2f{ target });
		NotifyObjectOfJump();
		m_IsEnabled = false;
		m_DieDelay.Start();
		m_JumpedToBack = false;
		if(m_Direction.y>0)
		{
			m_JumpedToBack = true;
		}
	}
}
void CharacterMovement::TriggerCurrentCube()
{
	if (!m_CubeIsTriggerd)
	{
		const auto pos = m_Owner->GetComponent<CTransform>()->GetPosition();
		if (abs(m_MovementSteering->GetTarget().x - pos.x) < 5 && abs(m_MovementSteering->GetTarget().y - pos.y) < 5)
		{
			m_CurrentCube->GetOwner()->Notify("Triggered");
			m_CubeIsTriggerd = true;
		}
	}
}
void CharacterMovement::ResetCurrentCube()
{
	if (!m_CubeIsTriggerd)
	{
		const auto pos = m_Owner->GetComponent<CTransform>()->GetPosition();
		if (abs(m_MovementSteering->GetTarget().x - pos.x) < 5 && abs(m_MovementSteering->GetTarget().y - pos.y) < 5)
		{
			m_CurrentCube->GetOwner()->Notify("Reset");
			m_CubeIsTriggerd = true;
		}
	}
}

void CharacterMovement::SetTargetToCurrentCube()const
{
	auto target = m_CurrentCube->GetCenter();
	target.x -= m_ObjectSize / 2;
	target.y += m_ObjectSize / 2;
	m_MovementSteering->SetTarget(Vector2f{ target });
}
void CharacterMovement::NotifyObjectOfJump()const
{
	//NOTIFY OBJECT THAT JUMP OCCURS
	if (abs(m_Direction.y) > 0.1f)
	{
		if (m_Direction.y > 0.1f)
		{
			m_Owner->Notify("JumpBack");
		}
		if (m_Direction.y < -0.1f)
		{
			m_Owner->Notify("JumpFront");
		}
	}
	//NOTIFY DIRECTION X 
	if (m_IsLeftSelected)
	{
		m_Owner->Notify("LookLeft");
	}
	else
	{
		m_Owner->Notify("LookRight");
	}
}
void CharacterMovement::ResetToStart()
{
	m_IsEnabled = true;
	m_RigidBody->SetGravityEnabled(false);
	m_RigidBody->SetVelocity(glm::vec2{});
	m_CurrentCube = m_Cubes[0];
	m_MovementSteering->SetMovementBehaviour(std::make_shared<Seek>(QBert::GetInstance().GetSpeed(), Vector2f{ }));
	m_DieDelay.Stop();
	m_DieDelay.Reset();
	m_CubeIsTriggerd = false;
	m_Renderer->SetCurrentLayer("Front");
	SetTargetToCurrentCube();
	m_RigidBody->SetGravityEnabled(false);
}
void CharacterMovement::ResetDeathAnim()
{
	m_DieDelay.Reset();
	m_DieDelay.Stop();
}
void CharacterMovement::Die()
{
	m_Owner->GetCTransform()->SetPosition(m_StartPos.x, m_StartPos.y, m_StartPos.z);
	ResetToStart();
}

void CharacterMovement::Notify(const std::string& message)
{
	if (message == "Up")
	{
		m_DirectionChoiceDelay.Start();
		m_Direction.y = 1;
	}
	else if (message == "Down")
	{
		m_DirectionChoiceDelay.Start();
		m_Direction.y = -1;
	}
	else if (message == "Left")
	{
		m_IsLeftSelected = true;
		m_DirectionChoiceDelay.Start();
		m_Direction.x = -1;
	}
	else if (message == "Right")
	{
		m_IsLeftSelected = false;
		m_DirectionChoiceDelay.Start();
		m_Direction.x = 1;
	}
}

//COMMANDS
void UpMovementKey::Execute()
{
	m_Actor->Notify("Up");
}
void DownMovementKey::Execute()
{
	m_Actor->Notify("Down");
}
void RightMovementKey::Execute()
{
	m_Actor->Notify("Right");
}
void LeftMovementKey::Execute()
{
	m_Actor->Notify("Left");
}
void UpMovementTrigger::Execute()
{
	auto joy = InputManager::GetInstance().GetControllerJoyStickTrigger(true);
	if (joy.y > 10000)
	{
		m_Actor->Notify("Up");
	}
}
void DownMovementTrigger::Execute()
{
	auto joy = InputManager::GetInstance().GetControllerJoyStickTrigger(true);
	if (joy.y < -10000)
	{
		m_Actor->Notify("Down");
	}
}
void RightMovementTrigger::Execute()
{
	auto joy = InputManager::GetInstance().GetControllerJoyStickTrigger(true);
	if (joy.x > 10000)
	{
		m_Actor->Notify("Right");
	}
}
void LeftMovementTrigger::Execute()
{
	auto joy = InputManager::GetInstance().GetControllerJoyStickTrigger(true);
	if (joy.x < -10000)
	{
		m_Actor->Notify("Left");
	}
}

