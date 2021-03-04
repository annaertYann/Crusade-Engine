#include "MiniginPCH.h"
#include "CTransform.h"
using namespace Crusade;
void CTransform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
void CTransform::SetRotation(const float x, const float y, const float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void CTransform::SetScale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void CTransform::Translate(const glm::vec3& translation)
{
	m_Position += translation;
}
CTransform::CTransform(const glm::vec3& position,const glm::vec3& rotation,const glm::vec3& scale)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}
void CTransform::Rotate(const glm::vec3& rotation)
{
	m_Rotation += rotation;
}
void CTransform::Scale(const glm::vec3& scale)
{
	m_Scale += scale;
	m_Position.x -= scale.x / 2;
	m_Position.y -= scale.y / 2;
	m_Position.z -= scale.z / 2;
}
