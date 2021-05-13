#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "Delay.h"
#include "MovementSteering.h"
#include "Colliders2D.h"
#include "Event.h"
class PlayerControllerKeyBoard final:public Crusade::Component
{
public:
	PlayerControllerKeyBoard(int UpButton, int DownButton,int LeftButton,int RightButton,float objectSize);
	void Awake() override;
	void Start() override;
	void Update() override;
	void Notify(const std::string& message) override;
	void SetOffMapTarget(const Vector2f& pos,const float& speed);//This disables normal movement
	void ResetToStart();
private:
	void TriggerCurrentCube();
	void NotifyObjectOfJump()const;
	void SetTargetToCurrentCube()const;
	void SetTargetWhenNoCubeFound();
	bool Move();
	std::unique_ptr<Crusade::CommandKillSwitch>m_UpSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_DownSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_LeftSwitch{};
	std::unique_ptr<Crusade::CommandKillSwitch>m_RightSwitch{};
	int m_UpButton;
	int m_DownButton;
	int m_LeftButton;
	int m_RightButton;
	float m_ObjectSize;
	bool m_IsLeftSelected = false;
	bool m_CubeIsTriggerd = false;
	bool m_IsEnabled = true;
	bool m_JumpedToBack = true;
	MovementSteering* m_MovementSteering=nullptr;
	Vector2f m_Direction{};
	Crusade::Delay m_DirectionChoiceDelay{0.3f};
	Crusade::Delay m_DieDelay{0.4f};
	std::vector<Crusade::CCollider*>m_Cubes;
	Crusade::CRigidBody2D* m_RigidBody = nullptr;
	Crusade::CCollider* m_CurrentCube = nullptr;
	Crusade::Publisher* m_Publisher=nullptr;
	Crusade::CRender* m_Renderer = nullptr;
	glm::vec3 m_StartPos={};
};
class UpMovementKey final :public Crusade::Command
{
public:
	explicit UpMovementKey(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class DownMovementKey final :public Crusade::Command
{
public:
	explicit DownMovementKey(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class RightMovementKey final :public Crusade::Command
{
public:
	explicit RightMovementKey(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class LeftMovementKey final :public Crusade::Command
{
public:
	explicit LeftMovementKey(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};