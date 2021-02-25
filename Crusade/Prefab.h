#pragma once
#include "GameObject.h"
#include "Singleton.h"
namespace Crusade
{
	template <typename T>
	class Prefab
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}
		virtual ~Prefab() = default;

		Prefab(const Prefab& other) = delete;
		Prefab(Prefab&& other) = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) = delete;
		
		virtual std::shared_ptr<GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale={1,1,1}) = 0;
	protected:
		Prefab() = default;
	};
}
