#include "MiniginPCH.h"
#include "SceneManager.h"

#include "GameObject.h"
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

void Crusade::SceneManager::LoadScene(const std::string& sceneName)
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == sceneName)
		{
			m_CurrentScene = scene;
			for (auto obj : m_CurrentScene->GetAllObjects())
			{
				obj->SetRemove();
			}
			m_CurrentScene->Load();
			return;
		}
	}
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
