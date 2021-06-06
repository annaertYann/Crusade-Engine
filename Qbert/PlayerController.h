#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "Delay.h"
#include "MovementSteering.h"
#include "Colliders2D.h"
#include "Event.h"
class CharacterMovement final:public Crusade::Component
{
public:
	CharacterMovement(float objectSize);
	void Start() override;
	void Update() override;
	void Notify(const std::string& message) override;
	void SetOffMapTarget(const Vector2f& pos,const float& speed);//This disables normal movement
	void ResetToStart();
	bool IsJumpingOffEdge()const { return m_DieDelay.GetIsActive(); }
	bool IsFalling()const { return m_RigidBody->GetIsGravityEnabled(); }
	void ResetDeathAnim();
	void Die();
	void SetTargetToClosestCube();
	
	void TriggerCurrentCube();
	void ResetCurrentCube();
	void IgnoreCurrentCube() { m_CubeIsTriggerd = true; }
private:
	void NotifyObjectOfJump()const;
	void SetTargetToCurrentCube()const;
	void SetTargetWhenNoCubeFound();
	bool Move();
	float m_ObjectSize;
	bool m_IsLeftSelected = false;
	bool m_CubeIsTriggerd = false;
	bool m_IsEnabled = true;
	bool m_JumpedToBack = true;
	bool m_IsFalling = false;
	MovementSteering* m_MovementSteering=nullptr;
	Vector2f m_Direction{};
	Crusade::Delay m_DirectionChoiceDelay{0.3f};
	Crusade::Delay m_DieDelay{0.1f};
	std::vector<Crusade::CCollider*>m_Cubes;
	Crusade::CRigidBody2D* m_RigidBody = nullptr;
	Crusade::CCollider* m_CurrentCube = nullptr;
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
class UpMovementTrigger final :public Crusade::Command
{
public:
	explicit UpMovementTrigger(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class DownMovementTrigger final :public Crusade::Command
{
public:
	explicit DownMovementTrigger(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class RightMovementTrigger final :public Crusade::Command
{
public:
	explicit RightMovementTrigger(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};
class LeftMovementTrigger final :public Crusade::Command
{
public:
	explicit LeftMovementTrigger(Crusade::GameObject* actor) :Command(actor) { }
	void Execute() override;
};