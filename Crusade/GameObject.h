#pragma once
#include "BaseComponent.h"
namespace Crusade
{
	class GameObject final
	{
	public:

		GameObject();
		~GameObject()=default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void SendCommand(const Component::Command& command);
		int GetTag()const { return m_Tag; }
		//HANDLE CHILDREN
		void AddChild(const std::shared_ptr<GameObject> &object) { m_Children.push_back(object); }
		//COMPONENT CONTROL
		std::vector<std::shared_ptr<Component>> GetAllComponents() const{ return m_Components; }
		template <typename T>
		void AddComponent(const std::shared_ptr<Component>& component);
		template <typename T>
		T* GetComponent();
	
	private:
		std::vector<std::shared_ptr<Component>> m_Components{};
		std::vector<std::shared_ptr<GameObject>> m_Children{};
		int m_Tag;
		static int m_NextTag;
	};
	
	template <typename T>
	T* GameObject::GetComponent()
	{
		for (const auto& component : m_Components)
		{
			T* temp = dynamic_cast<T*>(component.get());
			if (temp != nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}
	template <typename T>
	void GameObject::AddComponent(const std::shared_ptr<Component>& component)
	{
		if (GetComponent<T>()==nullptr)
		{
			component->SetOwner(this);
			component->Init();
			m_Components.push_back(component);
		}
	}
}

