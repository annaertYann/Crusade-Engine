#include "MiniginPCH.h"
#include "LevelFinisher.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Score.h"
#include "Lives.h"
#include "Event.h"
void LevelFinisher::Start()
{
	const auto list = Crusade::SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Cube");
	m_NumberOfCubes = int(list.size());
	m_Owner->AddComponent<Crusade::Publisher>(std::make_shared<Crusade::Publisher>());
	m_Owner->GetComponent<Crusade::Publisher>()->AddObserver(Crusade::SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
	m_Owner->GetComponent<Crusade::Publisher>()->AddObserver(Crusade::SceneManager::GetInstance().GetCurrentScene()->FindObject("SoundPlayer").get());
	if(!m_HasStarted)
	{
		m_Owner->GetComponent<Crusade::Publisher>()->SendNotification("Begin");
		m_HasStarted = true;
	}
}
void LevelFinisher::RecieveNotification(Crusade::GameObject* , const std::string& message)
{
	if(message=="Triggered")
	{
		m_CurrentTriggeredCubes++;
	}
	if (message == "DeTriggered")
	{
		m_CurrentTriggeredCubes--;
	}
	
	if (m_CurrentTriggeredCubes >= m_NumberOfCubes)
	{
		FinishLevel();
	}
}
void LevelFinisher::FinishLevel()const
{
	auto &sceneManager = Crusade::SceneManager::GetInstance();
	auto previousScene = sceneManager.GetCurrentScene();
	auto disks = previousScene->FindAllObjects("Disk");
	for (auto disk:disks)
	{
		m_Owner->GetComponent<Crusade::Publisher>()->SendNotification("DiscRemain");
	}
	previousScene->FindObject("ScoreDisplay")->GetComponent<ScoreSave>()->Save();
	previousScene->FindObject("LivesDisplay")->GetComponent<LifeSave>()->Save();
	sceneManager.LoadScene(m_NextLevelName);
	m_Owner->GetComponent<Crusade::Publisher>()->SendNotification("Advance");
	auto nextScene = sceneManager.GetCurrentScene();
	
}