#include "MiniginPCH.h"
#include "Levels.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "CRigidBody2D.h"
#include "Camera2D.h"
#include "Renderer.h"
#include "Qbert.h"
#include "Hexagon.h"
#include "FPS.h"
#include "Score.h"
#include "Lives.h"
#include "DeathBox.h"
#include "LevelFinisher.h"
#include "Disk.h"
using namespace Crusade;
void Level1::Load()
{
	std::vector<std::shared_ptr<GameObject>>objects{};
	//CAMERA
	auto window = Renderer::GetInstance().GetWindowSize();
	auto camera = std::make_shared<GameObject>();
	camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, window));
	camera->SetName("Camera");
	objects.push_back(camera);
	//ADD CUBES
	auto CubePyramid = std::make_shared<GameObject>();
	CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 320 - Cube::GetInstance().GetSize() / 2 ,480 - 100,0 }, glm::vec3{}));
	CubePyramid->AddComponent<HexagonLoad>(std::make_shared<HexagonLoad>(("Qbert1LevelLayout")));
	CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{ 255,0,0,255 }, SDL_Color{ 0,255,0,255 }));
	CubePyramid->AddComponent<HexagonSave>(std::make_shared<HexagonSave>( "Qbert1LevelLayout"));
	objects.push_back(CubePyramid);
	//ADD QBERT
	auto qbert = QBert::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
	//qbert->GetComponent<CTransform>()->SetScale(2, 2, 2);
	objects.push_back(qbert);
	//ADD FPS
	auto fps = std::make_shared<GameObject>();
	fps->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
	fps->AddComponent<CTextRender>(std::make_shared<CTextRender>("0", "Lingua.otf", 10, SDL_Color{ 0,255,0,255 }));
	fps->AddComponent<FPSScript>(std::make_shared<FPSScript>());
	objects.push_back(fps);
	//Score
	const auto score = ScoreDisplay::GetInstance().CreateObject(glm::vec3{ 540,460,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
	objects.push_back(score);
	//Lives
	const auto lives = LivesDisplay::GetInstance().CreateObject(glm::vec3{ 10,400,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
	objects.push_back(lives);
	//Deathbox
	objects.push_back((DeathBox::GetInstance().CreateObject(glm::vec3{ 0,10,0 }, glm::vec3{}, glm::vec3{ 1,1,1 })));
	//LevelFinisher
	auto levelFinisher = std::make_shared<GameObject>();
	levelFinisher->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
	levelFinisher->AddComponent<LevelFinisher>(std::make_shared<LevelFinisher>());
	levelFinisher->SetName("LevelFinisher");
	levelFinisher->GetComponent<LevelFinisher>()->SetNextLevelName("Qbert2");
	objects.push_back(levelFinisher);
	//ADD LEVEL NAME
	auto name = std::make_shared<GameObject>();
	name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 30,425,0 }, glm::vec3{}));
	name->AddComponent<CTextRender>(std::make_shared<CTextRender>("Level1", "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
	objects.push_back(name);
	//ADD LEVEL NAME
	auto Disk = Disk::GetInstance().CreateObject(glm::vec3{ 50,100,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
	objects.push_back(Disk);
	Add(objects);
}
void Level2::Load()
{
	std::vector<std::shared_ptr<GameObject>>objects{};
	//CAMERA
	auto window = Renderer::GetInstance().GetWindowSize();
	auto camera = std::make_shared<GameObject>();
	camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, window));
	camera->SetName("Camera");
	objects.push_back(camera);
	//ADD CUBES
	auto CubePyramid = std::make_shared<GameObject>();
	CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 320 - Cube::GetInstance().GetSize() / 2 ,480 - 100,0 }, glm::vec3{}));
	CubePyramid->AddComponent<HexagonLoad>(std::make_shared<HexagonLoad>(("Qbert2LevelLayout")));
	CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{ 255,0,0,255 }, SDL_Color{ 0,255,0,255 }));
	CubePyramid->AddComponent<HexagonSave>(std::make_shared<HexagonSave>("Qbert2LevelLayout"));
	objects.push_back(CubePyramid);
	//ADD QBERT
	auto qbert = QBert::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
	//qbert->GetComponent<CTransform>()->SetScale(2, 2, 2);
	objects.push_back(qbert);
	//ADD FPS
	auto fps = std::make_shared<GameObject>();
	fps->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
	fps->AddComponent<CTextRender>(std::make_shared<CTextRender>("0", "Lingua.otf", 10, SDL_Color{ 0,255,0,255 }));
	fps->AddComponent<FPSScript>(std::make_shared<FPSScript>());
	objects.push_back(fps);
	//Score
	const auto score = ScoreDisplay::GetInstance().CreateObject(glm::vec3{ 540,460,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
	objects.push_back(score);
	//Lives
	const auto lives = LivesDisplay::GetInstance().CreateObject(glm::vec3{ 10,400,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
	objects.push_back(lives);
	//Deathbox
	objects.push_back(DeathBox::GetInstance().CreateObject(glm::vec3{ 0,10,0 }, glm::vec3{}, glm::vec3{ 1,1,1 }));
	//LevelFinisher
	auto levelFinisher = std::make_shared<GameObject>();
	levelFinisher->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
	levelFinisher->AddComponent<LevelFinisher>(std::make_shared<LevelFinisher>());
	levelFinisher->SetName("LevelFinisher");
	levelFinisher->GetComponent<LevelFinisher>()->SetNextLevelName("Qbert3");
	objects.push_back(levelFinisher);
	//ADD LEVEL NAME
	auto name = std::make_shared<GameObject>();
	name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 30,425,0 }, glm::vec3{}));
	name->AddComponent<CTextRender>(std::make_shared<CTextRender>("Level2", "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
	objects.push_back(name);
	Add(objects);
}
void Level3::Load()
{
	std::vector<std::shared_ptr<GameObject>>objects{};
	{
		//CAMERA
		auto window = Renderer::GetInstance().GetWindowSize();
		auto camera = std::make_shared<GameObject>();
		camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, window));
		camera->SetName("Camera");
		objects.push_back(camera);
		//ADD CUBES
		auto CubePyramid = std::make_shared<GameObject>();
		CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 320 - Cube::GetInstance().GetSize() / 2 ,480 - 100,0 }, glm::vec3{}));
		CubePyramid->AddComponent<HexagonLoad>(std::make_shared<HexagonLoad>(("Qbert3LevelLayout")));
		CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{ 255,0,0,255 }, SDL_Color{ 0,255,0,255 }));
		CubePyramid->AddComponent<HexagonSave>(std::make_shared<HexagonSave>("Qbert3LevelLayout"));
		objects.push_back(CubePyramid);
		//ADD QBERT
		auto qbert = QBert::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
		//qbert->GetComponent<CTransform>()->SetScale(2, 2, 2);
		objects.push_back(qbert);
		//ADD FPS
		auto fps = std::make_shared<GameObject>();
		fps->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
		fps->AddComponent<CTextRender>(std::make_shared<CTextRender>("0", "Lingua.otf", 10, SDL_Color{ 0,255,0,255 }));
		fps->AddComponent<FPSScript>(std::make_shared<FPSScript>());
		objects.push_back(fps);
		//Score
		const auto score = ScoreDisplay::GetInstance().CreateObject(glm::vec3{ 540,460,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
		objects.push_back(score);
		//Lives
		const auto lives = LivesDisplay::GetInstance().CreateObject(glm::vec3{ 10,400,0 }, glm::vec3{}, glm::vec3{ 1,1,1 });
		objects.push_back(lives);
		//Deathbox
		objects.push_back(DeathBox::GetInstance().CreateObject(glm::vec3{ 0,10,0 }, glm::vec3{}, glm::vec3{ 1,1,1 }));
		//LevelFinisher
		auto levelFinisher = std::make_shared<GameObject>();
		levelFinisher->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 0,465,0 }, glm::vec3{}));
		levelFinisher->AddComponent<LevelFinisher>(std::make_shared<LevelFinisher>());
		levelFinisher->SetName("LevelFinisher");
		levelFinisher->GetComponent<LevelFinisher>()->SetNextLevelName("Qbert1");
		objects.push_back(levelFinisher);
		//ADD LEVEL NAME
		auto name = std::make_shared<GameObject>();
		name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 30,425,0 }, glm::vec3{}));
		name->AddComponent<CTextRender>(std::make_shared<CTextRender>("Level3", "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
		objects.push_back(name);
	}
	Add(objects);
}
