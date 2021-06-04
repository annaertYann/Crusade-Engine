#pragma once
#include "BaseComponent.h"
#include "Delay.h"
class AiSpawner final :public Crusade::Component
{
public:
	enum class Monsters
	{
		coily
		,ugg ,wrongway
		,slick,sam
		,END
	};
	void Update() override;
	void LateUpdate() override;
private:
	bool IsMonsterInList(const std::string& name);
	Crusade::Delay m_SpawnDelay{10.f};
	std::vector<Crusade::GameObject*> m_Ai;
};