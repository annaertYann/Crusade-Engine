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
void GameObject::Notify(const std::string& message)
{
	for (const auto& component : m_Components)
	{
		component->Notify(message);
	}
}

void GameObject::Update()
{
	if(!m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->Start();
		}
		m_Start = true;
	}
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate()
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->FixedUpdate();
		}
	}
}
void GameObject::LateUpdate()
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->LateUpdate();
		}
	}
}
void GameObject::OnCollisionEnter(CCollider* collider)
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->OnCollisionEnter(collider);
		}
	}
}
void GameObject::OnTriggerEnter(CCollider* trigger)
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->OnTriggerEnter(trigger);
		}
	}
}
void GameObject::OnCollisionExit(CCollider* collider)
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->OnCollisionExit(collider);
		}
	}
}
void GameObject::OnTriggerExit(CCollider* trigger)
{
	if (m_Start)
	{
		for (const auto& component : m_Components)
		{
			component->OnTriggerExit(trigger);
		}
	}
}