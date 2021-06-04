#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
#include "CTransform.h"
#include "Colliders2D.h"
#include "Delay.h"
namespace Crusade
{
	class CRigidBody2D final :public Component
	{
	public:
		void FixedUpdate() override;
		void Update() override;
		void AddForce(const glm::vec2& force) { m_Velocity += force; }

		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		glm::vec2 GetVelocity()const { return m_Velocity; }

		void SetGravityEnabled(const bool& x) { m_IsGravityEnabled = x; }
		void SetGravity(const float& acceleration) { m_Gravity.y = acceleration; }
		void SetAirFriction(const glm::vec2 friction) { m_AirFriction = friction; }

		CCollider* GetAttachedCollider()const { return m_AttachedCollider; }
		void SetIsStatic(const bool& x) { m_IsStatic = x; }
	private:
		void Start() override;
		void DoCollisions();
		void Bounce(const utils::HitInfo& info,const bool& reverse);
		void ApplyCollision(const utils::HitInfo& info,CCollider* col);
		bool IsObjectColliding(const int& tag);
		void RemoveFromIsCollidingList(const int& tag);
		std::vector<int>m_CollidingObjectTags;
		CTransform* m_Transform = nullptr;
		CCollider* m_AttachedCollider{};
		glm::vec2 m_Velocity{};
		glm::vec2 m_AirFriction{100,100};
		glm::vec2 m_Gravity{0,-400};
		Delay m_BounceDelay{0.1f};
		float m_Bounciness = 0.4f;
		bool m_IsGravityEnabled=true;
		bool m_IsStatic = false;
		bool m_IsColliding = false;
	};
}