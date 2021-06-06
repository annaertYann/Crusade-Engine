#include "MiniginPCH.h"
#include "Buttons.h"
#include "SceneManager.h"
#include "Levels.h"
void SinglePlayerLoad::Execute()
{
	Crusade::SceneManager::GetInstance().LoadScene("Qbert1");
}
void CoopLoad::Execute()
{
	auto& sceneManager = Crusade::SceneManager::GetInstance();
	sceneManager.SetCurrentScene("Qbert1");
	auto scene = sceneManager.GetCurrentScene();
	dynamic_cast<Level*>(scene.get())->SetMode(Level::Mode::coop);
	Crusade::SceneManager::GetInstance().LoadScene("Qbert1");
}
void VersusLoad::Execute()
{
	auto& sceneManager = Crusade::SceneManager::GetInstance();
	sceneManager.SetCurrentScene("Qbert1");
	auto scene = sceneManager.GetCurrentScene();
	dynamic_cast<Level*>(scene.get())->SetMode(Level::Mode::verus);
	Crusade::SceneManager::GetInstance().LoadScene("Qbert1");
}
