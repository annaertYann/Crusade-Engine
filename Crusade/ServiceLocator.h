#pragma once
#include "Sound_System.h"
#include "Singleton.h"
namespace Crusade
{
	
	class ServiceLocator :public Singleton<ServiceLocator>
	{
		static Sound_System* m_SS_Instance;
	public:
		static Sound_System* GetSoundSystem() { return m_SS_Instance; }
		static void RegisterSoundSystem(Sound_System* ss)
		{
			if (m_SS_Instance != nullptr)
			{
				delete m_SS_Instance;
			}
			m_SS_Instance = ss;
		}
		~ServiceLocator()
		{
			if (m_SS_Instance!=nullptr)
			{
				delete m_SS_Instance;
			}
		}
	};
}
