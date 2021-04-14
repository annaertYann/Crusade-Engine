#include "MiniginPCH.h"
#include "GameObject.h"
#include "CTransform.h"
using namespace Crusade;

int GameObject::m_NextNameTag = 0;

GameObject::GameObject()
{
	m_Name = "GameObject" +std::to_string(m_NextNameTag) ;
	m_ObjectNummer = m_NextNameTag;
	m_NextNameTag++;
}

void GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate()
{
	for (const auto& component : m_Components)
	{
		component->FixedUpdate();
	}
}
void GameObject::LateUpdate()
{
	for (const auto& component : m_Components)
	{
		component->LateUpdate();
	}
}
void GameObject::OnCollisionEnter(CCollider* collider)
{
	for (const auto& component : m_Components)
	{
		component->OnCollisionEnter(collider);
	}
}
void GameObject::OnTriggerEnter(CCollider* trigger)
{
	for (const auto& component : m_Components)
	{
		component->OnTriggerEnter(trigger);
	}
}
void GameObject::OnCollisionExit(CCollider* collider)
{
	for (const auto& component : m_Components)
	{
		component->OnCollisionExit(collider);
	}
}
void GameObject::OnTriggerExit(CCollider* trigger)
{
	for (const auto& component : m_Components)
	{
		component->OnTriggerExit(trigger);
	}
}