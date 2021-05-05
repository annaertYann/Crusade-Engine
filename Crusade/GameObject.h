#pragma once
#include "BaseComponent.h"
#include "RenderComponents.h"
#include "CTransform.h"
#include "CRigidBody2D.h"
namespace Crusade
{
	class Component;
	class GameObject final
	{
		friend class CRigidBody2D;
	public:
		GameObject();
		~GameObject()=default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		//CONTROL TAG
		void SetName(const std::string& name) { m_Name = name; }
		std::string GetName()const { return m_Name; }
		std::vector<std::string>& GetTags() { return m_Tags; }
		void AddTag(const std::string& tag) { m_Tags.push_back(tag); }
		
		int GetObjectNummer()const { return m_ObjectNummer; }
		//REMOVE FUNCTIONALITY
		void SetRemove() { m_Remove = true; }
		bool GetRemove()const { return m_Remove; }
		//HANDLE CHILDREN
		void AddChild(const std::shared_ptr<GameObject> &object) { m_Children.push_back(object); }
		//COMPONENT CONTROL
		void Notify(const std::string& message);
		std::vector<std::shared_ptr<Component>>& GetAllComponents() { return m_Components; }
		CRender* GetCRender() const{ return m_CRender; }
		CTransform* GetCTransform() const { return m_CTransform; }
		template <typename T>
		void AddComponent(const std::shared_ptr<Component>& component);
		template <typename T>
		T* GetComponent();
		template <typename T>
		void RemoveComponent();
	private:
		void OnTriggerEnter(CCollider* trigger);
		void OnCollisionEnter(CCollider* collider);
		void OnTriggerExit(CCollider* trigger);
		void OnCollisionExit(CCollider* collider);
		std::vector<std::shared_ptr<Component>> m_Components{};
		std::vector<std::shared_ptr<GameObject>> m_Children{};
		//OBJECT TAG
		std::string m_Name{};
		int m_ObjectNummer=-1;
		static int m_NextNameTag;
		std::vector<std::string> m_Tags;
		//REMOVE FUNCTIONALITY
		bool m_Remove=false;
		//START OBJECT
		bool m_Start = false;
		//COMMON COMPONENTS
		CRender* m_CRender=nullptr;
		CTransform* m_CTransform=nullptr;
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
			component->Awake();
			if (dynamic_cast<CRender*>(component.get()) != nullptr) { m_CRender = dynamic_cast<CRender*>(component.get()); }
			if (dynamic_cast<CTransform*>(component.get()) != nullptr) { m_CTransform = dynamic_cast<CTransform*>(component.get()); }
			m_Components.push_back(component);
		}
		else
		{
			std::cout << "CANT ADD COMPONENT,COMPONENT ALREADY EXISTS :ADDCOMPONENT" << std::endl;
		}
		
	}

	template <typename T>
	void GameObject::RemoveComponent()
	{
		//REMOVED COMPONENTS GET ADDED TO REMOVED LIST
		if (m_Components.size() > 0)
		{
			m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(), [&](const std::shared_ptr<Component>& component)
			{
				T* temp = dynamic_cast<T*>(component.get());
				if (temp != nullptr)
				{
					
					return true;
				}
				return false;
			}), m_Components.end());
		}
	}
}

