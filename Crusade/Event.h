#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Singleton.h"
namespace Crusade
{
	class Observer:public Component
	{
	public:
		Observer();
		virtual ~Observer()override;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		
		virtual void Notify(GameObject* actor,const  std::string& message) = 0;
		int GetTag()const { return m_Tag; }
	private:
		static int m_NextTag;
		int m_Tag=0;
	};


	class Publisher final :public Singleton<Publisher>
	{
	public:
		void Notify(GameObject* actor, const std::string& message);
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
	private:
		std::vector<Observer*> m_observers{};
	};

}


