#include "MiniginPCH.h"
#include "Score.h"
//Points are awarded for each color change(25), defeating Coily with a flying disc(500), remaining discs at the end of a stage(50) and catching Slickand Sam(300 each).
using namespace Crusade;
void Score::Start()
{
	m_Renderer = m_Owner->GetComponent<CTextRender>();
}
void Score::RecieveNotification(GameObject*, const std::string& message)
{
	if (message == "ColorChange")
	{
		m_Score += 25;
		m_NeedsUpdate = true;
	}
	else if (message == "CoilyDeath")
	{
		m_Score += 500;
		m_NeedsUpdate = true;
	}
	else if (message == "DiscRemain")
	{
		m_Score += 50;
		m_NeedsUpdate = true;
	}
	else if (message == "SamCatch")
	{
		m_Score += 300;
		m_NeedsUpdate = true;
	}
}
void Score::SetScore(int score)
{
	m_Score = score;
	m_NeedsUpdate = true;
}
void Score::Update()
{
	if(m_NeedsUpdate)
	{
		m_NeedsUpdate = false;
		m_Renderer->SetText("Score: " + std::to_string(m_Score));
	}
}

std::shared_ptr<GameObject> ScoreDisplay::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<CTransform>(std::make_shared<CTransform>(position,rotation,scale));
	obj->AddComponent<CTextRender>(std::make_shared<CTextRender>("Score: 0", "Lingua.otf",15,SDL_Color{255,255,255,255}));
	obj->AddComponent<Score>(std::make_shared<Score>());
	obj->SetName("ScoreDisplay");
	return obj;
}
