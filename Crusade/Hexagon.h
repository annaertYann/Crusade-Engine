#pragma once
#include "BaseComponent.h"
#include "Prefabs.h"
class CubePyramidConstructor final :public Crusade::Component
{
public:
	void Awake() override;
};

class Cube final : public Crusade::Prefab<Cube>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
	float GetSize()const { return m_HexaSize; }
private:
	float m_HexaSize = 70;
};