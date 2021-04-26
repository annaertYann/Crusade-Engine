#pragma once
#include "RenderComponents.h"
#include "BaseComponent.h"
#include "Delay.h"
#include "InputManager.h"
#include "Time.h"
#include "CSaveLoad.h"
class FPSScript final :public Crusade::Component
{
	public:
		void Update()override;
		float GetCurrentFPS()const { return m_CurrentFPS; };
	private:
		void Awake() override;
		float m_CurrentFPS=0;
		Crusade::Delay m_RenderDelay{0.1f};
		Crusade::CTextRender* m_CTextRender {};
		Crusade::Time m_Time;
};

class QbertController final :public Crusade::Component
{
public:
	QbertController(int dieButton,int GainScoreButton);
	void Awake() override;
	void Update() override;
private:
	std::unique_ptr<Crusade::CommandKillSwitch>m_DieSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_ScoreSwitch{};
	int m_DieButton;
	int m_ScoreButton;
};



class TestInput final :public Crusade::Component
{
public:
	void Awake() override;
	void Update() override;
private:
};
class BallSave: public Crusade::CTextSave
{
public:
	BallSave(std::string file):CTextSave(file){}
private:
	void SaveFromFile(std::ofstream& file) override;
};
class BallLoad:public Crusade::CTextLoad
{
public:
	BallLoad(std::string file) :CTextLoad(file) {}
private:
	void LoadFromFile(std::ifstream& file) override;
	void Awake() override { Load(); }
};