#pragma once
#include "Event.h"
#include "RenderComponents.h"
#include "Prefab.h"
//Points are awarded for each color change(25), defeating Coily with a flying disc(500), remaining discs at the end of a stage(50) and catching Slickand Sam(300 each).
class Score final:public Crusade::CObserver
{
public:
	void Start() override;
	void RecieveNotification(Crusade::GameObject* actor, const std::string& message) override;
private:
	int m_Score=0;
	Crusade::CTextRender* m_Renderer=nullptr;
};
class ScoreDisplay final : public Crusade::Prefab<ScoreDisplay>
{
public:
	std::shared_ptr<Crusade::GameObject> CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) override;
};