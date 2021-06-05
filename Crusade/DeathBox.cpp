#include "MiniginPCH.h"
#include "DeathBox.h"
using namespace Crusade;
std::shared_ptr<GameObject> DeathBox::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto rigid = std::make_shared<CRigidBody2D>();
	rigid->SetGravityEnabled(false);
	auto col = std::make_shared<CRectCollider>(Rectf{0,0,1000,10});
	col->SetDebugDrawing(true);
	obj->AddComponent<CCollider>(col);
	obj->AddComponent<CRigidBody2D>(rigid);
	obj->AddComponent<Eraser>(std::make_shared<Eraser>());
	obj->AddComponent<CRender>(std::make_shared<CRender>());
	obj->SetName("DeathBox");
	return obj;
}
void Eraser::OnTriggerEnter(CCollider* col)
{
	col->GetOwner()->Notify("Death");
}
