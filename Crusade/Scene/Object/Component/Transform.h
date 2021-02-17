#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"
namespace Crusade
{
	class Transform final : public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(float x, float y, float z);

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale={1,1,1};
	
	};
}
