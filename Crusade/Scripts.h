#pragma once
#include "RenderComponents.h"
#include "BaseComponent.h"
#include "Delay.h"
#include "InputManager.h"
class FPSScript final :public Crusade::Component
{
	public:
		void Update()override;
		float GetCurrentFPS()const { return m_CurrentFPS; };
	private:
		void Start() override;
		float m_CurrentFPS=0;
		Crusade::Delay m_RenderDelay{0.1f};
	Crusade::CTextRender* m_CTextRender = nullptr;
};

class Lives final:public Crusade::Component
{
public:
	explicit Lives(const int& lives):m_Lives(lives){}
	void Start() override;
	void AddLifes(const int& lives) { m_Lives += lives; }
	int GetLives()const { return m_Lives; }
private:
	int m_Lives;
	std::unique_ptr<Crusade::CommandKillSwitch> m_KillSWitch;
};
