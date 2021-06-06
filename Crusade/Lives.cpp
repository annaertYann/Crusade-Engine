#include "MiniginPCH.h"
#include "Lives.h"
#include "RenderComponents.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Score.h"
using namespace Crusade;
void Lives::Start()
{
	m_Transform = m_Owner->GetCTransform();
	m_NeedsUpdate = true;
}
void Lives::RecieveNotification(GameObject*, const std::string& message)
{
	if(message=="Death")
	{
		if (m_Lives > 0)
		{
			m_LifeIndicators.back()->SetRemove();
			m_LifeIndicators.pop_back();
			m_Lives--;
			std::cout << "Qbert Died : lives-1" << std::endl;
			if(m_Lives<=0)
			{
				SceneManager::GetInstance().LoadScene("Menu");
			}
		}
	}
	else if (message=="GainLife")
	{
		auto pos = m_Transform->GetPosition();
		auto& indicator = LifeIndicator::GetInstance();
		pos.y -= m_Lives * indicator.GetSize();
		auto obj = indicator.CreateObject(pos, m_Transform->GetRotation(), m_Transform->GetScale());
		SceneManager::GetInstance().GetCurrentScene()->Add(obj);
		m_LifeIndicators.push_back(obj.get());
		m_Lives++;
		std::cout << "Qbert gained a life" << std::endl;
	}
}
void Lives::Update()
{
	if(m_NeedsUpdate)
	{
		m_NeedsUpdate = false;
		for (auto ind : m_LifeIndicators)
		{
			ind->SetRemove();
		}
		m_LifeIndicators.clear();
		auto pos = m_Transform->GetPosition();
		auto& indicator = LifeIndicator::GetInstance();
		for (int i{}; i < m_Lives; i++)
		{
			pos.y -= indicator.GetSize();
			auto obj = indicator.CreateObject(pos, m_Transform->GetRotation(), m_Transform->GetScale());
			SceneManager::GetInstance().GetCurrentScene()->Add(obj);
			m_LifeIndicators.push_back(obj.get());
		}
	}
}
void Lives::SetLives(int lives)
{
	m_Lives = lives;
	m_NeedsUpdate = true;
}

std::shared_ptr<GameObject> LifeIndicator::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	obj->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("Qbert/Idle.png", glm::vec2{m_Size,m_Size }));
	return obj;
}
std::shared_ptr<GameObject> LivesDisplay::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	obj->AddComponent<CTextRender>(std::make_shared<CTextRender>("Lives:", "Lingua.otf", 15, SDL_Color{ 255,255,255,255 }));
	obj->AddComponent<Lives>(std::make_shared<Lives>());
	obj->AddComponent<LifeLoad>(std::make_shared<LifeLoad>());
	obj->AddComponent<LifeSave>(std::make_shared<LifeSave>());
	obj->SetName("LivesDisplay");
	return obj;
}


bool LifeSave::m_HasResert = false;
void LifeSave::SaveFromFile(std::ofstream& file)
{
	if (!m_HasResert)
	{
		file << "Life" << std::endl;
		file << 3 << std::endl;
		m_HasResert = true;
	}
	else
	{
		auto score = m_Owner->GetComponent<Lives>();
		file << "Life" << std::endl;
		file << score->GetLives() << std::endl;
	}
}
void LifeLoad::LoadFromFile(std::ifstream& file)
{
	auto life = m_Owner->GetComponent<Lives>();
	std::string line{};
	while (file)
	{
		std::getline(file, line);
		if (line == "Life")
		{
			std::getline(file, line);
			life->SetLives(std::stoi(line));
		}
	}
}


