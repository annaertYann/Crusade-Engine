#pragma once
#include "BaseComponent.h"
namespace Crusade
{
	class CRender final : public Component
	{
		public:
		explicit CRender(GameObject* owner):Component(owner){}
		void RenderObject()const;
	};
}
