#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component/Transform.h"
using namespace Crusade;

int GameObject::m_NextTag = 0;

GameObject::GameObject()
{
	AddComponent<Transform>(std::make_shared<Transform>());
	m_Tag = m_NextTag;
	m_NextTag++;
}

void GameObject::SendCommand(const Component::Command& command)
{
	for (const auto& component :m_Components)
	{
		component->SendCommand(command);
	}
}
void GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

