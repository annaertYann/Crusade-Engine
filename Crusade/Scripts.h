#pragma once
#include "RenderComponents.h"
#include "BaseComponent.h"
#include "Delay.h"
#include "InputManager.h"
#include "Time.h"
class FPSScript final :public Crusade::Component
{
	public:
		void Update()override;
		float GetCurrentFPS()const { return m_CurrentFPS; };
	private:
		void Start() override;
		float m_CurrentFPS=0;
		Crusade::Delay m_RenderDelay{0.1f};
		Crusade::CTextRender* m_CTextRender {};
		Crusade::Time m_Time;
};

class QbertController final :public Crusade::Component
{
public:
	QbertController(int dieButton,int GainScoreButton);
	void Start() override;
	void Update() override;
private:
	std::unique_ptr<Crusade::CommandKillSwitch>m_DieSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_ScoreSwitch{};
	int m_DieButton;
	int m_ScoreButton;
};
class MoveInput final :public Crusade::Component
{
public:
	void Start() override;
	void Update() override;
private:
};