#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
#include "CTransform.h"
namespace Crusade
{
	class CRigidBody2D final:public Component
	{
	public:
		void Start() override;
		void Update() override;
		void FixedUpdate() override;

		void AddForce(const glm::vec2& force) { m_Velocity += force; }

		
		void SetGravityEnabled(const bool& x) { m_IsGravityEnabled = x; }
		void SetGravity(const float& acceleration) { m_Gravity.y = acceleration; }
	private:
		CTransform* m_Transform=nullptr;
		glm::vec2 m_Velocity{};
		glm::vec2 m_Gravity{0,9.81f};
		bool m_IsGravityEnabled=true;
	};
}