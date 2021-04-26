#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Singleton.h"
namespace Crusade
{
	class CObserver:public Component
	{
	public:
		CObserver();
		virtual ~CObserver()override;

		CObserver(const CObserver& other) = delete;
		CObserver(CObserver&& other) = delete;
		CObserver& operator=(const CObserver& other) = delete;
		CObserver& operator=(CObserver&& other) = delete;
		
		virtual void Notify(GameObject* actor,const  std::string& message) = 0;
		int GetTag()const { return m_Tag; }
	private:
		static int m_NextTag;
		int m_Tag=0;
	};


	class Publisher final :public Singleton<Publisher> /////////// MAKE COMP U IDIOTA
	{
	public:
		void Notify(GameObject* actor, const std::string& message);
		void AddObserver(CObserver* observer);
		void RemoveObserver(CObserver* observer);
	private:
		std::vector<CObserver*> m_observers{};
	};

}


