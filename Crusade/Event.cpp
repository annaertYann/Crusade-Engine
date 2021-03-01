#include "MiniginPCH.h"
#include "Event.h"
using namespace Crusade;


int CObserver::m_NextTag = 0;

CObserver::CObserver()
{
	m_Tag = m_NextTag;
	m_NextTag++;
	Publisher::GetInstance().AddObserver(this);
}
CObserver::~CObserver()
{
	Publisher::GetInstance().RemoveObserver(this);
}

void Publisher::AddObserver(CObserver* observer)
{
	m_observers.push_back(observer);
}
void Publisher::RemoveObserver(CObserver* observer)
{
	if (m_observers.size() > 0)
	{
		m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), [&](CObserver* element)
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
