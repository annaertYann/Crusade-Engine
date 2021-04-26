#include "MiniginPCH.h"
#include "PlayerMovement.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace Crusade;
PlayerMovementKeyBoard::PlayerMovementKeyBoard(int UpButton, int DownButton, int LeftButton, int RightButton,float objectSize)
{
	m_UpButton = UpButton;
	m_DownButton = DownButton;
	m_RightButton = RightButton;
	m_LeftButton = LeftButton;
	m_ObjectSize = objectSize;
}
void PlayerMovementKeyBoard::Awake()
{
	m_DirectionChoiceDelay.Stop();
	m_MovementSteering = m_Owner->GetComponent<MovementSteering>();
	
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
void PlayerMovementKeyBoard::Start()
{
	auto cubes  = SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Cube");
	for (auto cube:cubes)
	{
		auto col = cube->GetComponent<CCollider>();
		m_Cubes.push_back(col);
	}
	m_CurrentCube = m_Cubes[0];
	auto target = m_CurrentCube->GetCenter();
	target.x -= m_ObjectSize/2;
	target.y += m_ObjectSize / 2;
	m_MovementSteering->SetTarget(Vector2f{ target});
}

void PlayerMovementKeyBoard::Update()
{
	auto& time = Time::GetInstance();
	if(m_DirectionChoiceDelay.Update(time.GetDeltaTime()))
	{
		utils::HitInfo info{};
		Point2f pos1{m_CurrentCube->GetCenter()};
		Point2f pos2{m_CurrentCube->GetCenter()};
		if(abs(m_Direction.x)<0.1f )
		{
			if(m_IsLeftSelected)
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
		pos2.x += m_Direction.x * m_CurrentCube->GetDimensions().x/2;
		pos2.y += m_Direction.y * m_CurrentCube->GetDimensions().x/2;
		for (auto cube:m_Cubes)
		{
			if (cube->GetOwner()->GetObjectNummer() != m_CurrentCube->GetOwner()->GetObjectNummer())
			{
				if (Raycast(cube->GetVertices(), pos1, pos2, info))
				{
					m_CurrentCube = cube;
					auto target = m_CurrentCube->GetCenter();
					target.x -= m_ObjectSize / 2;
					target.y += m_ObjectSize / 2;
					m_MovementSteering->SetTarget(Vector2f{ target });
					std::cout << "NEW TARGET SELECTED" << std::endl;
					NotifyObjectOfJump();
					m_Direction = Vector2f{};
					return;
				}
			}
		}
		m_Direction = Vector2f{};
		std::cout << "NO Target Found" << std::endl;
	}
}

void PlayerMovementKeyBoard::NotifyObjectOfJump()const
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

void PlayerMovementKeyBoard::Notify(const std::string& message)
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
