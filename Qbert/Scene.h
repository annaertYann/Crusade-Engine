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
		void Add(const std::vector<std::shared_ptr<GameObject>>&objects);
		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		void Render() const;

		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::shared_ptr<GameObject> FindObject(const std::string& name);
		std::vector< std::shared_ptr<GameObject>> FindAllObjects(const std::string& name);
		std::vector<std::shared_ptr<GameObject>> FindAllObjectsWithTag(const std::string& tag);
		std::vector<std::shared_ptr<GameObject>>& GetCollisionObjects() { return m_CollisionObjects; }
		std::vector < std::shared_ptr<GameObject>>& GetAllObjects() { return m_Objects; }
		std::string GetName()const { return m_Name; }

	protected:
		explicit Scene();
	private:
		void DeleteObjectsToBeAdded() { m_ObjectsToBeAdded.clear(); }
		void SetName(const std::string& name) { m_Name = name; }
		void AddCamera();
		virtual void Load() = 0;
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_CollisionObjects{};
		std::vector < std::shared_ptr<GameObject>> m_ObjectsToBeAdded{};
		static unsigned int m_IdCounter; 
	};
	class DefaultScene final :public Scene
	{
	private:
		void Load() override {}
	};
}
