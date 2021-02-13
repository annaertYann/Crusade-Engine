#include "MiniginPCH.h"
#include "Transform.h"
using namespace Crusade;
void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
void Transform::SetRotation(const float x, const float y, const float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}
void Transform::SetScale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
Transform::Transform(GameObject* owner)
	:Component(owner)
{
	m_Scale.x = 1;
	m_Scale.y = 1;
	m_Scale.z = 1;
}