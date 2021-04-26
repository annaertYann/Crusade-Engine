#include "MiniginPCH.h"
#include "Prefabs.h"
#include "InputManager.h"
#include "Scripts.h"
#include "CRigidBody2D.h"
#include "Scene.h"
#include "SceneManager.h"
#include "CAnimator2D.h"
#include "Camera2D.h"
#include "ServiceLocator.h"
using namespace Crusade;
/////////////////////////////////////////////////////////////////////////////////
//QBERT
/////////////////////////////////////////////////////////////////////////////////
void QBertDied::Execute()
{
	Publisher::GetInstance().Notify(m_Actor, "QBertDied");
	m_Actor->GetComponent<CAnimator2D>()->TriggerTransition("Explosion");
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
void MoveUp::Execute()
{
	auto rigid = m_Actor->GetComponent<CRigidBody2D>();
	if (rigid)
	{
		rigid->SetVelocity({0,50});
	}
}
void MoveDown::Execute()
{
	auto rigid = m_Actor->GetComponent<CRigidBody2D>();
	if (rigid)
	{
		rigid->SetVelocity({ 0,-50 });
	}
}
void MoveRight::Execute()
{
	auto rigid = m_Actor->GetComponent<CRigidBody2D>();
	if (rigid)
	{
		rigid->SetVelocity({ 50,0 });
	}
}
void MoveLeft::Execute()
{
	auto rigid = m_Actor->GetComponent<CRigidBody2D>();
	if (rigid)
	{
		rigid->SetVelocity({ -50,0 });
	}
}
/////////////////////////////////////////////////////////////////////////////////
//LIVES DISPLAY
/////////////////////////////////////////////////////////////////////////////////
void LivesCounter::Awake()
{
	auto text = m_Owner->GetComponent<CTextRender>();
	if (text)
	{
		text->SetText("Lives: " + std::to_string(m_Lives));
	}
	m_Delay.Stop();
	m_BonkSoundID = ServiceLocator::GetSoundSystem()->RegisterSound("../Data/Bonk.mp3");
}
void LivesCounter::Notify(GameObject*, const std::string& message)
{
	if (message=="QBertDied")
	{
		ServiceLocator::GetSoundSystem()->play(m_BonkSoundID, 10);
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
