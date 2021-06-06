#pragma once
#include <cassert>
#include "Scene.h"
#include "Singleton.h"
#pragma warning (disable:26816)
namespace Crusade
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		template <typename T>
		Scene& CreateScene(const std::string& name);
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render();
		void SetCurrentScene(const std::string& sceneName);
		void LoadScene(const std::string& sceneName);
		std::shared_ptr<Scene> GetCurrentScene()const { return m_CurrentScene; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene{};
	};
	
	template <typename T>
	Scene& SceneManager::CreateScene(const std::string& name)
	{
		static_assert(std::is_base_of<Scene, T>::value, "Creating new scene requires valid scene dervivative ");
		for (const auto& scene : m_Scenes)
		{
			const auto x = scene->GetName() == name;
			if (x) { std::cout << "Scene Name Already Used: "+scene->GetName() << std::endl; }
			assert(!x);
		}
		Scene* p =  new T();
		p->SetName(name);
		const auto scene = std::shared_ptr<Scene>(p);
		m_Scenes.push_back(scene);
		m_CurrentScene = scene;
		return *scene;
	}
}
