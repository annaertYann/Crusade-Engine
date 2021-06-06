#pragma once
#include "Button.h"
class SinglePlayerLoad final :public Crusade::ButtonAction
{
public:
	void Execute() override;
};
class CoopLoad final :public Crusade::ButtonAction
{
public:
	void Execute() override;
};
class VersusLoad final :public Crusade::ButtonAction
{
public:
	void Execute() override;
};
