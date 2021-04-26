#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"



class QBertTest final : public Crusade::Prefab<QBertTest>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
};