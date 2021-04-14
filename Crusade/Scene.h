#pragma once
#include "SceneManager.h"
namespace Crusade
{
	class GameObject;
	class Scene
	{
		friend class SceneManager;
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
		std::vector<std::shared_ptr<GameObject>> GetCollisionObjects()const { return m_CollisionObjects; }
		std::string GetName()const { return m_Name; }
	
	private:
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_CollisionObjects{};
		static unsigned int m_IdCounter; 
	};
}
