#include "MiniginPCH.h"
#include "Disk.h"
#include "GameObject.h"
#include "RenderComponents.h"
using namespace Crusade;
void DiskController::Start()
{
	m_Transform = m_Owner->GetComponent<CTransform>();
	m_Movement = m_Owner->GetComponent<MovementSteering>();
	m_Movement->SetMovementBehaviour(std::make_shared<Seek>(m_Speed));
	m_Movement->SetTarget(Vector2f{m_Transform->GetPosition().x,m_Transform->GetPosition().y});
}
void DiskController::OnTriggerEnter(CCollider* col)
{
	if (!m_Player)
	{
		const auto player = col->GetOwner()->GetComponent<CharacterMovement>();
		if (player)
		{
			if (player->IsJumpingOffEdge())
			{
				m_Player = player;
				auto trans = player->GetOwner()->GetComponent<CTransform>();
				auto pos = trans->GetPosition();
				pos.x = m_Owner->GetCTransform()->GetPosition().x;
				pos.y = m_Owner->GetCTransform()->GetPosition().y;
				trans->SetPosition(pos.x, pos.y, pos.z);
				m_Movement->SetTarget(m_EndPosition);
			}
		}
	}
}
void DiskController::Update()
{
	if (m_Player)
	{
		
		if ( !m_IsActivated)
		{
			auto pos = m_Player->GetOwner()->GetComponent<CTransform>()->GetPosition();
			auto pos1 = m_Owner->GetComponent<CTransform>()->GetPosition();
			auto diff = pos - pos1;
			m_Player->SetOffMapTarget(Vector2f{ m_EndPosition.x + diff.x,m_EndPosition.y + diff.y }, m_Speed);
			m_IsActivated = true;
		}
		if ( m_IsActivated)
		{
			auto pos = glm::vec3{ m_EndPosition.x,m_EndPosition.y,0 };
			auto pos1 = m_Owner->GetComponent<CTransform>()->GetPosition();
			auto diff = pos - pos1;
			if (abs(diff.x) < 5)
			{
				m_Player->ResetToStart();
				m_Owner->SetRemove();
			}
		}
	}
}
std::shared_ptr<GameObject> Disk::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	obj->AddComponent<DiskController>(std::make_shared<DiskController>());
	obj->AddComponent<MovementSteering>(std::make_shared<MovementSteering>(std::make_shared<Seek>()));
	obj->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect, glm::vec2{ m_DiskSize,m_DiskSize }, false, SDL_Color{255,0,0,255}));
	obj->AddComponent<CRectCollider>(std::make_shared<CRectCollider>(Rectf{ 0,0,m_DiskSize,m_DiskSize }));
	obj->AddComponent<CRigidBody2D>(std::make_shared<CRigidBody2D>());
	obj->GetComponent<CRigidBody2D>()->SetGravityEnabled(false);
	obj->GetComponent<CCollider>()->SetIsTrigger(true);
	obj->GetComponent<DiskController>()->SetEndPosition(Vector2f{320,480});
	obj->GetComponent<CRender>()->SetCurrentLayer("Front");
	obj->SetName("Disk");
	return obj;
}
