#include "MiniginPCH.h"
#include "GameObject.h"
using namespace Crusade;

void GameObject::SendCommand(const Component::Command& command)
{
	for (const auto& component :m_components)
	{
		component->SendCommand(command);
	}
}
void GameObject::Update()
{
	for (const auto& component : m_components)
	{
		component->Update();
	}
}

