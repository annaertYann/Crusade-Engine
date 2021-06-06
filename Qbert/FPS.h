#pragma once
#include "Delay.h"
#include "RenderComponents.h"
#include "Time.h"
class FPSScript final :public Crusade::Component
{
public:
	void Update()override;
	float GetCurrentFPS()const { return m_CurrentFPS; };
private:
	void Awake() override;
	float m_CurrentFPS = 0;
	Crusade::Delay m_RenderDelay{ 0.1f };
	Crusade::CTextRender* m_CTextRender{};
	Crusade::Time m_Time;
};