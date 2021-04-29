#include "MiniginPCH.h"
#include "Hexagon.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Event.h"
using namespace Crusade;
void CubePyramidConstructor::Awake()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	//const auto window = scene->FindObject("Camera")->GetComponent<Camera2D>()->GetOriginalWindow();
	const auto pos = m_Owner->GetCTransform()->GetPosition();
	auto HEXAGON = Cube::GetInstance().CreateObject({ pos.x,pos.y,pos.z }, {}, {1,1,1});
	const auto hexaSize = HEXAGON->GetComponent<CRender>()->GetDimensions().x;
	auto numberOfCubesInRow = 1;
	for (int j{}; j < 7; j++)
	{
		for (int i{}; i < numberOfCubesInRow; i++)
		{
			auto obj = Cube::GetInstance().CreateObject({ pos.x - (j * hexaSize / 2) + (i * hexaSize),pos.y - j * hexaSize * 3 / 4  ,pos.z }, {}, {1,1,1});
			scene->Add(obj);
			auto activator = obj->GetComponent<CubeActivator>();
			activator->SetColors(m_Color1, m_Color2);
			activator->SetTriggerType(m_TriggerType);
		}
		numberOfCubesInRow++;
	}
	
}
std::shared_ptr<GameObject> Cube::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	auto cube = std::make_shared<GameObject>();
	cube->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	cube->AddComponent<CRender>(std::make_shared<CRender>());
	cube->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Hexagon, glm::vec2{ m_HexaSize,m_HexaSize }, false, SDL_Color{ 1,0,0,1 }));
	auto col = std::make_shared<cHexagonCollider>(Rectf{ 0,0,m_HexaSize,m_HexaSize });
	col->SetIsTrigger(true);
	cube->AddComponent<CCollider>(col);
	cube->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("Cube.png"));
	cube->AddComponent<CubeActivator>(std::make_shared<CubeActivator>());
	cube->AddComponent<Publisher>(std::make_shared<Publisher>());
	cube->AddTag("Cube");
	cube->SetName("Cube");
	return cube;
}
void CubeActivator::Start()
{
	m_Renderer = m_Owner->GetComponent<CShape2DRender>();
	m_Publisher = m_Owner->GetComponent<Publisher>();
	m_Publisher->AddObserver( SceneManager::GetInstance().GetCurrentScene()->FindObject("ScoreDisplay").get());
}
void CubeActivator::Notify(const std::string& message)
{
	if (message == "Triggered")
	{
		switch (m_TriggerType)
		{
		case TriggerType::permanent:
			TriggerPermanent();
			break;
		case TriggerType::switching:
			TriggerSwitching();
			break;
		}
	}
}
void CubeActivator::TriggerPermanent()
{
	m_IsTrigged = true;
	m_Renderer->SetColor(m_Color2);
	if (m_Publisher) { m_Publisher->SendNotification("ColorChange"); }
}
void CubeActivator::TriggerSwitching()
{
	utils::SwitchBoolean(m_IsTrigged);
	if (m_IsTrigged)
	{
		m_Renderer->SetColor(m_Color2);
	}
	else
	{
		m_Renderer->SetColor(m_Color1);
	}
	if (m_Publisher) {m_Publisher->SendNotification("ColorChange");}
}

