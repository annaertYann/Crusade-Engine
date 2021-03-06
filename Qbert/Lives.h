#pragma once
#include "CSaveLoad.h"
#include "Event.h"
#include "Prefab.h"
#include "GameObject.h"
class Lives final :public Crusade::CObserver
{
public:
	void RecieveNotification(Crusade::GameObject* actor, const std::string& message) override;
	void SetLives(int lives);
	int GetLives()const { return m_Lives; }
	void Update() override;
private:
	void Start() override;
	int m_Lives = 3;
	bool m_NeedsUpdate = false;
	std::vector<Crusade::GameObject*>m_LifeIndicators;
	Crusade::CTransform* m_Transform=nullptr;
};

class LifeIndicator final : public Crusade::Prefab<LifeIndicator>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
	float GetSize()const { return m_Size; }
private:
	float m_Size=30;
};
class LivesDisplay final : public Crusade::Prefab<LivesDisplay>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
	
};

class LifeSave final :public Crusade::CTextSave
{
public:
	LifeSave() :CTextSave("Life")
	{
		if (!m_HasResert)
		{
			Save();
		}
	}
	void SaveFromFile(std::ofstream& file) override;
private:
	static bool m_HasResert;
};
class LifeLoad final :public Crusade::CTextLoad
{
public:
	void Start() override { Load(); }
	LifeLoad() :CTextLoad("Life") {}
	void LoadFromFile(std::ifstream& file) override;
};