#pragma once
#include  "BaseComponent.h"
namespace Crusade
{
	class CFPS final :public Component
	{
	public:
		explicit CFPS(GameObject* owner) :Component(owner){}
		void Update()override;
		int GetCurrentFPS()const;
	private:
		void Reset();
		float m_LastFPS=0;
		float m_Frames=0;
		float m_AccuSec=0;
		float m_MaxFrames = 100;
	};
	
}