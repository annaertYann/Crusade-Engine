#include "MiniginPCH.h"
#include "LevelFinisher.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Score.h"
#include "Lives.h"
#include "Levels.h"
void LevelFinisher::Start()
{
	const auto list = Crusade::SceneManager::GetInstance().GetCurrentScene()->FindAllObjectsWithTag("Cube");
	m_NumberOfCubes = int(list.size());
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
	if (m_CurrentTriggeredCubes==m_NumberOfCubes)
	{
		FinishLevel();
	}
}
void LevelFinisher::FinishLevel()const
{
	auto &sceneManager = Crusade::SceneManager::GetInstance();
	auto previousScene = sceneManager.GetCurrentScene();
	sceneManager.LoadScene(m_NextLevelName);
	auto nextScene = sceneManager.GetCurrentScene();


	//ADJUST OBSERVERS IF NEEDED
	if (nextScene->FindObject("ScoreDisplay"))
	{
		auto score1 = nextScene->FindObject("ScoreDisplay")->GetComponent<Score>();
		const auto score2 = previousScene->FindObject("ScoreDisplay")->GetComponent<Score>();
		score1->SetScore(score2->GetScore());
		
	}
	if (nextScene->FindObject("LivesDisplay"))
	{
		nextScene->FindObject("LivesDisplay")->GetComponent<Lives>()->SetLives(previousScene->FindObject("LivesDisplay")->GetComponent<Lives>()->GetLives());
	}
}