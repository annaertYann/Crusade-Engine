#pragma once
#include "BaseComponent.h"
#include "Prefab.h"
class Eraser final : public Crusade::Component
{
private:
	void OnTriggerEnter(Crusade::CCollider* col) override;
};

class DeathBox final : public Crusade::Prefab<DeathBox>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
};
