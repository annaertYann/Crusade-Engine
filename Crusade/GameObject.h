#pragma once
#include "BaseComponent.h"
namespace Crusade
{
	class GameObject final
	{
	public:

		GameObject() = default;
		~GameObject()=default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void SendCommand(const Component::Command& command);

		//COMPONENT CONTROL
		std::vector<std::shared_ptr<Component>> GetAllComponents() const{ return m_components; }
		void AddComponent(const std::shared_ptr<Component> component) { m_components.push_back(component); };
		template <typename T>
		T* GetComponent();
	
	private:
		std::vector<std::shared_ptr<Component>> m_components{};
	};
	
	template <typename T>
	T* GameObject::GetComponent()
	{
		for (const auto& component : m_components)
		{
			T* temp = dynamic_cast<T*>(component.get());
			if (temp != nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}
}

