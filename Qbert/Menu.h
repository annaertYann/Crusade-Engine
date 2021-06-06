#pragma once
#include "Scene.h"
#include "BaseComponent.h"
class TestHudElements : public Crusade::Component
{
public:
	void Update() override;
};
class Menu final :public Crusade::Scene
{
public:
	void Load() override;
};
