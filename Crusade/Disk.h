#pragma once
#include "BaseComponent.h"
#include "CTransform.h"
#include "PlayerController.h"
#include "MovementSteering.h"
#include "Prefab.h"
class DiskController final :public Crusade::Component
{
public:
	void Start() override;
	void Update() override;
	void SetEndPosition(const Vector2f& endpos) { m_EndPosition = endpos; }
	void SetSpeed(const float& speed) { m_Speed = speed; }
private:
	void OnTriggerEnter(Crusade::CCollider*) override;
	Crusade::CTransform* m_Transform = nullptr;
	PlayerControllerKeyBoard* m_Player=nullptr;
	Vector2f m_EndPosition{0,0};
	MovementSteering* m_Movement=nullptr;
	float m_Speed=200;
	bool m_IsActivated = false;
};
class Disk final :public Crusade::Prefab<Disk>
{
public :
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
private:
	float m_DiskSize = 20;
};