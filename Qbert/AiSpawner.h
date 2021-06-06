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
	void spawnMonster();
	bool m_CoilySpawned = false;
	Crusade::Delay m_SpawnDelay{4.5f};
	std::vector<Crusade::GameObject*> m_Ai;
};