#pragma once
#include "Singleton.h"
namespace Crusade
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render();
		void SetCurrentScene(const std::string& sceneName);
		std::shared_ptr<Scene> GetCurrentScene()const { return m_CurrentScene; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene{};
	};
}
