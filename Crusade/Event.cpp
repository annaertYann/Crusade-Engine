#include "MiniginPCH.h"
#include "Event.h"
using namespace Crusade;


int Observer::m_NextTag = 0;

Observer::Observer()
{
	m_Tag = m_NextTag;
	m_NextTag++;
	Publisher::GetInstance().AddObserver(this);
}
Observer::~Observer()
{
	Publisher::GetInstance().RemoveObserver(this);
}

void Publisher::AddObserver(Observer* observer)
{
	m_observers.push_back(observer);
}
void Publisher::RemoveObserver(Observer* observer)
{
	if (m_observers.size() > 0)
	{
		m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), [&](Observer* element)
		{
			return observer->GetTag() == element->GetTag();
		}), m_observers.end());
	}
}

void Publisher::Notify(GameObject* actor, const std::string& message)
{
	for (const auto& element:m_observers)
	{
		element->Notify(actor, message);
	}
}
