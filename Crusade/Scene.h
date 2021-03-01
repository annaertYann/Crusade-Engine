#pragma once
#include "SceneManager.h"

namespace Crusade
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		
		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		void Render() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::shared_ptr<GameObject> FindObject(const std::string& name);
		std::vector<std::shared_ptr<GameObject>> FindAllObjectsWithTag(const std::string& tag);
		std::string GetName()const { return m_Name; }
	
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};
}
