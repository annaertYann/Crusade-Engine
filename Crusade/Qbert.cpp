#include "MiniginPCH.h"
#include "Qbert.h"
#include "CAnimator2D.h"
#include "CTransform.h"
#include "MovementSteering.h"
#include "PlayerController.h"
using namespace Crusade;
std::shared_ptr<GameObject> QBert::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> qbert{ std::make_shared<GameObject>()};
	qbert->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
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
	qbert->AddComponent<PlayerControllerKeyBoard>(std::make_shared<PlayerControllerKeyBoard>(SDL_SCANCODE_UP,SDL_SCANCODE_DOWN,SDL_SCANCODE_LEFT,SDL_SCANCODE_RIGHT,40.f));
	//col
	auto rigid  = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	qbert->AddComponent<CRigidBody2D>(rigid);
	auto col =  std::make_shared<CRectCollider>(Rectf{ 0,0,40,40 });
	col->SetIsTrigger(true);
	qbert->AddComponent<CCollider>(col);
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
