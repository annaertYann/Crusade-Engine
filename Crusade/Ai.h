#pragma once
#include "Prefab.h"

class Coily final : public Crusade::Prefab<Coily>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
private:
};
class Ugg final : public Crusade::Prefab<Ugg>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
private:
};
class WrongWay final : public Crusade::Prefab<WrongWay>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
private:
};

class AISpawnerPrefab final : public Crusade::Prefab<AISpawnerPrefab>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
private:
};