#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
namespace Crusade
{
	class CObserver:public Component
	{
	public:
		virtual void RecieveNotification(GameObject* actor,const  std::string& message) = 0;
	};
	
	class Publisher final :public Component
	{
	public:
		void SendNotification(const std::string& message);
		void AddObserver(GameObject* observer);
		void RemoveObserver(GameObject* observer);
	private:
		std::vector<CObserver*> m_observers{};
	};

}


