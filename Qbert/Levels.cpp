#include "MiniginPCH.h"
#include "Levels.h"
#include "GameObject.h"
#include "CRigidBody2D.h"
#include "Camera2D.h"
#include "Qbert.h"
#include "Hexagon.h"
#include "FPS.h"
#include "Score.h"
#include "Lives.h"
#include "DeathBox.h"
#include "LevelFinisher.h"
#include "Disk.h"
#include "Ai.h"
#include "AIMovements.h"
#include "SoundPlayer.h"
using namespace Crusade;
void Level::Load()
{
	std::vector<std::shared_ptr<GameObject>>objects{};
	//ADD CUBES
	auto CubePyramid = std::make_shared<GameObject>();
	CubePyramid->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 320 - Cube::GetInstance().GetSize() / 2 ,480 - 100,0 }, glm::vec3{}));
	CubePyramid->AddComponent<HexagonLoad>(std::make_shared<HexagonLoad>((m_FilePath)));
	CubePyramid->AddComponent<CubePyramidConstructor>(std::make_shared<CubePyramidConstructor>(CubeActivator::TriggerType::switching, SDL_Color{ 255,0,0,255 }, SDL_Color{ 0,255,0,255 }));
	CubePyramid->AddComponent<HexagonSave>(std::make_shared<HexagonSave>(m_FilePath));
	objects.push_back(CubePyramid);
	//ADD QBERT
	auto qbert = QBert::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
	qbert->GetComponent<QbertController>()->AddKeyBoardControls();
	if (m_CurrentMode == Mode::singlePlayer)
	{
		qbert->GetComponent<QbertController>()->AddJoystickControls();
	}
	objects.push_back(qbert);
	if(m_CurrentMode==Mode::coop)
	{
		auto qbert1 = QBert::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
		qbert1->GetComponent<QbertController>()->AddJoystickControls();
		objects.push_back(qbert1);

		qbert->GetCTransform()->SetPosition(0,200,0);
		qbert1->GetCTransform()->SetPosition(640, 200, 0);
	}
	//FPS
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
	levelFinisher->GetComponent<LevelFinisher>()->SetNextLevelName(m_NextLevelName);
	objects.push_back(levelFinisher);
	//ADD LEVEL NAME
	auto name = std::make_shared<GameObject>();
	name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 30,425,0 }, glm::vec3{}));
	name->AddComponent<CTextRender>(std::make_shared<CTextRender>(m_LevelName, "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
	objects.push_back(name);
	//ADD AI
	auto AISpawner = AISpawnerPrefab::GetInstance().CreateObject(glm::vec3{ 320,640,0 });
	if (m_CurrentMode == Mode::verus)
	{
		CoilyMovement::SetStartStateToManual();
	}
	objects.push_back(AISpawner);
	//ADD SOUND PLAYER
	auto soundPlayer = std::make_shared<GameObject>();
	soundPlayer->AddComponent<SoundPlayer>(std::make_shared<SoundPlayer>());
	soundPlayer->SetName("SoundPlayer");
	objects.push_back(soundPlayer);
	Add(objects);
}
Level::Level(std::string levelName, std::string filepath, std::string nexLevelName)
{
	m_LevelName = levelName;
	m_FilePath = filepath;
	m_NextLevelName = nexLevelName;
}

Level1::Level1()
	:Level("Level1","Qbert1LevelLayout","Qbert2")
{

}
Level2::Level2()
	: Level("Level2", "Qbert2LevelLayout", "Qbert3")
{
	
}
Level3::Level3()
	: Level("Level3", "Qbert3LevelLayout", "Menu")
{
	
}
