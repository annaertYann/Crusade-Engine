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
		int number = rand() % int(Monsters::END);
		number = int(Monsters::wrongway);
		switch (Monsters(number))
		{
		case Monsters::coily:
			if (!IsMonsterInList("Coily"))
			{
				const auto obj = Coily::GetInstance().CreateObject(m_Owner->GetCTransform()->GetPosition());
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
			}
			break;
		case Monsters::ugg:
			if (!IsMonsterInList("Ugg"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = Ugg::GetInstance().CreateObject({0,pos.y / 4,pos.z});
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				obj->GetComponent<CharacterMovement>()->SetTargetToClosestCube();
				m_Ai.push_back(obj.get());
			}
			break;
		case Monsters::wrongway:
			if (!IsMonsterInList("WrongWay"))
			{
				auto pos = m_Owner->GetCTransform()->GetPosition();
				const auto obj = WrongWay::GetInstance().CreateObject({ pos.x*2,pos.y/4,pos.z });
				SceneManager::GetInstance().GetCurrentScene()->Add(obj);
				m_Ai.push_back(obj.get());
			}
			break;
		case Monsters::slick:
			break;
		case Monsters::sam:
			break;
		case Monsters::END:
			break;
		default: ;
		}
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
