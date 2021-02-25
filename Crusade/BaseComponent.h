#pragma once
namespace Crusade
{
	class GameObject;
	class Component
	{
	public:
		explicit Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Message(const std::string&){};
		virtual void Update(){}
		virtual void Render()const{}
		
		friend class GameObject;
	
	protected:
		GameObject* m_Owner = nullptr;
	
	private:
		virtual void Start(){};
		void SetOwner(GameObject* owner) { m_Owner = owner; }
	};
}

