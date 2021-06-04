#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"
#include "CAnimator2D.h"
#include "PlayerController.h"
class QBert final : public Crusade::Prefab<QBert>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
	float GetSpeed()const { return m_Speed; }
private:
	float m_Speed = 200;
};
class QbertAnimationTriggerer final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
private:
	Crusade::CAnimator2D* m_Animator=nullptr;
	Crusade::CRender* m_Render = nullptr;
	bool m_IsBack = false;
};

class QbertController final : public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
	void Update() override;
	void AddKeyBoardControls();
	void AddJoystickControls();
private:
	std::unique_ptr<Crusade::CommandKillSwitch>m_UpSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_DownSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_LeftSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_RightSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_UpSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_DownSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_LeftSwitchTrigger{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_RightSwitchTrigger{};
	CharacterMovement* m_Movement=nullptr;
	Crusade::Publisher* m_Publisher = nullptr;
	int m_Counter=0;
};
