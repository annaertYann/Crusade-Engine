#pragma once
namespace Crusade
{
	class GameObject;
	class Component
	{
	public:
		enum class Command
		{
		};
		explicit Component() = default;
		virtual ~Component() = default;

		virtual void SendCommand(const Command&){};
		virtual void Init() {}
		virtual void Update(){}
		virtual void Render()const{}
		void SetOwner(GameObject* owner) { m_Owner = owner; };
		
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	protected:
		GameObject* m_Owner = nullptr;
	};
}

