#include "MiniginPCH.h"
#include "QBertTest.h"
#include "InputManager.h"
#include "CRigidBody2D.h"
#include "CAnimator2D.h"
#include "Camera2D.h"
#include "Scripts.h"
using namespace Crusade;
std::shared_ptr<GameObject> QBertTest::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto qBert = std::make_shared<GameObject>();
	qBert->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	qBert->AddComponent<QbertController>(std::make_shared<QbertController>(SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2));
	//ANIMATIONS
	const auto animIdle = std::make_shared<Animation>("Qbert/Idle.png", 1, 1.f, false);
	const auto animJump = std::make_shared<Animation>("Qbert/Jump.png", 2, 2.f, true);
	const auto animBackIdle = std::make_shared<Animation>("Qbert/IdleBack.png", 1, 1.f, false);
	const auto animBackJump = std::make_shared<Animation>("Qbert/JumpBack.png", 2, 2.f, true);
	const auto explosion = std::make_shared<Animation>("Qbert/Explosion.png", 1, 8, 10.f, true);
	//ANIMATOR
	const auto animator = std::make_shared<CAnimator2D>(animJump, glm::vec2{ 50, 50 });
	//TRANSITIONS
	const std::shared_ptr<bool>explosionCondition{ new bool{} };
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"",true });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",true });

	animator->AddTransition(new Transition{ animIdle,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animBackIdle,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animBackJump,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animJump,explosion,"Explosion",false,explosionCondition });

	animator->AddTransition(new Transition{ explosion,animJump,"",true });

	qBert->AddComponent<CAnimator2D>(animator);
	return qBert;
}