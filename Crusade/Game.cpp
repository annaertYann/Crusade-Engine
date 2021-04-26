#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "CRigidBody2D.h"
#include "Camera2D.h"
#include "Renderer.h"
#include "Qbert.h"
#include "Hexagon.h"
using namespace Crusade;
void Game::LoadGame()const
{
	//TEST SCENE
	{
	}
	//QBERT GAME
	{
		auto& scene1 = SceneManager::GetInstance().CreateScene("Qbert");
		//SET CURRENT SCENE
		SceneManager::GetInstance().SetCurrentScene("Qbert");
		//CAMERA
		auto window = Renderer::GetInstance().GetWindowSize();
		auto camera = std::make_shared<GameObject>();
		camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 },window ));
		camera->SetName("Camera");
		scene1.Add(camera);

		auto CubePyramid = std::make_shared<GameObject>();
		CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{320-Cube::GetInstance().GetSize()/2 ,480-100,0},glm::vec3{}));
		CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{1,0,0,1},SDL_Color{0,1,0,1}));
		scene1.Add(CubePyramid);

		auto qbert = QBert::GetInstance().CreateObject(glm::vec3{320,640,0});
		//qbert->GetComponent<CTransform>()->SetScale(2, 2, 2);
		scene1.Add(qbert);

		
	}
}
