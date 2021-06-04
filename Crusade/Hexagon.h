#pragma once
#include "BaseComponent.h"
#include "RenderComponents.h"
#include "Prefab.h"
#include "Event.h"
#include "CSaveLoad.h"
class Cube final : public Crusade::Prefab<Cube>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
	float GetSize()const { return m_HexaSize; }
private:
	float m_HexaSize = 70;
};

class CubeActivator final:public Crusade::Component
{
public:
	enum class TriggerType
	{
		permanent,halfPermanent,switching
	};
	explicit CubeActivator(const TriggerType& triggerType = TriggerType::permanent,const SDL_Color& color1 = SDL_Color{ 1,0,0,1 }, const SDL_Color& color2 = SDL_Color{ 0,1,0,1 })
	:m_Color1(color1), m_Color2(color2),m_TriggerType(triggerType) {}
	void Start() override;
	void Awake() override;
	void Notify(const std::string& message) override;
	void SetColors(const SDL_Color& color1, const SDL_Color& color2);
	void SetTriggerType(const TriggerType& type) { m_TriggerType = type; }
private:
	void TriggerPermanent();
	void TriggerHalfPermanent();
	void TriggerSwitching();
	Crusade::CShape2DRender* m_Renderer=nullptr;
	SDL_Color m_Color1;
	SDL_Color m_Color2;
	TriggerType m_TriggerType;
	bool m_IsTrigged = false;
	Crusade::Publisher* m_Publisher=nullptr;
};
class CubePyramidConstructor final :public Crusade::Component
{
public:
	explicit CubePyramidConstructor(const CubeActivator::TriggerType& triggerType = CubeActivator::TriggerType::permanent,
		const SDL_Color& color1 = SDL_Color{ 1,0,0,1 }, const SDL_Color& color2 = SDL_Color{ 0,1,0,1 })
		:m_Color1(color1), m_Color2(color2),m_TriggerType(triggerType) {}
	void Awake() override;
	SDL_Color GetColor1()const { return m_Color1; }
	SDL_Color GetColor2()const { return m_Color2; }
	CubeActivator::TriggerType GetType()const { return m_TriggerType; }
private:
	float DiskSpawnRate = float(1.f/5.f);
	void CreateDisk(const glm::vec3& pos,bool left,float size);
	SDL_Color m_Color1;
	SDL_Color m_Color2;
	CubeActivator::TriggerType m_TriggerType;
	std::vector<CubeActivator*>m_Cubes{};
};
class HexagonSave final:public Crusade::CTextSave
{
public:
	void Start() override { Save(); }
	HexagonSave(const std::string& filename):CTextSave(filename){}
	void SaveFromFile(std::ofstream& file) override;
};
class HexagonLoad final :public Crusade::CTextLoad
{
public:
	struct saveInfo
	{
		glm::vec3 pos;
		SDL_Color color1;
		SDL_Color color2;
		int TriggerType;
	};
	explicit  HexagonLoad(const std::string& filename) :CTextLoad(filename) {}
	saveInfo GetInfo()const { return m_Info; }
private:
	void LoadFromFile(std::ifstream& file) override;
	saveInfo m_Info{};
};