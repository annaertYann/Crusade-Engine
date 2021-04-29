#include "MiniginPCH.h"
#include "PlayerController.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Qbert.h"
using namespace Crusade;
PlayerControllerKeyBoard::PlayerControllerKeyBoard(int UpButton, int DownButton, int LeftButton, int RightButton,float objectSize)
{
	m_UpButton = UpButton;
	m_DownButton = DownButton;
	m_RightButton = RightButton;
	m_LeftButton = LeftButton;
	m_ObjectSize = objectSize;
}
void PlayerControllerKeyBoard::Awake()
{
	m_DirectionChoiceDelay.Stop();
	m_DieDelay.Stop();
	m_MovementSteering = m_Owner->GetComponent<MovementSteering>();
	const auto publisher = std::make_shared<Publisher>();
	m_Owner->AddComponent<Publisher>(publisher);
	m_Publisher = publisher.get();
	//INPUT
	auto upMovementKey = new UpMovementKey{ m_Owner };
	auto downMovementKey = new DownMovementKey{ m_Owner };
	auto rightMovementKey = new RightMovementKey{ m_Owner };
	auto leftMovementKey = new LeftMovementKey{ m_Owner };
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<UpMovementKey>(upMovementKey),0,-1,m_UpButton });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<DownMovementKey>(downMovementKey),0,-1,m_DownButton });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<RightMovementKey>(rightMovementKey),0,-1,m_RightButton });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<LeftMovementKey>(leftMovementKey),0,-1,m_LeftButton });
	m_UpSwitch = InputManager::GetInstance().CreateCommandKillSwitch(upMovementKey);
	m_DownSwitch = InputManager::GetInstance().CreateCommandKillSwitch(downMovementKey);
	m_RightSwitch = InputManager::GetInstance().CreateCommandKillSwitch(rightMovementKey);
	m_LeftSwitch = InputManager::GetInstance().CreateCommandKillSwitch(leftMovementKey);
	
}
void PlayerControllerKeyBoard::Start()
{
	auto cubes  = SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Cube");
	for (auto cube:cubes)
	{
		auto col = cube->GetComponent<CCollider>();
		m_Cubes.push_back(col);
	}
	m_CurrentCube = m_Cubes[0];
	SetTargetToCurrentCube();
	m_RigidBody = m_Owner->GetComponent<CRigidBody2D>();
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("LivesDisplay").get());
	m_StartPos = m_Owner->GetCTransform()->GetPosition();
}
void PlayerControllerKeyBoard::Update()
{
	auto& time = Time::GetInstance();
	if(m_DirectionChoiceDelay.Update(time.GetDeltaTime())&&m_IsEnabled)
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
		m_RigidBody->SetGravityEnabled("true");
	}
	TriggerCurrentCube();
}
bool PlayerControllerKeyBoard::Move()
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
void PlayerControllerKeyBoard::SetTargetWhenNoCubeFound()
{
	if (!(abs(m_Direction.x) < 0.1f))
	{
		auto target = m_CurrentCube->GetCenter();
		target.x += m_Direction.x * m_ObjectSize;
		target.y += m_Direction.y * m_ObjectSize;
		m_MovementSteering->SetTarget(Vector2f{ target });
		NotifyObjectOfJump();
		m_IsEnabled = false;

		m_DieDelay.Start();
	}
	std::cout << "NO Target Found" << std::endl;
}
void PlayerControllerKeyBoard::TriggerCurrentCube()
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
void PlayerControllerKeyBoard::SetTargetToCurrentCube()const
{
	auto target = m_CurrentCube->GetCenter();
	target.x -= m_ObjectSize / 2;
	target.y += m_ObjectSize / 2;
	m_MovementSteering->SetTarget(Vector2f{ target });
	std::cout << "NEW TARGET SELECTED" << std::endl;
}
void PlayerControllerKeyBoard::NotifyObjectOfJump()const
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
void PlayerControllerKeyBoard::Notify(const std::string& message)
{
	if(message == "Up")
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
	else if (message == "DiscStart")
	{
		m_DieDelay.Reset();
		m_DieDelay.Stop();
	}
	else if (message == "DiscEnd")
	{
		ResetToStart();
	}
	else if (message == "Death")
	{
		m_Publisher->SendNotification("Death");
		m_Owner->GetCTransform()->SetPosition(m_StartPos.x, m_StartPos.y, m_StartPos.z);
		ResetToStart();
	}
}
void PlayerControllerKeyBoard::ResetToStart()
{
	m_IsEnabled = true;
	m_RigidBody->SetGravityEnabled(false);
	m_CurrentCube = m_Cubes[0];
	m_MovementSteering->SetMovementBehaviour(std::make_shared<Seek>(QBert::GetInstance().GetSpeed(), Vector2f{ }));
	m_DieDelay.Stop();
	m_DieDelay.Reset();
	SetTargetToCurrentCube();
	m_RigidBody->SetGravityEnabled(false);
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
