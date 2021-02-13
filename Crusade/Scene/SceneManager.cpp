#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#pragma warning( disable : 26816)
void Crusade::SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}
void Crusade::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}
void Crusade::SceneManager::LateUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate();
	}
}
void Crusade::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

Crusade::Scene& Crusade::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
