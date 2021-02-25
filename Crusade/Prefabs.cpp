#include "MiniginPCH.h"
#include "Prefabs.h"
#include "InputManager.h"
#include "Scripts.h"
#include "ResourceManager.h"
using namespace Crusade;
/////////////////////////////////////////////////////////////////////////////////
//QBERT
/////////////////////////////////////////////////////////////////////////////////
void PlayerDied::Execute()
{
	Publisher::GetInstance().Notify(m_Actor, "PlayerDied");
	std::cout << "PlayerDied" << std::endl;
}
std::shared_ptr<GameObject> Qbert::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto qBert = std::make_shared<GameObject>();
	qBert->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	qBert->AddComponent<Lives>(std::make_shared<Lives>(3));
	qBert->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("Qbert/Idle.png")));
	return qBert;
}


/////////////////////////////////////////////////////////////////////////////////
//LIVES DISPLAY
/////////////////////////////////////////////////////////////////////////////////
void LivesCounter::Notify(GameObject* actor, const std::string& message)
{
	if (message=="PlayerDied")
	{
		auto lives = actor->GetComponent<Lives>();
		if (lives)
		{
			lives->AddLifes(-1);
			if (lives->GetLives() > 0)
			{
				auto text = m_Owner->GetComponent<CTextRender>();
				if (text)
				{
					text->SetText("Lives: " + std::to_string(lives->GetLives()));
				}
			}
			else
			{
				actor->SetRemove();
				auto text = m_Owner->GetComponent<CTextRender>();
				if (text)
				{
					text->SetText("Lives: 0");
				}
				//DEFEAT SCREEN OR SOMETHING
				////////////////
				////////////////
			}
		}
	}
}
