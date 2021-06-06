#include "MiniginPCH.h"
#include "Event.h"
using namespace Crusade;
void Publisher::AddObserver(GameObject* observer)
{
	auto comps = observer->GetAllComponents();
	for (auto comp:comps)
	{
		auto casted = dynamic_cast<CObserver*>(comp.get());
		if (casted !=nullptr)
		{
			m_observers.push_back(casted);
		}
	}
}
void Publisher::RemoveObserver(GameObject* observer)
{
	if (m_observers.size() > 0)
	{
		m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), [&](CObserver* element)
		{
			return observer->GetObjectNummer() == element->GetOwner()->GetObjectNummer();
		}), m_observers.end());
	}
}

void Publisher::SendNotification(const std::string& message)
{
	for (const auto& element:m_observers)
	{
		element->RecieveNotification(m_Owner, message);
	}
}
