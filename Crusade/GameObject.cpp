#include "MiniginPCH.h"
#include "GameObject.h"
#include "CTransform.h"
using namespace Crusade;

int GameObject::m_NextNameTag = 0;

GameObject::GameObject()
{
	m_Name = "GameObject" +std::to_string(m_NextNameTag) ;
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
