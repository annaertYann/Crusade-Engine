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
#include "FPS.h"
#include "Score.h"
#include "Lives.h"
#include "DeathBox.h"
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
		//ADD CUBES
		auto CubePyramid = std::make_shared<GameObject>();
		CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{320-Cube::GetInstance().GetSize()/2 ,480-100,0},glm::vec3{}));
		CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{1,0,0,1},SDL_Color{0,1,0,1}));
		scene1.Add(CubePyramid);
		//ADD QBERT
		auto qbert = QBert::GetInstance().CreateObject(glm::vec3{320,640,0});
		//qbert->GetComponent<CTransform>()->SetScale(2, 2, 2);
		scene1.Add(qbert);
		//ADD FPS
		auto fps = std::make_shared<GameObject>();
		fps->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{0,465,0},glm::vec3{}));
		fps->AddComponent<CTextRender>(std::make_shared<CTextRender>("0", "Lingua.otf", 10, SDL_Color{ 0,1,0,1 }));
		fps->AddComponent<FPSScript>(std::make_shared<FPSScript>());
		scene1.Add(fps);
		//Score
		const auto score = ScoreDisplay::GetInstance().CreateObject(glm::vec3{540,460,0}, glm::vec3{}, glm::vec3{1,1,1});
		scene1.Add(score);
		//Lives
		const auto lives = LivesDisplay::GetInstance().CreateObject(glm::vec3{10,400,0}, glm::vec3{}, glm::vec3{1,1,1});
		scene1.Add(lives);
		//Deathbox
		scene1.Add(DeathBox::GetInstance().CreateObject(glm::vec3{ 0,10,0 }, glm::vec3{}, glm::vec3{ 1,1,1 }));
	}
}
