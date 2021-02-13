#pragma once
#include  "BaseComponent.h"
namespace Crusade
{
	class CFPS final :public Component
	{
	public:
		void Update()override;
		int GetCurrentFPS()const;
		void SetMaxFrames(const float maxFrames) { m_MaxFrames = maxFrames; }
	private:
		void Reset();
		float m_LastFPS=0;
		float m_Frames=0;
		float m_AccuSec=0;
		float m_MaxFrames = 100;
	};
	
}