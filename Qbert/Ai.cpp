#include "MiniginPCH.h"
#include "Ai.h"
#include "Qbert.h"
#include "CAnimator2D.h"
#include "CharacterAnimationTrigger.h"
#include "CTransform.h"
#include "MovementSteering.h"
#include "PlayerController.h"
#include "SceneManager.h"
#include "AIMovements.h"
#include "AiSpawner.h"
using namespace Crusade;
std::shared_ptr<GameObject> Coily::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

	std::shared_ptr<GameObject> coily{ std::make_shared<GameObject>() };
	coily->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	coily->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	coily->AddComponent<Publisher>(std::make_shared<Publisher>());
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Coily/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("Coily/JumpFront.png", 2, 8.f, true);
	const auto animBackIdle = std::make_shared<Animation>("Coily/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("Coily/JumpBack.png", 2, 8.f, true);
	const auto animIdleEgg = std::make_shared<Animation>("Coily/EggIdle.png", 1, 10.f, false);
	const auto animJumpEgg = std::make_shared<Animation>("Coily/EggJump.png", 2, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animIdleEgg, glm::vec2{ 40, 40 });
	coily->AddComponent<CharacterAnimationTrigger>(std::make_shared<CharacterAnimationTrigger>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };
	
	animator->AddTransition(new Transition{ animIdleEgg,animJumpEgg,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJumpEgg,animIdleEgg,"",true });
	animator->AddTransition(new Transition{ animIdleEgg,animIdle,"Transform",true ,std::make_shared<bool>()});
	
	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });
	
	coily->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	coily->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f, Vector2f{ 0,300.f })));
	coily->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	coily->AddComponent<CoilyMovement>(std::make_shared<CoilyMovement>());
	//col
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	coily->AddComponent<CRigidBody2D>(rigid);
	auto col = std::make_shared<CRectCollider>(Rectf{ 10,10,10,10 });
	col->SetIsTrigger(true);
	coily->AddComponent<CCollider>(col);
	coily->SetName("Coily");
	return coily;
}
std::shared_ptr<Crusade::GameObject> Ugg::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> ugg{ std::make_shared<GameObject>() };
	ugg->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	ugg->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	ugg->AddComponent<Publisher>(std::make_shared<Publisher>());
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Ugg/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("Ugg/JumpFront.png", 2, 8.f, true);
	const auto animBackIdle = std::make_shared<Animation>("Ugg/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("Ugg/JumpBack.png", 2, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animIdle, glm::vec2{ 40, 40 });
	ugg->AddComponent<CharacterAnimationTrigger>(std::make_shared<CharacterAnimationTrigger>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };

	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });

	ugg->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	ugg->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f, Vector2f{ 0,300.f })));
	ugg->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	ugg->AddComponent<UggMovement>(std::make_shared<UggMovement>());
	//col
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	ugg->AddComponent<CRigidBody2D>(rigid);
	auto col = std::make_shared<CRectCollider>(Rectf{ 10,10,10,10 });
	col->SetIsTrigger(true);
	ugg->AddComponent<CCollider>(col);
	ugg->SetName("Ugg");
	return ugg;
}
std::shared_ptr<Crusade::GameObject> WrongWay::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> wrongWay{ std::make_shared<GameObject>() };
	wrongWay->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	wrongWay->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	wrongWay->AddComponent<Publisher>(std::make_shared<Publisher>());
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("WrongWay/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("WrongWay/JumpFront.png", 4, 8.f, true);
	const auto animBackIdle = std::make_shared<Animation>("WrongWay/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("WrongWay/JumpBack.png", 4, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animIdle, glm::vec2{ 40, 40 });
	wrongWay->AddComponent<CharacterAnimationTrigger>(std::make_shared<CharacterAnimationTrigger>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };
	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });

	wrongWay->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	wrongWay->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f, Vector2f{ 0,300.f })));
	wrongWay->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	wrongWay->AddComponent<WrongWayMovement>(std::make_shared<WrongWayMovement>());
	//col
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	wrongWay->AddComponent<CRigidBody2D>(rigid);
	auto col = std::make_shared<CRectCollider>(Rectf{ 10,10,10,10 });
	col->SetIsTrigger(true);
	wrongWay->AddComponent<CCollider>(col);
	wrongWay->SetName("WrongWay");
	return wrongWay;
}
std::shared_ptr<Crusade::GameObject> Slick::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> slick{ std::make_shared<GameObject>() };
	slick->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	slick->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	slick->AddComponent<Publisher>(std::make_shared<Publisher>());
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Slick/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("Slick/JumpFront.png", 4, 8.f, true);
	const auto animBackIdle = std::make_shared<Animation>("Slick/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("Slick/JumpBack.png", 4, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animIdle, glm::vec2{ 40, 40 });
	slick->AddComponent<CharacterAnimationTrigger>(std::make_shared<CharacterAnimationTrigger>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };
	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });

	slick->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	slick->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f, Vector2f{ 0,300.f })));
	slick->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	slick->AddComponent<SlickMovement>(std::make_shared<SlickMovement>());
	//col
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	slick->AddComponent<CRigidBody2D>(rigid);
	auto col = std::make_shared<CRectCollider>(Rectf{ 10,10,10,10 });
	col->SetIsTrigger(true);
	slick->AddComponent<CCollider>(col);
	slick->SetName("Slick");
	return slick;
}
std::shared_ptr<Crusade::GameObject> Sam::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> sam{ std::make_shared<GameObject>() };
	sam->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	sam->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	sam->AddComponent<Publisher>(std::make_shared<Publisher>());
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Sam/Idle.png", 1, 10.f, false);
	const auto animJump = std::make_shared<Animation>("Sam/JumpFront.png", 4, 8.f, true);
	const auto animBackIdle = std::make_shared<Animation>("Sam/IdleBack.png", 1, 10.f, false);
	const auto animBackJump = std::make_shared<Animation>("Sam/JumpBack.png", 4, 8.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animIdle, glm::vec2{ 40, 40 });
	sam->AddComponent<CharacterAnimationTrigger>(std::make_shared<CharacterAnimationTrigger>());
	//TRANSITIONS
	const std::shared_ptr<bool>jumpFrontCondition{ new bool{} };
	const std::shared_ptr<bool>jumpBackCondition{ new bool{} };
	animator->AddTransition(new Transition{ animIdle,animJump,"JumpFront",false,jumpFrontCondition });
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"JumpBack",false,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animBackJump,"",false ,jumpBackCondition });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",false ,jumpFrontCondition });

	sam->AddComponent<CAnimator2D>(animator);
	//MOVEMENT
	sam->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>(200.f, Vector2f{ 0,300.f })));
	sam->AddComponent<CharacterMovement>(std::make_shared<CharacterMovement>(40.f));
	sam->AddComponent<SamMovement>(std::make_shared<SamMovement>());
	//col
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	sam->AddComponent<CRigidBody2D>(rigid);
	auto col = std::make_shared<CRectCollider>(Rectf{ 10,10,10,10 });
	col->SetIsTrigger(true);
	sam->AddComponent<CCollider>(col);
	sam->SetName("Sam");
	return sam;
}

std::shared_ptr<Crusade::GameObject> AISpawnerPrefab::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> coily{ std::make_shared<GameObject>() };
	coily->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	coily->AddComponent<AiSpawner>(std::make_shared<AiSpawner>());
	return coily;
	
}
