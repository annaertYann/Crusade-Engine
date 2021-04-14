#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"
namespace Crusade
{
	class CTransform final : public Component
	{
	public:
		CTransform() = default;
		CTransform(const glm::vec3 &position , const glm::vec3& rotation ,const glm::vec3& scale={1,1,1} );
		
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(float x, float y, float z);

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);

		void Translate(const glm::vec3& translation);
		void Rotate(const glm::vec3& rotation);
		void Scale(const glm::vec3& scale);
	private:
		void OnCollisionEnter(CCollider*) override;
		void OnCollisionExit(CCollider*) override;
		glm::vec3 m_Position{};
		glm::vec3 m_Rotation{};
		glm::vec3 m_Scale= {1,1,1};
	
	};
}
