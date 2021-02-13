#pragma once
#include "BaseComponent.h"
#include "Delay.h"
namespace Crusade
{
	
	class DisplayFPS final :public Component
	{
	public:
		void Update()override;
	private:
		Delay m_delay{0.1f};
	};
}