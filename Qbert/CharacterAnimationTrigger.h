#pragma once
#include "BaseComponent.h"
namespace Crusade
{
	class CRender;
	class CAnimator2D;
}

class CharacterAnimationTrigger final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
private:
	Crusade::CAnimator2D* m_Animator = nullptr;
	Crusade::CRender* m_Render = nullptr;
	bool m_IsBack = false;
};
