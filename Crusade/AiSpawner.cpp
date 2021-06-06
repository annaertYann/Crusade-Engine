#include "MiniginPCH.h"
#include "AiSpawner.h"
#include "Time.h"
#include "SceneManager.h"
#include "Ai.h"
#include "PlayerController.h"
using namespace Crusade;
void AiSpawner::Update()
{
	auto deltaTime = Time::GetInstance().GetDeltaTime();
	if(m_SpawnDelay.Update(deltaTime))
	{
		m_SpawnDelay.Start();
		spawnMonster();
	}
}
void AiSpawner::spawnMonster()
{
	bool done = false;
	int number = rand() % int(Monsters::END);
	int tries = 0;
	if(!m_CoilySpawned)
	{
		number = int(Monsters::coily);
		m_CoilySpawned = true;
	}
	while (!done)
	{
		switch (Monsters(number))
		{
		case Monsters::coily:
			if (!IsMonsterInList("Coily"))
			{
				const auto obj = Coily::GetInstance().CreateObject(m_Owner->GetCTransform()->GetPosition());
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
				done = true;
			}
			tries++;
			break;
		case Monsters::ugg:
			if (!IsMonsterInList("Ugg"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = Ugg::GetInstance().CreateObject({ 0,pos.y / 4,pos.z });
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
				done = true;
			}
			tries++;
			break;
		case Monsters::wrongway:
			if (!IsMonsterInList("WrongWay"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = WrongWay::GetInstance().CreateObject({ pos.x * 2,pos.y / 4,pos.z });
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
				done = true;
			}
			tries++;
			break;
		case Monsters::slick:
			if (!IsMonsterInList("Slick"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = Slick::GetInstance().CreateObject(m_Owner->GetCTransform()->GetPosition());
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
				done = true;
			}
			tries++;
			break;
		case Monsters::sam:
			if (!IsMonsterInList("Sam"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = Sam::GetInstance().CreateObject(m_Owner->GetCTransform()->GetPosition());
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
				done = true;
			}
			tries++;
			break;
		case Monsters::END:
			break;
		default:;
		}
		if(tries>int(Monsters::END))
		{
			done = tries > int(Monsters::END) - 1;
		}
		number = rand() % int(Monsters::END);
	}
}

void AiSpawner::LateUpdate()
{
	//REMOVE DEAD OBJECTS FROM OBJECTLIST
	if (m_Ai.size() > 0)
	{
		m_Ai.erase(std::remove_if(m_Ai.begin(), m_Ai.end(), [&](const GameObject* object)
		{
			return object->GetRemove();
		}), m_Ai.end());
	}
}

bool AiSpawner::IsMonsterInList(const std::string& name)
{
	for(auto obj : m_Ai)
	{
		if(obj->GetName()==name)
		{
			return true;
		}
	}
	return false;
}
