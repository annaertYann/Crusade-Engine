#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#pragma warning( disable : 26816)
void Crusade::SceneManager::FixedUpdate()
{
	m_CurrentScene->FixedUpdate();
}
void Crusade::SceneManager::Update()
{
	m_CurrentScene->Update();
}
void Crusade::SceneManager::LateUpdate()
{
	m_CurrentScene->LateUpdate();
}
void Crusade::SceneManager::Render()
{
	m_CurrentScene->Render();
}

Crusade::Scene& Crusade::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	if(m_CurrentScene.get()==nullptr)
	{
		m_CurrentScene = scene;
	}
	return *scene;
}
void Crusade::SceneManager::SetCurrentScene(const std::string& sceneName)
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName()==sceneName)
		{
			m_CurrentScene = scene;
			return;
		}
	}
}
