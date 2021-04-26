#include "MiniginPCH.h"
#include "Hexagon.h"
#include "SceneManager.h"
#include "Scene.h"
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
	cube->AddComponent<CCollider>(std::make_shared<cHexagonCollider>(Rectf{ 0,0,m_HexaSize,m_HexaSize }));
	cube->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("Cube.png"));
	cube->AddTag("Cube");
	return cube;
}