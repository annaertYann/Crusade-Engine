#pragma once
#include "Prefab.h"

class Coily final : public Crusade::Prefab<Coily>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
private:
};
