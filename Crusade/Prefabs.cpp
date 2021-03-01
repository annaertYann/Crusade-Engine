#include "MiniginPCH.h"
#include "Prefabs.h"
#include "InputManager.h"
#include "Scripts.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Animator2D.h"
using namespace Crusade;
/////////////////////////////////////////////////////////////////////////////////
//QBERT
/////////////////////////////////////////////////////////////////////////////////
void QBertDied::Execute()
{
	Publisher::GetInstance().Notify(m_Actor, "QBertDied");
	m_Actor->GetComponent<Animator2D>()->TriggerTransition("Explosion");
	std::cout << "QBertDied" << std::endl;
}
void QBertGainedPoints::Execute()
{
	int x{rand()%4};
	switch (x)
	{
	case 0:
		Publisher::GetInstance().Notify(m_Actor, "ColorChange");
		std::cout << "ColorChange" << std::endl;
		break;
	case 1:
		Publisher::GetInstance().Notify(m_Actor, "CoilyKill");
		std::cout << "CoilyKill" << std::endl;
		break;
	case 2:
		Publisher::GetInstance().Notify(m_Actor, "DiscRemain");
		std::cout << "DiscRemain" << std::endl;
		break;
	case 3:
		Publisher::GetInstance().Notify(m_Actor, "CatchSlickSam");
		std::cout << "CatchSlickSam" << std::endl;
		break;
	}
	
}
std::shared_ptr<GameObject> QBert::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
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
	const auto animator = std::make_shared<Animator2D>(animJump, glm::vec2{ 50, 50 });
	//TRANSITIONS
	const std::shared_ptr<bool>explosionCondition{new bool{}};
	animator->AddTransition(new Transition{ animJump,animIdle,"",true });
	animator->AddTransition(new Transition{ animIdle,animBackJump,"",true });
	animator->AddTransition(new Transition{ animBackJump,animBackIdle,"",true });
	animator->AddTransition(new Transition{ animBackIdle,animJump,"",true });
	
	animator->AddTransition(new Transition{ animIdle,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animBackIdle,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animBackJump,explosion,"Explosion",false,explosionCondition });
	animator->AddTransition(new Transition{ animJump,explosion,"Explosion",false,explosionCondition });
	
	animator->AddTransition(new Transition{ explosion,animJump,"",true});
	
	qBert->AddComponent<Animator2D>(animator);
	return qBert;
}


/////////////////////////////////////////////////////////////////////////////////
//LIVES DISPLAY
/////////////////////////////////////////////////////////////////////////////////
void LivesCounter::Start()
{
	auto text = m_Owner->GetComponent<CTextRender>();
	if (text)
	{
		text->SetText("Lives: " + std::to_string(m_Lives));
	}
	m_Delay.Stop();
}
void LivesCounter::Notify(GameObject*, const std::string& message)
{
	if (message=="QBertDied")
	{
		m_Lives--;
		if (m_Lives > 0)
		{
			auto text = m_Owner->GetComponent<CTextRender>();
			if (text)
			{
				text->SetText("Lives: " + std::to_string(m_Lives));
			}
		}
		else
		{
			m_Delay.Start();
			auto text = m_Owner->GetComponent<CTextRender>();
			if (text)
			{
				text->SetText("Lives: 0");
			}
			//DEFEAT SCREEN OR SOMETHING
			////////////////
			////////////////
		}
	}
}
void LivesCounter::Update()
{
	if(m_Delay.Update(Time::GetInstance().GetDeltaTime()))
	{
		auto players = SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Player");
		for (auto player : players)
		{
			player->SetRemove();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//POINTS COUNTER
/////////////////////////////////////////////////////////////////////////////////
void PointsCounter::Notify(GameObject*, const std::string& message)
{
	bool changed{};
	if (message == "ColorChange")
	{
		m_Points += 25;
		changed = true;
	}
	else
		if (message == "CoilyKill")
		{
			m_Points += 500;
			changed = true;
		}
		else
			if (message == "DiscRemain")
			{
				m_Points += 50;
				changed = true;
			}
			else
				if (message == "CatchSlickSam")
				{
					m_Points += 300;
					changed = true;
				}
	if (changed)
	{
		auto text = m_Owner->GetComponent<CTextRender>();
		if (text)
		{
			text->SetText("Score: "+std::to_string(m_Points));
		}
	}
}
