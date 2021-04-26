#pragma once
namespace Crusade
{
	class GameObject;
	class CCollider;
	class Component
	{
	public:
		explicit Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		GameObject* GetOwner()const { return m_Owner; }
		
		virtual void FixedUpdate(){}
		virtual void Update(){}
		virtual void LateUpdate(){}
		virtual void Render()const{}
		friend class GameObject;
	
	protected:
		GameObject* m_Owner = nullptr;
	
	private:
		virtual void Notify(const std::string&) {}
		virtual void OnTriggerEnter(CCollider* ){}
		virtual void OnCollisionEnter(CCollider*) { }
		virtual void OnTriggerExit(CCollider*) {}
		virtual void OnCollisionExit(CCollider*) { }
		virtual void Awake(){}//HAPPENS RIHT AFTER COMPONENTS GETS ADDED TO THE OBJECT // NOT ALL COMPONENTS MAY BE ADDED ALREADY
		virtual void Start(){}//HAPPENS RIGHT BEFORE THE FIRST UPDATE
		void SetOwner(GameObject* owner) { m_Owner = owner; }
	};
}

