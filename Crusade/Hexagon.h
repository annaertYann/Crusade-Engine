#pragma once
#include "BaseComponent.h"
#include "RenderComponents.h"
#include "Prefab.h"
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
		permanent,switching
	};
	explicit CubeActivator(const TriggerType& triggerType = TriggerType::permanent,const SDL_Color& color1 = SDL_Color{ 1,0,0,1 }, const SDL_Color& color2 = SDL_Color{ 0,1,0,1 })
	:m_Color1(color1), m_Color2(color2),m_TriggerType(triggerType) {}
	void Start() override;
	void Notify(const std::string& message) override;
	void SetColors(const SDL_Color& color1, const SDL_Color& color2) { m_Color1 = color1; m_Color2 = color2; }
	void SetTriggerType(const TriggerType& type) { m_TriggerType = type; }
private:
	void TriggerPermanent();
	void TriggerSwitching();
	Crusade::CShape2DRender* m_Renderer=nullptr;
	SDL_Color m_Color1;
	SDL_Color m_Color2;
	TriggerType m_TriggerType;
	bool m_IsTrigged = false;
};
class CubePyramidConstructor final :public Crusade::Component
{
public:
	explicit CubePyramidConstructor(const CubeActivator::TriggerType& triggerType = CubeActivator::TriggerType::permanent,
		const SDL_Color& color1 = SDL_Color{ 1,0,0,1 }, const SDL_Color& color2 = SDL_Color{ 0,1,0,1 })
		:m_Color1(color1), m_Color2(color2),m_TriggerType(triggerType) {}
	void Awake() override;
private:
	SDL_Color m_Color1;
	SDL_Color m_Color2;
	CubeActivator::TriggerType m_TriggerType;
};