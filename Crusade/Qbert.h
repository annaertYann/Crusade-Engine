#pragma once
#include "Prefab.h"
#include "Command.h"
#include "Event.h"
#include "CAnimator2D.h"
class QBert final : public Crusade::Prefab<QBert>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = { 1,1,1 }) override;
};
class QbertAnimationTriggerer final :public Crusade::Component
{
public:
	void Start() override;
	void Notify(const std::string& message) override;
private:
	Crusade::CAnimator2D* m_Animator=nullptr;
	Crusade::CRender* m_Render = nullptr;
	bool m_IsBack = false;
};