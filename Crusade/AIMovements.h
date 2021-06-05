#pragma once
#include "BaseComponent.h"
#include "Delay.h"
#include "CTransform.h"
#include "Event.h"
#include "InputManager.h"
class CharacterMovement;
class CoilyMovment final:public Crusade::Component
{
public:
	enum class State
	{
		egg,
		chase
		,manualWaiting
		,manual
	};
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
	void SetToManualControl() { if (m_CurrentState == State::egg) { m_CurrentState = State::manualWaiting; } }
private:
	void AddPlayerControls();
	void EggUpdate();
	void ChaseUpdate();
	void Transform();
	void OnTriggerEnter(Crusade::CCollider*) override;
	std::vector<Crusade::CTransform*>m_QbertTransforms;
	Crusade::CTransform* m_QbertChoice = nullptr;
	CharacterMovement* m_Movement = nullptr;
	State m_CurrentState=State::egg;
	Crusade::Delay m_MoveDelay{1.f};
	bool m_MoveLeftSwitch = false;
	int m_JumpCounter = 0;
	int m_maxJumpsBeforeTransform = 6;
	Crusade::Publisher* m_Publisher=nullptr;

	std::unique_ptr<Crusade::CommandKillSwitch>m_UpSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_DownSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_LeftSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_RightSwitchTrigger{};
};
class UggMovement final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
private:
	void OnTriggerEnter(Crusade::CCollider*) override;
	CharacterMovement* m_Movement = nullptr;
	Crusade::Delay m_MoveDelay{ 1.f };
};
class WrongWayMovement final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
private:
	void OnTriggerEnter(Crusade::CCollider*) override;
	CharacterMovement* m_Movement = nullptr;
	Crusade::Delay m_MoveDelay{ 1.f };
	
};
class SlickMovement final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
private:
	void OnTriggerEnter(Crusade::CCollider*) override;
	CharacterMovement* m_Movement = nullptr;
	Crusade::Delay m_MoveDelay{ 1.f };
	Crusade::Publisher* m_Publisher = nullptr;
};
class SamMovement final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
private:
	void OnTriggerEnter(Crusade::CCollider*) override;
	CharacterMovement* m_Movement = nullptr;
	Crusade::Delay m_MoveDelay{ 1.f };
	Crusade::Publisher* m_Publisher = nullptr;
};