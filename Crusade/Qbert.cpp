#include "MiniginPCH.h"
#include "Qbert.h"
#include "CAnimator2D.h"
#include "CTransform.h"
#include "MovementSteering.h"
#include "PlayerController.h"
#include "SceneManager.h"
using namespace Crusade;
std::shared_ptr<GameObject> QBert::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> qbert{ std::make_shared<GameObject>()};
	qbert->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	qbert->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Qbert/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("Qbert/Jump.png", 2, 8.f,true);
	const auto animBackIdle = std::make_shared<Animation>("Qbert/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("Qbert/JumpBack.png",2, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animJump, glm::vec2{ 40, 40 });
	qbert->AddComponent<QbertAnimationTriggerer>(std::make_shared<QbertAnimationTriggerer>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };
	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition});
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });
	qbert->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	qbert->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f,Vector2f{0,300.f})));
	qbert->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	qbert->AddComponent<QbertController>(std::make_shared<QbertController>());
	//col
	auto rigid  = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	qbert->AddComponent<CRigidBody2D>(rigid);
	auto col =  std::make_shared<CRectCollider>(Rectf{ 0,0,40,40 });
	col->SetIsTrigger(true);
	qbert->AddComponent<CCollider>(col);
	qbert->SetName("Qbert");
	return qbert;
}
void QbertAnimationTriggerer::Start()
{
	m_Animator = m_Owner->GetComponent<CAnimator2D>();
	m_Render = m_Owner->GetComponent<CRender>();
}
void QbertAnimationTriggerer::Notify(const std::string& message)
{
	if (message=="JumpFront")
	{
		m_IsBack = false;
		m_Animator->TriggerTransition(message);
	}
	else if(message == "JumpBack")
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
}

void QbertController::Start()
{
	const auto publisher = std::make_shared<Publisher>();
	m_Owner->AddComponent<Publisher>(publisher);
	m_Publisher = publisher.get();
	m_Publisher->AddObserver(SceneManager::GetInstance().GetCurrentScene()->FindObject("LivesDisplay").get());
	m_Movement = m_Owner->GetComponent<CharacterMovement>();
	
}

void QbertController::Update()
{
	m_Movement->TriggerCurrentCube();
}

void QbertController::Notify(const std::string& message)
{
	if (message == "DiscStart")
	{
	 m_Movement->ResetDeathAnim();
	}
	else if (message == "DiscEnd")
	{
		m_Movement->ResetToStart();
	}
	else if (message == "Death")
	{
		m_Publisher->SendNotification("Death");
		m_Movement->Die();
	}
}
void QbertController::AddKeyBoardControls()
{
	auto upMovementKey = new UpMovementKey{ m_Owner };
	auto downMovementKey = new DownMovementKey{ m_Owner };
	auto rightMovementKey = new RightMovementKey{ m_Owner };
	auto leftMovementKey = new LeftMovementKey{ m_Owner };
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<UpMovementKey>(upMovementKey),m_Counter,-1 ,SDL_SCANCODE_UP });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<DownMovementKey>(downMovementKey),m_Counter,-1,SDL_SCANCODE_DOWN });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<RightMovementKey>(rightMovementKey),m_Counter,-1,SDL_SCANCODE_RIGHT });
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::unique_ptr<LeftMovementKey>(leftMovementKey),m_Counter,-1,SDL_SCANCODE_LEFT });
	m_UpSwitch = InputManager::GetInstance().CreateCommandKillSwitch(upMovementKey);
	m_DownSwitch = InputManager::GetInstance().CreateCommandKillSwitch(downMovementKey);
	m_RightSwitch = InputManager::GetInstance().CreateCommandKillSwitch(rightMovementKey);
	m_LeftSwitch = InputManager::GetInstance().CreateCommandKillSwitch(leftMovementKey);
}

void QbertController::AddJoystickControls()
{
	auto upMovementKey = new UpMovementTrigger{ m_Owner };
	auto downMovementKey = new DownMovementTrigger{ m_Owner };
	auto rightMovementKey = new RightMovementTrigger{ m_Owner };
	auto leftMovementKey = new LeftMovementTrigger{ m_Owner };
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<UpMovementTrigger>(upMovementKey),m_Counter });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<DownMovementTrigger>(downMovementKey),m_Counter });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<RightMovementTrigger>(rightMovementKey),m_Counter });
	InputManager::GetInstance().AddTriggerInput(new InputTriggerAction{ TriggerType::controllerLeftJoyStick,std::unique_ptr<LeftMovementTrigger>(leftMovementKey),m_Counter });
	m_UpSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(upMovementKey);
	m_DownSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(downMovementKey);
	m_RightSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(rightMovementKey);
	m_LeftSwitchTrigger = InputManager::GetInstance().CreateCommandKillSwitch(leftMovementKey);
}
